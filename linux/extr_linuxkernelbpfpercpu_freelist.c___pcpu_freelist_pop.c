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
struct pcpu_freelist_node {struct pcpu_freelist_node* next; } ;
struct pcpu_freelist_head {int /*<<< orphan*/  lock; struct pcpu_freelist_node* first; } ;
struct pcpu_freelist {int /*<<< orphan*/  freelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_possible_mask ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 struct pcpu_freelist_head* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

struct pcpu_freelist_node *__pcpu_freelist_pop(struct pcpu_freelist *s)
{
	struct pcpu_freelist_head *head;
	struct pcpu_freelist_node *node;
	int orig_cpu, cpu;

	orig_cpu = cpu = raw_smp_processor_id();
	while (1) {
		head = per_cpu_ptr(s->freelist, cpu);
		raw_spin_lock(&head->lock);
		node = head->first;
		if (node) {
			head->first = node->next;
			raw_spin_unlock(&head->lock);
			return node;
		}
		raw_spin_unlock(&head->lock);
		cpu = cpumask_next(cpu, cpu_possible_mask);
		if (cpu >= nr_cpu_ids)
			cpu = 0;
		if (cpu == orig_cpu)
			return NULL;
	}
}