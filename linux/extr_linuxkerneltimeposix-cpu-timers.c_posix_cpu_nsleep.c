#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  clockid; } ;
struct restart_block {TYPE_1__ nanosleep; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  clockid_t ;
struct TYPE_5__ {struct restart_block restart_block; } ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/  const) ; 
 scalar_t__ CPUCLOCK_PID (int /*<<< orphan*/  const) ; 
 int EINVAL ; 
 int ERESTARTNOHAND ; 
 int ERESTART_RESTARTBLOCK ; 
 int TIMER_ABSTIME ; 
 TYPE_2__* current ; 
 int do_cpu_nanosleep (int /*<<< orphan*/  const,int,struct timespec64 const*) ; 
 int /*<<< orphan*/  posix_cpu_nsleep_restart ; 
 scalar_t__ task_pid_vnr (TYPE_2__*) ; 

__attribute__((used)) static int posix_cpu_nsleep(const clockid_t which_clock, int flags,
			    const struct timespec64 *rqtp)
{
	struct restart_block *restart_block = &current->restart_block;
	int error;

	/*
	 * Diagnose required errors first.
	 */
	if (CPUCLOCK_PERTHREAD(which_clock) &&
	    (CPUCLOCK_PID(which_clock) == 0 ||
	     CPUCLOCK_PID(which_clock) == task_pid_vnr(current)))
		return -EINVAL;

	error = do_cpu_nanosleep(which_clock, flags, rqtp);

	if (error == -ERESTART_RESTARTBLOCK) {

		if (flags & TIMER_ABSTIME)
			return -ERESTARTNOHAND;

		restart_block->fn = posix_cpu_nsleep_restart;
		restart_block->nanosleep.clockid = which_clock;
	}
	return error;
}