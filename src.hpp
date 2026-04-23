
#pragma once //include guard

#undef strtok

char *strtok(char * __restrict str, const char * __restrict delim);

char *strtok(char * __restrict str, const char * __restrict delim) {
    // Static variable to keep track of the current position in the string
    static char* current_pos = nullptr;
    
    // If str is not null, start from the beginning of the new string
    if (str != nullptr) {
        current_pos = str;
    }
    
    // If current_pos is null (no string to process), return nullptr
    if (current_pos == nullptr) {
        return nullptr;
    }
    
    // Skip any leading delimiters
    while (*current_pos != '\0') {
        bool is_delim = false;
        for (int i = 0; delim[i] != '\0'; i++) {
            if (*current_pos == delim[i]) {
                is_delim = true;
                break;
            }
        }
        if (!is_delim) {
            break;
        }
        current_pos++;
    }
    
    // If we've reached the end of the string, there are no more tokens
    if (*current_pos == '\0') {
        current_pos = nullptr;
        return nullptr;
    }
    
    // Save the start of the token
    char* token_start = current_pos;
    
    // Find the end of the token (next delimiter or end of string)
    while (*current_pos != '\0') {
        bool is_delim = false;
        for (int i = 0; delim[i] != '\0'; i++) {
            if (*current_pos == delim[i]) {
                is_delim = true;
                break;
            }
        }
        if (is_delim) {
            // Replace delimiter with null terminator
            *current_pos = '\0';
            // Move to the next character for the next call
            current_pos++;
            return token_start;
        }
        current_pos++;
    }
    
    // If we get here, we've reached the end of the string
    // The current token extends to the end of the string
    // current_pos is now pointing to '\0', so next call will return nullptr
    return token_start;
}
