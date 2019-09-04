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
typedef  int limb ;
typedef  int /*<<< orphan*/ * largefelem ;
typedef  int const* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_diff_128_64(largefelem out, const felem in)
{
    /*
     * In order to prevent underflow, we add 64p mod p (which is equivalent
     * to 0 mod p) before subtracting. p is 2^521 - 1, i.e. in binary a 521
     * digit number with all bits set to 1. See "The representation of field
     * elements" comment above for a description of how limbs are used to
     * represent a number. 64p is represented with 8 limbs containing a number
     * with 58 bits set and one limb with a number with 57 bits set.
     */
    static const limb two63m6 = (((limb) 1) << 63) - (((limb) 1) << 6);
    static const limb two63m5 = (((limb) 1) << 63) - (((limb) 1) << 5);

    out[0] += two63m6 - in[0];
    out[1] += two63m5 - in[1];
    out[2] += two63m5 - in[2];
    out[3] += two63m5 - in[3];
    out[4] += two63m5 - in[4];
    out[5] += two63m5 - in[5];
    out[6] += two63m5 - in[6];
    out[7] += two63m5 - in[7];
    out[8] += two63m5 - in[8];
}