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
struct kthread_worker {unsigned int flags; struct task_struct* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct kthread_worker* ERR_CAST (struct task_struct*) ; 
 struct kthread_worker* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int NUMA_NO_NODE ; 
 struct task_struct* __kthread_create_on_node (int /*<<< orphan*/ ,struct kthread_worker*,int,char const*,int /*<<< orphan*/ ) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  kfree (struct kthread_worker*) ; 
 int /*<<< orphan*/  kthread_bind (struct task_struct*,int) ; 
 int /*<<< orphan*/  kthread_init_worker (struct kthread_worker*) ; 
 int /*<<< orphan*/  kthread_worker_fn ; 
 struct kthread_worker* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

struct kthread_worker *
__kthread_create_worker(int cpu, unsigned int flags,
			const char namefmt[], va_list args)
{
	struct kthread_worker *worker;
	struct task_struct *task;
	int node = NUMA_NO_NODE;

	worker = kzalloc(sizeof(*worker), GFP_KERNEL);
	if (!worker)
		return ERR_PTR(-ENOMEM);

	kthread_init_worker(worker);

	if (cpu >= 0)
		node = cpu_to_node(cpu);

	task = __kthread_create_on_node(kthread_worker_fn, worker,
						node, namefmt, args);
	if (IS_ERR(task))
		goto fail_task;

	if (cpu >= 0)
		kthread_bind(task, cpu);

	worker->flags = flags;
	worker->task = task;
	wake_up_process(task);
	return worker;

fail_task:
	kfree(worker);
	return ERR_CAST(task);
}