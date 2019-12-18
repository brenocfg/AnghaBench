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
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __unbuffered_tpr_y ; 
 int /*<<< orphan*/  might_sleep () ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

void rcu_reader(void)
{
	int idx;

#ifndef FORCE_FAILURE_3
	idx = srcu_read_lock(&ss);
#endif
	might_sleep();

	__unbuffered_tpr_y = READ_ONCE(y);
#ifdef FORCE_FAILURE
	srcu_read_unlock(&ss, idx);
	idx = srcu_read_lock(&ss);
#endif
	WRITE_ONCE(x, 1);

#ifndef FORCE_FAILURE_3
	srcu_read_unlock(&ss, idx);
#endif
	might_sleep();
}