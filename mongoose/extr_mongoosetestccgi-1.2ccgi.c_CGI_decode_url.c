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
 int hex (char const) ; 
 scalar_t__ mymalloc (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

char *
CGI_decode_url(const char *p) {
    char *out;
    int i, k, L, R;

    if (p == 0) {
        return 0;
    }
    out = (char *) mymalloc(strlen(p) + 1);
    for (i = k = 0; p[i] != 0; i++) {
        switch(p[i]) {

        case '+':
            out[k++] = ' ';
            continue;

        case '%':
            if ((L = hex(p[i + 1])) >= 0 &&
                (R = hex(p[i + 2])) >= 0)
            {
                out[k++] = (L << 4) + R;
                i += 2;
                continue;
            }
            break;
        }
        out[k++] = p[i];
    }
    out[k] = 0;
    return out;
}