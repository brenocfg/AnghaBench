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

__attribute__((used)) static void make_kn(unsigned char *k1, const unsigned char *l, int bl)
{
    int i;
    unsigned char c = l[0], carry = c >> 7, cnext;

    /* Shift block to left, including carry */
    for (i = 0; i < bl - 1; i++, c = cnext)
        k1[i] = (c << 1) | ((cnext = l[i + 1]) >> 7);

    /* If MSB set fixup with R */
    k1[i] = (c << 1) ^ ((0 - carry) & (bl == 16 ? 0x87 : 0x1b));
}