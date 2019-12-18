#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct upid {int /*<<< orphan*/  nr; TYPE_1__* ns; } ;
struct task_struct {int dummy; } ;
struct pid {int level; struct upid* numbers; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_mnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_flush_task_mnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pid* task_pid (struct task_struct*) ; 
 struct pid* task_tgid (struct task_struct*) ; 

void proc_flush_task(struct task_struct *task)
{
	int i;
	struct pid *pid, *tgid;
	struct upid *upid;

	pid = task_pid(task);
	tgid = task_tgid(task);

	for (i = 0; i <= pid->level; i++) {
		upid = &pid->numbers[i];
		proc_flush_task_mnt(upid->ns->proc_mnt, upid->nr,
					tgid->numbers[i].nr);
	}
}