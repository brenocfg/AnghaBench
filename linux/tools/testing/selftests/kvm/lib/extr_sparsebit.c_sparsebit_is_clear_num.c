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
struct sparsebit {int dummy; } ;
typedef  scalar_t__ sparsebit_num_t ;
typedef  scalar_t__ sparsebit_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sparsebit_is_clear (struct sparsebit*,scalar_t__) ; 
 scalar_t__ sparsebit_next_set (struct sparsebit*,scalar_t__) ; 

bool sparsebit_is_clear_num(struct sparsebit *s,
	sparsebit_idx_t idx, sparsebit_num_t num)
{
	sparsebit_idx_t next_set;

	assert(num > 0);
	assert(idx + num - 1 >= idx);

	/* With num > 0, the first bit must be cleared. */
	if (!sparsebit_is_clear(s, idx))
		return false;

	/* Find the next set bit */
	next_set = sparsebit_next_set(s, idx);

	/*
	 * If no set bits beyond idx, then there are at least num
	 * cleared bits. idx + num doesn't wrap.  Otherwise check if
	 * there are enough cleared bits between idx and the next set bit.
	 */
	return next_set == 0 || next_set - idx >= num;
}