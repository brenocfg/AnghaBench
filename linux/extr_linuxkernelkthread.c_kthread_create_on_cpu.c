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
struct task_struct {int dummy; } ;
struct TYPE_2__ {unsigned int cpu; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  KTHREAD_IS_PER_CPU ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 int /*<<< orphan*/  kthread_bind (struct task_struct*,unsigned int) ; 
 struct task_struct* kthread_create_on_node (int (*) (void*),void*,int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_kthread (struct task_struct*) ; 

struct task_struct *kthread_create_on_cpu(int (*threadfn)(void *data),
					  void *data, unsigned int cpu,
					  const char *namefmt)
{
	struct task_struct *p;

	p = kthread_create_on_node(threadfn, data, cpu_to_node(cpu), namefmt,
				   cpu);
	if (IS_ERR(p))
		return p;
	kthread_bind(p, cpu);
	/* CPU hotplug need to bind once again when unparking the thread. */
	set_bit(KTHREAD_IS_PER_CPU, &to_kthread(p)->flags);
	to_kthread(p)->cpu = cpu;
	return p;
}