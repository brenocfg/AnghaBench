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

void ec_GFp_nistp_recode_scalar_bits(unsigned char *sign,
                                     unsigned char *digit, unsigned char in)
{
    unsigned char s, d;

    s = ~((in >> 5) - 1);       /* sets all bits to MSB(in), 'in' seen as
                                 * 6-bit value */
    d = (1 << 6) - in - 1;
    d = (d & s) | (in & ~s);
    d = (d >> 1) + (d & 1);

    *sign = s & 1;
    *digit = d;
}