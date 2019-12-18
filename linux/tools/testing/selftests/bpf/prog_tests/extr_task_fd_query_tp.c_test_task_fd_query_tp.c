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
 int /*<<< orphan*/  test_task_fd_query_tp_core (char*,char*) ; 

void test_task_fd_query_tp(void)
{
	test_task_fd_query_tp_core("sched/sched_switch",
				   "sched_switch");
	test_task_fd_query_tp_core("syscalls/sys_enter_read",
				   "sys_enter_read");
}