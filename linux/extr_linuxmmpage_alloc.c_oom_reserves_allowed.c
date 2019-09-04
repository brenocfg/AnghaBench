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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MMU ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsk_is_oom_victim (struct task_struct*) ; 

__attribute__((used)) static bool oom_reserves_allowed(struct task_struct *tsk)
{
	if (!tsk_is_oom_victim(tsk))
		return false;

	/*
	 * !MMU doesn't have oom reaper so give access to memory reserves
	 * only to the thread with TIF_MEMDIE set
	 */
	if (!IS_ENABLED(CONFIG_MMU) && !test_thread_flag(TIF_MEMDIE))
		return false;

	return true;
}