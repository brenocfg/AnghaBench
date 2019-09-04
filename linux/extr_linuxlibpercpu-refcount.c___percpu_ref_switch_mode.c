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
struct percpu_ref {int percpu_count_ptr; scalar_t__ force_atomic; int /*<<< orphan*/  confirm_switch; } ;
typedef  int /*<<< orphan*/  percpu_ref_func_t ;

/* Variables and functions */
 int __PERCPU_REF_DEAD ; 
 int /*<<< orphan*/  __percpu_ref_switch_to_atomic (struct percpu_ref*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __percpu_ref_switch_to_percpu (struct percpu_ref*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_lock ; 
 int /*<<< orphan*/  percpu_ref_switch_waitq ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __percpu_ref_switch_mode(struct percpu_ref *ref,
				     percpu_ref_func_t *confirm_switch)
{
	lockdep_assert_held(&percpu_ref_switch_lock);

	/*
	 * If the previous ATOMIC switching hasn't finished yet, wait for
	 * its completion.  If the caller ensures that ATOMIC switching
	 * isn't in progress, this function can be called from any context.
	 */
	wait_event_lock_irq(percpu_ref_switch_waitq, !ref->confirm_switch,
			    percpu_ref_switch_lock);

	if (ref->force_atomic || (ref->percpu_count_ptr & __PERCPU_REF_DEAD))
		__percpu_ref_switch_to_atomic(ref, confirm_switch);
	else
		__percpu_ref_switch_to_percpu(ref);
}