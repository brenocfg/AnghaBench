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
struct srcu_struct {int* srcu_lock_nesting; int /*<<< orphan*/  srcu_wq; int /*<<< orphan*/  srcu_gp_waiting; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int /*<<< orphan*/  swake_up_one (int /*<<< orphan*/ *) ; 

void __srcu_read_unlock(struct srcu_struct *ssp, int idx)
{
	int newval = ssp->srcu_lock_nesting[idx] - 1;

	WRITE_ONCE(ssp->srcu_lock_nesting[idx], newval);
	if (!newval && READ_ONCE(ssp->srcu_gp_waiting))
		swake_up_one(&ssp->srcu_wq);
}