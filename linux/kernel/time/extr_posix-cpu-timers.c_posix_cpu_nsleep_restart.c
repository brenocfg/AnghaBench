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
struct timespec64 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  clockid; } ;
struct restart_block {TYPE_1__ nanosleep; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 long do_cpu_nanosleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec64*) ; 
 struct timespec64 ns_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long posix_cpu_nsleep_restart(struct restart_block *restart_block)
{
	clockid_t which_clock = restart_block->nanosleep.clockid;
	struct timespec64 t;

	t = ns_to_timespec64(restart_block->nanosleep.expires);

	return do_cpu_nanosleep(which_clock, TIMER_ABSTIME, &t);
}