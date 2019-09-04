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
 scalar_t__ VERDANA_KERNING ; 
 scalar_t__ VERDANA_PADDING ; 
 double* verdana11_widths ; 

__attribute__((used)) static inline double verdana11_width(char *s) {
    double w = 0.0;
    char *d = s;

    while(*s) {
        double t = verdana11_widths[(unsigned char)*s];
        if(t == 0.0)
            s++;
        else {
            w += t + VERDANA_KERNING;
            if(d != s)
                *d++ = *s++;
            else
                d = ++s;
        }
    }

    *d = '\0';
    w -= VERDANA_KERNING;
    w += VERDANA_PADDING;
    return w;
}