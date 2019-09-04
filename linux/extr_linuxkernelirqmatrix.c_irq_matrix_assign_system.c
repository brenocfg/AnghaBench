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
struct irq_matrix {unsigned int matrix_bits; int online_maps; unsigned int alloc_start; unsigned int alloc_end; int /*<<< orphan*/  systembits_inalloc; int /*<<< orphan*/  total_allocated; int /*<<< orphan*/  system_map; int /*<<< orphan*/  maps; } ;
struct cpumap {int /*<<< orphan*/  allocated; int /*<<< orphan*/  alloc_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct cpumap* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_irq_matrix_assign_system (unsigned int,struct irq_matrix*) ; 

void irq_matrix_assign_system(struct irq_matrix *m, unsigned int bit,
			      bool replace)
{
	struct cpumap *cm = this_cpu_ptr(m->maps);

	BUG_ON(bit > m->matrix_bits);
	BUG_ON(m->online_maps > 1 || (m->online_maps && !replace));

	set_bit(bit, m->system_map);
	if (replace) {
		BUG_ON(!test_and_clear_bit(bit, cm->alloc_map));
		cm->allocated--;
		m->total_allocated--;
	}
	if (bit >= m->alloc_start && bit < m->alloc_end)
		m->systembits_inalloc++;

	trace_irq_matrix_assign_system(bit, m);
}