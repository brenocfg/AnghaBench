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

__attribute__((used)) static size_t
next_pow2(size_t n)
{
    size_t bit_count = 0;
    
    /* Always have at least one bit */
    if (n == 0)
        return 1;
    
    /* If already a power-of-two, then return that */
    if ((n & (n - 1)) == 0)
        return n;
    
    /* Count the nubmer of bits */
    while (n != 0) {
        n >>= 1;
        bit_count += 1;
    }
    
    return 1 << bit_count;
}