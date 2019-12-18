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
struct irq_matrix {int /*<<< orphan*/  online_maps; int /*<<< orphan*/  global_available; int /*<<< orphan*/  maps; } ;
struct cpumap {int online; scalar_t__ available; } ;

/* Variables and functions */
 struct cpumap* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_irq_matrix_offline (struct irq_matrix*) ; 

void irq_matrix_offline(struct irq_matrix *m)
{
	struct cpumap *cm = this_cpu_ptr(m->maps);

	/* Update the global available size */
	m->global_available -= cm->available;
	cm->online = false;
	m->online_maps--;
	trace_irq_matrix_offline(m);
}