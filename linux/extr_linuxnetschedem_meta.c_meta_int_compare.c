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
struct meta_obj {scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int meta_int_compare(struct meta_obj *a, struct meta_obj *b)
{
	/* Let gcc optimize it, the unlikely is not really based on
	 * some numbers but jump free code for mismatches seems
	 * more logical. */
	if (unlikely(a->value == b->value))
		return 0;
	else if (a->value < b->value)
		return -1;
	else
		return 1;
}