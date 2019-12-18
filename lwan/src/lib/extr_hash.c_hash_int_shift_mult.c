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
 unsigned int odd_constant ; 

__attribute__((used)) static inline unsigned int hash_int_shift_mult(const void *keyptr)
{
    /* http://www.concentric.net/~Ttwang/tech/inthash.htm */
    unsigned int key = (unsigned int)(long)keyptr;
    unsigned int c2 = odd_constant;

    key = (key ^ 61) ^ (key >> 16);
    key += key << 3;
    key ^= key >> 4;
    key *= c2;
    key ^= key >> 15;
    return key;
}