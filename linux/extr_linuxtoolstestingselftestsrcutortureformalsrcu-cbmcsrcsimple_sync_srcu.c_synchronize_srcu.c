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
struct srcu_struct {int completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  assume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  srcu_flip (struct srcu_struct*) ; 
 int /*<<< orphan*/  try_check_zero (struct srcu_struct*,int,int const) ; 

void synchronize_srcu(struct srcu_struct *sp)
{
	int idx;
	/*
	 * This code assumes that try_check_zero will succeed anyway,
	 * so there is no point in multiple tries.
	 */
	const int trycount = 1;

	might_sleep();

	/* Ignore the lock, as multiple writers aren't working yet anyway. */

	idx = 1 ^ (sp->completed & 1);

	/* For comments see srcu_advance_batches. */

	assume(try_check_zero(sp, idx, trycount));

	srcu_flip(sp);

	assume(try_check_zero(sp, idx^1, trycount));
}