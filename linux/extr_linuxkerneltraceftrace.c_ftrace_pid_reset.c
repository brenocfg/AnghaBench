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
struct trace_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_ftrace_pids (struct trace_array*) ; 
 int /*<<< orphan*/  ftrace_lock ; 
 int /*<<< orphan*/  ftrace_startup_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_update_pid_func () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftrace_pid_reset(struct trace_array *tr)
{
	mutex_lock(&ftrace_lock);
	clear_ftrace_pids(tr);

	ftrace_update_pid_func();
	ftrace_startup_all(0);

	mutex_unlock(&ftrace_lock);
}