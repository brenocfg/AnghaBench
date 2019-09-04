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
struct trace_pid_list {scalar_t__ pid_max; int /*<<< orphan*/  pids; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

bool
trace_find_filtered_pid(struct trace_pid_list *filtered_pids, pid_t search_pid)
{
	/*
	 * If pid_max changed after filtered_pids was created, we
	 * by default ignore all pids greater than the previous pid_max.
	 */
	if (search_pid >= filtered_pids->pid_max)
		return false;

	return test_bit(search_pid, filtered_pids->pids);
}