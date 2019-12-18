#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cycles; } ;
struct hist_entry {TYPE_1__ diff; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int hist_entry__has_pairs (struct hist_entry*) ; 
 scalar_t__ labs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t block_cycles_diff_cmp(struct hist_entry *left,
				     struct hist_entry *right)
{
	bool pairs_left  = hist_entry__has_pairs(left);
	bool pairs_right = hist_entry__has_pairs(right);
	s64 l, r;

	if (!pairs_left && !pairs_right)
		return 0;

	l = labs(left->diff.cycles);
	r = labs(right->diff.cycles);
	return r - l;
}