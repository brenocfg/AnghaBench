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
typedef  int sparsebit_num_t ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sparsebit_is_clear (struct sparsebit*,int) ; 
 scalar_t__ sparsebit_is_clear_num (struct sparsebit*,int,int) ; 
 int sparsebit_next_clear (struct sparsebit*,int) ; 
 int sparsebit_next_set (struct sparsebit*,int) ; 

sparsebit_idx_t sparsebit_next_clear_num(struct sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
{
	sparsebit_idx_t idx;

	assert(num >= 1);

	for (idx = sparsebit_next_clear(s, start);
		idx != 0 && idx + num - 1 >= idx;
		idx = sparsebit_next_clear(s, idx)) {
		assert(sparsebit_is_clear(s, idx));

		/*
		 * Does the sequence of bits starting at idx consist of
		 * num cleared bits?
		 */
		if (sparsebit_is_clear_num(s, idx, num))
			return idx;

		/*
		 * Sequence of cleared bits at idx isn't large enough.
		 * Skip this entire sequence of cleared bits.
		 */
		idx = sparsebit_next_set(s, idx);
		if (idx == 0)
			return 0;
	}

	return 0;
}