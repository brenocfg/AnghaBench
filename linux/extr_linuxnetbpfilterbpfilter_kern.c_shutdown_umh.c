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
struct umh_info {scalar_t__ pid; int /*<<< orphan*/  pipe_from_umh; int /*<<< orphan*/  pipe_to_umh; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  find_vpid (scalar_t__) ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static void shutdown_umh(struct umh_info *info)
{
	struct task_struct *tsk;

	if (!info->pid)
		return;
	tsk = get_pid_task(find_vpid(info->pid), PIDTYPE_PID);
	if (tsk) {
		force_sig(SIGKILL, tsk);
		put_task_struct(tsk);
	}
	fput(info->pipe_to_umh);
	fput(info->pipe_from_umh);
	info->pid = 0;
}