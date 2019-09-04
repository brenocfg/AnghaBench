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
 int ROUND (unsigned int,int,int) ; 
 int /*<<< orphan*/  UNUSEDPARM (int) ; 

__attribute__((used)) static inline uint64_t
ENCRYPT(unsigned r, uint64_t a_bits, uint64_t a_mask, uint64_t b_bits, uint64_t b_mask, uint64_t m, uint64_t seed)
{
    uint64_t L, R;
    unsigned j = 1;
    uint64_t tmp;

    UNUSEDPARM(b_bits);

    L = m & a_mask;
    R = m >> a_bits;

    for (j=1; j<=r; j++) {
        tmp = (L + ROUND(j, R, seed)) & a_mask;
        L = R;
        R = tmp;
        j++;

        tmp = (L + ROUND(j, R, seed)) & b_mask;
        L = R;
        R = tmp;
    }

    if ((j-1) & 1) {
        return (L << (a_bits)) + R;
    } else {
        return (R << (a_bits)) + L;
    }
}