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
struct cpumap {int /*<<< orphan*/  available; int /*<<< orphan*/  allocated; int /*<<< orphan*/  alloc_map; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct cpumap* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_irq_matrix_assign (unsigned int,int /*<<< orphan*/ ,struct irq_matrix*,struct cpumap*) ; 

void irq_matrix_assign(struct irq_matrix *m, unsigned int bit)
{
	struct cpumap *cm = this_cpu_ptr(m->maps);

	if (WARN_ON_ONCE(bit < m->alloc_start || bit >= m->alloc_end))
		return;
	if (WARN_ON_ONCE(test_and_set_bit(bit, cm->alloc_map)))
		return;
	cm->allocated++;
	m->total_allocated++;
	cm->available--;
	m->global_available--;
	trace_irq_matrix_assign(bit, smp_processor_id(), m, cm);
}