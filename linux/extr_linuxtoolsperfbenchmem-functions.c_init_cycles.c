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
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  cycle_attr ; 
 scalar_t__ cycles_fd ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  perf_event_open_cloexec_flag () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ sys_perf_event_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_cycles(void)
{
	cycles_fd = sys_perf_event_open(&cycle_attr, getpid(), -1, -1, perf_event_open_cloexec_flag());

	if (cycles_fd < 0 && errno == ENOSYS) {
		pr_debug("No CONFIG_PERF_EVENTS=y kernel support configured?\n");
		return -1;
	}

	return cycles_fd;
}