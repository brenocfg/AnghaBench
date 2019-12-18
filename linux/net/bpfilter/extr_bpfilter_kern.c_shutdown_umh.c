#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {TYPE_1__ info; scalar_t__ stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  SIGKILL ; 
 TYPE_2__ bpfilter_ops ; 
 int /*<<< orphan*/  find_vpid (int /*<<< orphan*/ ) ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,struct task_struct*,int) ; 

__attribute__((used)) static void shutdown_umh(void)
{
	struct task_struct *tsk;

	if (bpfilter_ops.stop)
		return;

	tsk = get_pid_task(find_vpid(bpfilter_ops.info.pid), PIDTYPE_PID);
	if (tsk) {
		send_sig(SIGKILL, tsk, 1);
		put_task_struct(tsk);
	}
}