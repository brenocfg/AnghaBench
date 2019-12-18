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
 int /*<<< orphan*/  mb_clear_bit (int,void*) ; 
 int /*<<< orphan*/  mb_set_bit (int,void*) ; 
 scalar_t__ mb_test_bit (int,void*) ; 

__attribute__((used)) static inline int mb_buddy_adjust_border(int* bit, void* bitmap, int side)
{
	if (mb_test_bit(*bit + side, bitmap)) {
		mb_clear_bit(*bit, bitmap);
		(*bit) -= side;
		return 1;
	}
	else {
		(*bit) += side;
		mb_set_bit(*bit, bitmap);
		return -1;
	}
}