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
typedef  int int64_t ;
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_contract(felem out, const felem in)
{
    static const int64_t two56 = ((limb) 1) << 56;
    /* 0 <= in < 2*p, p = 2^224 - 2^96 + 1 */
    /* if in > p , reduce in = in - 2^224 + 2^96 - 1 */
    int64_t tmp[4], a;
    tmp[0] = in[0];
    tmp[1] = in[1];
    tmp[2] = in[2];
    tmp[3] = in[3];
    /* Case 1: a = 1 iff in >= 2^224 */
    a = (in[3] >> 56);
    tmp[0] -= a;
    tmp[1] += a << 40;
    tmp[3] &= 0x00ffffffffffffff;
    /*
     * Case 2: a = 0 iff p <= in < 2^224, i.e., the high 128 bits are all 1
     * and the lower part is non-zero
     */
    a = ((in[3] & in[2] & (in[1] | 0x000000ffffffffff)) + 1) |
        (((int64_t) (in[0] + (in[1] & 0x000000ffffffffff)) - 1) >> 63);
    a &= 0x00ffffffffffffff;
    /* turn a into an all-one mask (if a = 0) or an all-zero mask */
    a = (a - 1) >> 63;
    /* subtract 2^224 - 2^96 + 1 if a is all-one */
    tmp[3] &= a ^ 0xffffffffffffffff;
    tmp[2] &= a ^ 0xffffffffffffffff;
    tmp[1] &= (a ^ 0xffffffffffffffff) | 0x000000ffffffffff;
    tmp[0] -= 1 & a;

    /*
     * eliminate negative coefficients: if tmp[0] is negative, tmp[1] must be
     * non-zero, so we only need one step
     */
    a = tmp[0] >> 63;
    tmp[0] += two56 & a;
    tmp[1] -= 1 & a;

    /* carry 1 -> 2 -> 3 */
    tmp[2] += tmp[1] >> 56;
    tmp[1] &= 0x00ffffffffffffff;

    tmp[3] += tmp[2] >> 56;
    tmp[2] &= 0x00ffffffffffffff;

    /* Now 0 <= out < p */
    out[0] = tmp[0];
    out[1] = tmp[1];
    out[2] = tmp[2];
    out[3] = tmp[3];
}