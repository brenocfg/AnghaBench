#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  IS_UTF8_BYTE (char) ; 
 scalar_t__ IS_UTF8_STARTBYTE (char) ; 
 scalar_t__ unlikely (int) ; 
 char url_percent_escape_decode (char*) ; 
 char url_utf8_get_byte_length (char) ; 

char url_decode_multibyte_utf8(char *s, char *d, char *d_end) {
    char first_byte = url_percent_escape_decode(s);

    if(unlikely(!first_byte || !IS_UTF8_STARTBYTE(first_byte)))
        return 0;

    char byte_length = url_utf8_get_byte_length(first_byte);

    if(unlikely(byte_length <= 0 || d+byte_length >= d_end))
        return 0;

    char to_read = byte_length;
    while(to_read > 0) {
        char c = url_percent_escape_decode(s);

        if(unlikely( !IS_UTF8_BYTE(c) ))
            return 0;
        if((to_read != byte_length) && IS_UTF8_STARTBYTE(c)) 
            return 0;

        *d++ = c;
        s+=3;
        to_read--;
    }

    return byte_length;
}