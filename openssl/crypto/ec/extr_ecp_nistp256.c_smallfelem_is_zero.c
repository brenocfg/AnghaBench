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

/* Variables and functions */
 int* kPrime ; 

__attribute__((used)) static limb smallfelem_is_zero(const smallfelem small)
{
    limb result;
    u64 is_p;

    u64 is_zero = small[0] | small[1] | small[2] | small[3];
    is_zero--;
    is_zero &= is_zero << 32;
    is_zero &= is_zero << 16;
    is_zero &= is_zero << 8;
    is_zero &= is_zero << 4;
    is_zero &= is_zero << 2;
    is_zero &= is_zero << 1;
    is_zero = 0 - (is_zero >> 63);

    is_p = (small[0] ^ kPrime[0]) |
        (small[1] ^ kPrime[1]) |
        (small[2] ^ kPrime[2]) | (small[3] ^ kPrime[3]);
    is_p--;
    is_p &= is_p << 32;
    is_p &= is_p << 16;
    is_p &= is_p << 8;
    is_p &= is_p << 4;
    is_p &= is_p << 2;
    is_p &= is_p << 1;
    is_p = 0 - (is_p >> 63);

    is_zero |= is_p;

    result = is_zero;
    result |= ((limb) is_zero) << 64;
    return result;
}