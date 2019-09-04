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
 int EAGAIN ; 
 int find_first_zero_bit (unsigned long*,unsigned long) ; 
 scalar_t__ test_and_set_bit (int,unsigned long*) ; 

__attribute__((used)) static int arm_ccn_pmu_alloc_bit(unsigned long *bitmap, unsigned long size)
{
	int bit;

	do {
		bit = find_first_zero_bit(bitmap, size);
		if (bit >= size)
			return -EAGAIN;
	} while (test_and_set_bit(bit, bitmap));

	return bit;
}