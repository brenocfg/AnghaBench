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
 int /*<<< orphan*/  CONSOLE_REPLAY_ALL ; 
 int /*<<< orphan*/  DUMP_ALL ; 
 int PANIC_PRINT_ALL_PRINTK_MSG ; 
 int PANIC_PRINT_FTRACE_INFO ; 
 int PANIC_PRINT_LOCK_INFO ; 
 int PANIC_PRINT_MEM_INFO ; 
 int PANIC_PRINT_TASK_INFO ; 
 int PANIC_PRINT_TIMER_INFO ; 
 int /*<<< orphan*/  console_flush_on_panic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_show_all_locks () ; 
 int /*<<< orphan*/  ftrace_dump (int /*<<< orphan*/ ) ; 
 int panic_print ; 
 int /*<<< orphan*/  show_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_state () ; 
 int /*<<< orphan*/  sysrq_timer_list_show () ; 

__attribute__((used)) static void panic_print_sys_info(void)
{
	if (panic_print & PANIC_PRINT_ALL_PRINTK_MSG)
		console_flush_on_panic(CONSOLE_REPLAY_ALL);

	if (panic_print & PANIC_PRINT_TASK_INFO)
		show_state();

	if (panic_print & PANIC_PRINT_MEM_INFO)
		show_mem(0, NULL);

	if (panic_print & PANIC_PRINT_TIMER_INFO)
		sysrq_timer_list_show();

	if (panic_print & PANIC_PRINT_LOCK_INFO)
		debug_show_all_locks();

	if (panic_print & PANIC_PRINT_FTRACE_INFO)
		ftrace_dump(DUMP_ALL);
}