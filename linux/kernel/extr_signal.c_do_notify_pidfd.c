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
struct task_struct {scalar_t__ exit_state; } ;
struct pid {int /*<<< orphan*/  wait_pidfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct pid* task_pid (struct task_struct*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_notify_pidfd(struct task_struct *task)
{
	struct pid *pid;

	WARN_ON(task->exit_state == 0);
	pid = task_pid(task);
	wake_up_all(&pid->wait_pidfd);
}