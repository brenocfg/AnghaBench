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
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_foo_bar_with_fn (char*,int) ; 
 int /*<<< orphan*/  trace_foo_with_template_fn (char*,int) ; 

__attribute__((used)) static void simple_thread_func_fn(int cnt)
{
	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(HZ);

	/* More silly tracepoints */
	trace_foo_bar_with_fn("Look at me", cnt);
	trace_foo_with_template_fn("Look at me too", cnt);
}