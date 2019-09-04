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
struct thread_group_cputimer {int /*<<< orphan*/  running; } ;
struct signal_struct {struct thread_group_cputimer cputimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TICK_DEP_BIT_POSIX_TIMER ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tick_dep_clear_signal (struct signal_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void stop_process_timers(struct signal_struct *sig)
{
	struct thread_group_cputimer *cputimer = &sig->cputimer;

	/* Turn off cputimer->running. This is done without locking. */
	WRITE_ONCE(cputimer->running, false);
	tick_dep_clear_signal(sig, TICK_DEP_BIT_POSIX_TIMER);
}