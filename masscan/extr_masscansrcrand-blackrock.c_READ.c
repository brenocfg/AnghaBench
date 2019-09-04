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
typedef  int uint64_t ;

/* Variables and functions */
 int* sbox ; 

__attribute__((used)) static inline uint64_t
READ(uint64_t r, uint64_t R, uint64_t seed)
{
    uint64_t r0, r1, r2, r3;

#define GETBYTE(R,n) ((((R)>>(n*8))^seed^r)&0xFF)

    R ^= (seed << r) ^ (seed >> (64 - r));

    r0 = sbox[GETBYTE(R,0)]<< 0 | sbox[GETBYTE(R,1)]<< 8;
    r1 = (sbox[GETBYTE(R,2)]<<16UL | sbox[GETBYTE(R,3)]<<24UL)&0x0ffffFFFFUL;
    r2 = sbox[GETBYTE(R,4)]<< 0 | sbox[GETBYTE(R,5)]<< 8;
    r3 = (sbox[GETBYTE(R,6)]<<16UL | sbox[GETBYTE(R,7)]<<24UL)&0x0ffffFFFFUL;

    R = r0 ^ r1 ^ r2<<23UL ^ r3<<33UL;

    return R;
}