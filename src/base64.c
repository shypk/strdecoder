#include "base64.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ER 255


bool base64_decode_0(const char* encoded, char* decoded ) {
                                //0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    const char maptbl[256] = {  
                                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62,  0,  0,  0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,
                                 0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,  0,  0,  0,  0,
                                 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,  0,  0,  0,  0,  0,
                                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
                            };
                            
    int len = strlen(encoded);

    size_t padding = 0;
    if ( len == 0) return true;
    if ( len >= 1 && encoded[len - 1] == '=') padding++;
    if ( len >= 2 && encoded[len - 2] == '=') padding++;

    int i = 0;
    int j = 0;    
    for ( i = 0; i < len-4; i += 4) {
        unsigned int val = (maptbl[(int)encoded[i]] << 18) |
                           (maptbl[(int)encoded[i+1]] << 12) |
                           (maptbl[(int)encoded[i+2]] << 6) |
                           maptbl[(int)encoded[i+3]];
        decoded[j++] = (val >> 16) & 0xFF;
        decoded[j++] = (val >> 8) & 0xFF;
        decoded[j++] = val & 0xFF;
    }

    // rest
    {
        unsigned int val = 0;
        if ( i < len )  val |= (maptbl[(int)encoded[i]] << 18);
        if ( i+1 < len )  val |= (maptbl[(int)encoded[i+1]] << 12);
        if ( i+2 < len )  val |= (maptbl[(int)encoded[i+2]] << 6);
        if ( i+3 < len )  val |= (maptbl[(int)encoded[i+3]] );
        
        if( val != 0 ) {
            decoded[j++] = (val >> 16) & 0xFF;
            if (padding < 2) decoded[j++] = (val >> 8) & 0xFF;
            if (padding < 1) decoded[j++] = val & 0xFF;
        }
    }
    
    decoded[j] = '\0';
    return true;
}


bool base64_decode_1(const char* encoded, char* decoded ) {
                                //0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
    const unsigned char maptbl[256] = {  
           		        ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,
                                ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, 62, ER, ER, ER, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, ER, ER, ER, ER, ER, ER,
                                ER, ER,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, ER, ER, ER, ER, ER,
                                ER, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, ER, ER, ER,  0, ER,
                                ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,
                                ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,
                                ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER,
                                ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER, ER
			    };
                            
    int len = strlen(encoded);

    size_t padding = 0;
    if ( len == 0) return true;
    if ( len >= 1 && encoded[len - 1] == '=') padding++;
    if ( len >= 2 && encoded[len - 2] == '=') padding++;

    int i = 0;
    int j = 0;    
    for ( i = 0; i < len-4; i += 4) {
        unsigned int a = maptbl[(int)encoded[i]];
        unsigned int b = maptbl[(int)encoded[i+1]];
        unsigned int c = maptbl[(int)encoded[i+2]];
        unsigned int d = maptbl[(int)encoded[i+3]];
        if (a == ER || b == ER || c == ER || d == ER) {
            return false;
        }
        unsigned int val = (a << 18) | (b << 12) | (c << 6) | d;
        
        decoded[j++] = (val >> 16) & 0xFF;
        decoded[j++] = (val >> 8) & 0xFF;
        decoded[j++] = val & 0xFF;
    }

    // rest
    {
        unsigned int val = 0;
        if ( i < len ){
            if (maptbl[(int)encoded[i]] == ER) return false;
            val |= (maptbl[(int)encoded[i]] << 18);
        }
        if ( i+1 < len ){
            if (maptbl[(int)encoded[i+1]] == ER) return false;
            val |= (maptbl[(int)encoded[i+1]] << 12); 
        } 
        if ( i+2 < len ){
            if (maptbl[(int)encoded[i+2]] == ER) return false;
            val |= (maptbl[(int)encoded[i+2]] << 6);
        }  
        if ( i+3 < len ){
            if (maptbl[(int)encoded[i+3]] == ER) return false;
            val |= (maptbl[(int)encoded[i+3]] );
        }

        if( val != 0 ) {
            decoded[j++] = (val >> 16) & 0xFF;
            if (padding < 2) decoded[j++] = (val >> 8) & 0xFF;
            if (padding < 1) decoded[j++] = val & 0xFF;
        }
    }
    
    decoded[j] = '\0';
    return true;
}


bool base64_decode(const char* encoded, char* decoded ) {
    return base64_decode_0(encoded, decoded);
}


bool base64_decode_safe(const char* encoded, char* decoded ) {
    return base64_decode_1(encoded, decoded);
}
