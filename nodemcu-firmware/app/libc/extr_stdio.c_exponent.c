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
 int MAX_FCONVERSION ; 
 void* to_char (int) ; 

__attribute__((used)) static char *
exponent(char *p, int exp, int fmtch)
{
    char *t;
    char expbuf[MAX_FCONVERSION];

    *p++ = fmtch;
    if (exp < 0) {
        exp = -exp;
        *p++ = '-';
    }
    else
        *p++ = '+';
    t = expbuf + MAX_FCONVERSION;
    if (exp > 9) {
        do {
            *--t = to_char(exp % 10);
        } while ((exp /= 10) > 9);
        *--t = to_char(exp);
        for (; t < expbuf + MAX_FCONVERSION; *p++ = *t++);
    }
    else {
        *p++ = '0';
        *p++ = to_char(exp);
    }
    return (p);
}