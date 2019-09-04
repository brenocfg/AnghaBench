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
typedef  size_t T ;

/* Variables and functions */
 int* SB1 ; 
 int* SB2 ; 
 int* SB3 ; 
 int* SB4 ; 
 int* SB5 ; 
 int* SB6 ; 
 int* SB7 ; 
 int* SB8 ; 

__attribute__((used)) static inline uint64_t
ROUND(uint64_t r, uint64_t R, uint64_t seed)
{
#define GETBYTE(R,n) ((uint64_t)(((((R)>>(n*8ULL)))&0xFFULL)))
#if 0    
    uint64_t r0, r1, r2, r3;
#endif
    uint64_t T, Y;

    T = R ^ ((seed>>r) | (seed<<(64-r)));


    if (r & 1) {
        Y = SB8[ (T      ) & 0x3F ] ^              \
             SB6[ (T >>  8) & 0x3F ] ^              \
             SB4[ (T >> 16) & 0x3F ] ^              \
             SB2[ (T >> 24) & 0x3F ];               \
    } else {
        Y = SB7[ (T      ) & 0x3F ] ^              \
             SB5[ (T >>  8) & 0x3F ] ^              \
             SB3[ (T >> 16) & 0x3F ] ^              \
             SB1[ (T >> 24) & 0x3F ]; 
    }
    return Y;
#if 0
    r0 = sbox2[GETBYTE(R,0)]<< 6 | sbox2[GETBYTE(R,1)]<< 0;
    r1 = sbox2[GETBYTE(R,2)]<< 6 | sbox2[GETBYTE(R,5)]<< 0;
    r2 = sbox2[GETBYTE(R,4)]<< 6 | sbox2[GETBYTE(R,5)]<< 0;
    r3 = sbox2[GETBYTE(R,6)]<< 6 | sbox2[GETBYTE(R,7)]<< 0;

    R = r0 ^ (r1<<12) * (r2 << 24) ^ (r3 << 36) * r;

    return R;
    /*return((uint64_t)sbox2[GETBYTE(R,7ULL)]<< 0ULL)
        | ((uint64_t)sbox2[GETBYTE(R,6ULL)]<< 8ULL)
        | ((uint64_t)sbox2[GETBYTE(R,5ULL)]<<16ULL)
        | ((uint64_t)sbox2[GETBYTE(R,4ULL)]<<24ULL)
        | ((uint64_t)sbox2[GETBYTE(R,3ULL)]<<32ULL)
        | ((uint64_t)sbox2[GETBYTE(R,2ULL)]<<40ULL)
        | ((uint64_t)sbox2[GETBYTE(R,1ULL)]<<48ULL)
        | ((uint64_t)sbox2[GETBYTE(R,0ULL)]<<56ULL)
        ;*/
    return R;
#endif
}