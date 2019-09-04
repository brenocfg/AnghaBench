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
struct smpboot_thread_data {unsigned int cpu; struct smp_hotplug_thread* ht; } ;
struct smp_hotplug_thread {int /*<<< orphan*/  (* create ) (unsigned int) ;int /*<<< orphan*/  store; int /*<<< orphan*/  thread_comm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  TASK_PARKED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  kfree (struct smpboot_thread_data*) ; 
 struct task_struct* kthread_create_on_cpu (int /*<<< orphan*/ ,struct smpboot_thread_data*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_park (struct task_struct*) ; 
 struct smpboot_thread_data* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct task_struct** per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smpboot_thread_fn ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  wait_task_inactive (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__smpboot_create_thread(struct smp_hotplug_thread *ht, unsigned int cpu)
{
	struct task_struct *tsk = *per_cpu_ptr(ht->store, cpu);
	struct smpboot_thread_data *td;

	if (tsk)
		return 0;

	td = kzalloc_node(sizeof(*td), GFP_KERNEL, cpu_to_node(cpu));
	if (!td)
		return -ENOMEM;
	td->cpu = cpu;
	td->ht = ht;

	tsk = kthread_create_on_cpu(smpboot_thread_fn, td, cpu,
				    ht->thread_comm);
	if (IS_ERR(tsk)) {
		kfree(td);
		return PTR_ERR(tsk);
	}
	/*
	 * Park the thread so that it could start right on the CPU
	 * when it is available.
	 */
	kthread_park(tsk);
	get_task_struct(tsk);
	*per_cpu_ptr(ht->store, cpu) = tsk;
	if (ht->create) {
		/*
		 * Make sure that the task has actually scheduled out
		 * into park position, before calling the create
		 * callback. At least the migration thread callback
		 * requires that the task is off the runqueue.
		 */
		if (!wait_task_inactive(tsk, TASK_PARKED))
			WARN_ON(1);
		else
			ht->create(cpu);
	}
	return 0;
}