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
struct irq_matrix {int /*<<< orphan*/  online_maps; int /*<<< orphan*/  global_available; scalar_t__ systembits_inalloc; scalar_t__ alloc_size; int /*<<< orphan*/  maps; } ;
struct cpumap {int online; int initialized; scalar_t__ available; scalar_t__ managed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct cpumap* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_irq_matrix_online (struct irq_matrix*) ; 

void irq_matrix_online(struct irq_matrix *m)
{
	struct cpumap *cm = this_cpu_ptr(m->maps);

	BUG_ON(cm->online);

	if (!cm->initialized) {
		cm->available = m->alloc_size;
		cm->available -= cm->managed + m->systembits_inalloc;
		cm->initialized = true;
	}
	m->global_available += cm->available;
	cm->online = true;
	m->online_maps++;
	trace_irq_matrix_online(m);
}