#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; int /*<<< orphan*/  alloc_lock; } ;
struct access_report_info {char const* access; int /*<<< orphan*/  work; struct task_struct* agent; struct task_struct* target; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  __report_access ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_task_comm (char*,struct task_struct*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  init_task_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct access_report_info*) ; 
 struct access_report_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice_ratelimited (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 scalar_t__ task_work_add (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void report_access(const char *access, struct task_struct *target,
				struct task_struct *agent)
{
	struct access_report_info *info;
	char agent_comm[sizeof(agent->comm)];

	assert_spin_locked(&target->alloc_lock); /* for target->comm */

	if (current->flags & PF_KTHREAD) {
		/* I don't think kthreads call task_work_run() before exiting.
		 * Imagine angry ranting about procfs here.
		 */
		pr_notice_ratelimited(
		    "ptrace %s of \"%s\"[%d] was attempted by \"%s\"[%d]\n",
		    access, target->comm, target->pid,
		    get_task_comm(agent_comm, agent), agent->pid);
		return;
	}

	info = kmalloc(sizeof(*info), GFP_ATOMIC);
	if (!info)
		return;
	init_task_work(&info->work, __report_access);
	get_task_struct(target);
	get_task_struct(agent);
	info->access = access;
	info->target = target;
	info->agent = agent;
	if (task_work_add(current, &info->work, true) == 0)
		return; /* success */

	WARN(1, "report_access called from exiting task");
	put_task_struct(target);
	put_task_struct(agent);
	kfree(info);
}