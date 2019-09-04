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
struct irq_matrix {unsigned int alloc_start; unsigned int alloc_end; int /*<<< orphan*/  global_available; int /*<<< orphan*/  total_allocated; int /*<<< orphan*/  maps; } ;
struct cpumap {scalar_t__ online; int /*<<< orphan*/  available; int /*<<< orphan*/  managed_allocated; int /*<<< orphan*/  allocated; int /*<<< orphan*/  alloc_map; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct cpumap* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  trace_irq_matrix_free (unsigned int,unsigned int,struct irq_matrix*,struct cpumap*) ; 

void irq_matrix_free(struct irq_matrix *m, unsigned int cpu,
		     unsigned int bit, bool managed)
{
	struct cpumap *cm = per_cpu_ptr(m->maps, cpu);

	if (WARN_ON_ONCE(bit < m->alloc_start || bit >= m->alloc_end))
		return;

	clear_bit(bit, cm->alloc_map);
	cm->allocated--;
	if(managed)
		cm->managed_allocated--;

	if (cm->online)
		m->total_allocated--;

	if (!managed) {
		cm->available++;
		if (cm->online)
			m->global_available++;
	}
	trace_irq_matrix_free(bit, cpu, m, cm);
}