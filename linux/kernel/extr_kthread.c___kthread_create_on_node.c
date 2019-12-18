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
typedef  int /*<<< orphan*/  va_list ;
struct task_struct {int dummy; } ;
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
struct kthread_create_info {int (* threadfn ) (void*) ;int node; struct task_struct* result; int /*<<< orphan*/ * done; int /*<<< orphan*/  list; void* data; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct task_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  SCHED_NORMAL ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  cpu_all_mask ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  kfree (struct kthread_create_info*) ; 
 struct kthread_create_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_create_list ; 
 int /*<<< orphan*/  kthread_create_lock ; 
 int /*<<< orphan*/  kthreadd_task ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_setscheduler_nocheck (struct task_struct*,int /*<<< orphan*/ ,struct sched_param const*) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_task_comm (struct task_struct*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 scalar_t__ xchg (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

struct task_struct *__kthread_create_on_node(int (*threadfn)(void *data),
						    void *data, int node,
						    const char namefmt[],
						    va_list args)
{
	DECLARE_COMPLETION_ONSTACK(done);
	struct task_struct *task;
	struct kthread_create_info *create = kmalloc(sizeof(*create),
						     GFP_KERNEL);

	if (!create)
		return ERR_PTR(-ENOMEM);
	create->threadfn = threadfn;
	create->data = data;
	create->node = node;
	create->done = &done;

	spin_lock(&kthread_create_lock);
	list_add_tail(&create->list, &kthread_create_list);
	spin_unlock(&kthread_create_lock);

	wake_up_process(kthreadd_task);
	/*
	 * Wait for completion in killable state, for I might be chosen by
	 * the OOM killer while kthreadd is trying to allocate memory for
	 * new kernel thread.
	 */
	if (unlikely(wait_for_completion_killable(&done))) {
		/*
		 * If I was SIGKILLed before kthreadd (or new kernel thread)
		 * calls complete(), leave the cleanup of this structure to
		 * that thread.
		 */
		if (xchg(&create->done, NULL))
			return ERR_PTR(-EINTR);
		/*
		 * kthreadd (or new kernel thread) will call complete()
		 * shortly.
		 */
		wait_for_completion(&done);
	}
	task = create->result;
	if (!IS_ERR(task)) {
		static const struct sched_param param = { .sched_priority = 0 };
		char name[TASK_COMM_LEN];

		/*
		 * task is already visible to other tasks, so updating
		 * COMM must be protected.
		 */
		vsnprintf(name, sizeof(name), namefmt, args);
		set_task_comm(task, name);
		/*
		 * root may have changed our (kthreadd's) priority or CPU mask.
		 * The kernel thread should not inherit these properties.
		 */
		sched_setscheduler_nocheck(task, SCHED_NORMAL, &param);
		set_cpus_allowed_ptr(task, cpu_all_mask);
	}
	kfree(create);
	return task;
}