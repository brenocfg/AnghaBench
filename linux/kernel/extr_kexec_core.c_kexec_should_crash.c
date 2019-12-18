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
struct task_struct {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 scalar_t__ crash_kexec_post_notifiers ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ is_global_init (struct task_struct*) ; 
 scalar_t__ panic_on_oops ; 

int kexec_should_crash(struct task_struct *p)
{
	/*
	 * If crash_kexec_post_notifiers is enabled, don't run
	 * crash_kexec() here yet, which must be run after panic
	 * notifiers in panic().
	 */
	if (crash_kexec_post_notifiers)
		return 0;
	/*
	 * There are 4 panic() calls in do_exit() path, each of which
	 * corresponds to each of these 4 conditions.
	 */
	if (in_interrupt() || !p->pid || is_global_init(p) || panic_on_oops)
		return 1;
	return 0;
}