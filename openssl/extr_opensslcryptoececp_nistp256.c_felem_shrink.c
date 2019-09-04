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
typedef  int u64 ;
typedef  int* smallfelem ;
typedef  int limb ;
typedef  int* felem ;

/* Variables and functions */
 int bottom63bits ; 
 int* kPrime ; 
 int* zero110 ; 

__attribute__((used)) static void felem_shrink(smallfelem out, const felem in)
{
    felem tmp;
    u64 a, b, mask;
    u64 high, low;
    static const u64 kPrime3Test = 0x7fffffff00000001ul; /* 2^63 - 2^32 + 1 */

    /* Carry 2->3 */
    tmp[3] = zero110[3] + in[3] + ((u64)(in[2] >> 64));
    /* tmp[3] < 2^110 */

    tmp[2] = zero110[2] + (u64)in[2];
    tmp[0] = zero110[0] + in[0];
    tmp[1] = zero110[1] + in[1];
    /* tmp[0] < 2**110, tmp[1] < 2^111, tmp[2] < 2**65 */

    /*
     * We perform two partial reductions where we eliminate the high-word of
     * tmp[3]. We don't update the other words till the end.
     */
    a = tmp[3] >> 64;           /* a < 2^46 */
    tmp[3] = (u64)tmp[3];
    tmp[3] -= a;
    tmp[3] += ((limb) a) << 32;
    /* tmp[3] < 2^79 */

    b = a;
    a = tmp[3] >> 64;           /* a < 2^15 */
    b += a;                     /* b < 2^46 + 2^15 < 2^47 */
    tmp[3] = (u64)tmp[3];
    tmp[3] -= a;
    tmp[3] += ((limb) a) << 32;
    /* tmp[3] < 2^64 + 2^47 */

    /*
     * This adjusts the other two words to complete the two partial
     * reductions.
     */
    tmp[0] += b;
    tmp[1] -= (((limb) b) << 32);

    /*
     * In order to make space in tmp[3] for the carry from 2 -> 3, we
     * conditionally subtract kPrime if tmp[3] is large enough.
     */
    high = (u64)(tmp[3] >> 64);
    /* As tmp[3] < 2^65, high is either 1 or 0 */
    high = 0 - high;
    /*-
     * high is:
     *   all ones   if the high word of tmp[3] is 1
     *   all zeros  if the high word of tmp[3] if 0
     */
    low = (u64)tmp[3];
    mask = 0 - (low >> 63);
    /*-
     * mask is:
     *   all ones   if the MSB of low is 1
     *   all zeros  if the MSB of low if 0
     */
    low &= bottom63bits;
    low -= kPrime3Test;
    /* if low was greater than kPrime3Test then the MSB is zero */
    low = ~low;
    low = 0 - (low >> 63);
    /*-
     * low is:
     *   all ones   if low was > kPrime3Test
     *   all zeros  if low was <= kPrime3Test
     */
    mask = (mask & low) | high;
    tmp[0] -= mask & kPrime[0];
    tmp[1] -= mask & kPrime[1];
    /* kPrime[2] is zero, so omitted */
    tmp[3] -= mask & kPrime[3];
    /* tmp[3] < 2**64 - 2**32 + 1 */

    tmp[1] += ((u64)(tmp[0] >> 64));
    tmp[0] = (u64)tmp[0];
    tmp[2] += ((u64)(tmp[1] >> 64));
    tmp[1] = (u64)tmp[1];
    tmp[3] += ((u64)(tmp[2] >> 64));
    tmp[2] = (u64)tmp[2];
    /* tmp[i] < 2^64 */

    out[0] = tmp[0];
    out[1] = tmp[1];
    out[2] = tmp[2];
    out[3] = tmp[3];
}