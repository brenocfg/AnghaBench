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
 int HASH1 ; 
 int HASH2 ; 
 int HASHSZ ; 

__attribute__((used)) static unsigned int hashnum(unsigned int num)
{
	unsigned int mask1 = HASH1 << 27, mask2 = HASH2 << 27;

	for (; mask1 >= HASH1; mask1 >>= 1, mask2 >>= 1)
		if (num & mask1)
			num ^= mask2;
	return num & (HASHSZ-1);
}