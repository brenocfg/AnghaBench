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
typedef  long long u_quad_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

char *
llbtoa(char *dst, u_quad_t value, int base)
{
    char buf[66], digit;
    int i, j, rem, neg;

    if (value == 0) {
        dst[0] = '0';
        dst[1] = 0;
        return (dst);
    }

    neg = 0;
    if (base == -10) {
        base = 10;
        if (value & (1LL << 63)) {
            value = (~value) + 1;
            neg = 1;
        }
    }

    for (i = 0; value != 0; i++) {
        rem = value % base;
        value /= base;
        if (rem >= 0 && rem <= 9)
            digit = rem + '0';
        else if (rem >= 10 && rem <= 36)
            digit = (rem - 10) + 'a';
        buf[i] = digit;
    }

    buf[i] = 0;
    if (neg)
        strcat (buf, "-");

    /* reverse the string */
    for (i = 0, j = strlen (buf) - 1; j >= 0; i++, j--)
        dst[i] = buf[j];
    dst[i] = 0;
    return (dst);
}