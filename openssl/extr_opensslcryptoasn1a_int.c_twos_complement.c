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

__attribute__((used)) static void twos_complement(unsigned char *dst, const unsigned char *src,
                            size_t len, unsigned char pad)
{
    unsigned int carry = pad & 1;

    /* Begin at the end of the encoding */
    dst += len;
    src += len;
    /* two's complement value: ~value + 1 */
    while (len-- != 0) {
        *(--dst) = (unsigned char)(carry += *(--src) ^ pad);
        carry >>= 8;
    }
}