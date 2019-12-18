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
 scalar_t__ IS_UTF8_BYTE (char) ; 
 scalar_t__ isprint (char) ; 
 scalar_t__ likely (char) ; 
 scalar_t__ unlikely (int) ; 
 char url_decode_multibyte_utf8 (char*,char*,char*) ; 
 char url_percent_escape_decode (char*) ; 
 int utf8_check (unsigned char*) ; 

char *url_decode_r(char *to, char *url, size_t size) {
    char *s = url,           // source
         *d = to,            // destination
         *e = &to[size - 1]; // destination end

    while(*s && d < e) {
        if(unlikely(*s == '%')) {
            char t = url_percent_escape_decode(s);
            if(IS_UTF8_BYTE(t)) {
                char bytes_written = url_decode_multibyte_utf8(s, d, e);
                if(likely(bytes_written)){
                    d += bytes_written;
                    s += (bytes_written * 3)-1;
                }
                else {
                    goto fail_cleanup;
                }
            }
            else if(likely(t) && isprint(t)) {
                // avoid HTTP header injection
                *d++ = t;
                s += 2;
            }
            else
                goto fail_cleanup;
        }
        else if(unlikely(*s == '+'))
            *d++ = ' ';

        else
            *d++ = *s;

        s++;
    }

    *d = '\0';

    if(unlikely( utf8_check((unsigned  char *)to) )) //NULL means sucess here
        return NULL;

    return to;

fail_cleanup:
    *d = '\0';
    return NULL;
}