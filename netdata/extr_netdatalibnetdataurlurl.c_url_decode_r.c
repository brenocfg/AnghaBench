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
 int from_hex (char) ; 
 scalar_t__ isprint (char) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

char *url_decode_r(char *to, char *url, size_t size) {
    char *s = url,           // source
         *d = to,            // destination
         *e = &to[size - 1]; // destination end

    while(*s && d < e) {
        if(unlikely(*s == '%')) {
            if(likely(s[1] && s[2])) {
                char t = from_hex(s[1]) << 4 | from_hex(s[2]);
                // avoid HTTP header injection
                *d++ = (char)((isprint(t))? t : ' ');
                s += 2;
            }
        }
        else if(unlikely(*s == '+'))
            *d++ = ' ';

        else
            *d++ = *s;

        s++;
    }

    *d = '\0';

    return to;
}