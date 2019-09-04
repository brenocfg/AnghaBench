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
struct taskstats {int dummy; } ;
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  fill_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct taskstats*) ; 
 struct task_struct* find_get_task_by_vpid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_stats_for_pid(pid_t pid, struct taskstats *stats)
{
	struct task_struct *tsk;

	tsk = find_get_task_by_vpid(pid);
	if (!tsk)
		return -ESRCH;
	fill_stats(current_user_ns(), task_active_pid_ns(current), tsk, stats);
	put_task_struct(tsk);
	return 0;
}