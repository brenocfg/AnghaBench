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
struct irq_matrix {int /*<<< orphan*/  maps; } ;
struct cpumap {unsigned int allocated; } ;

/* Variables and functions */
 struct cpumap* this_cpu_ptr (int /*<<< orphan*/ ) ; 

unsigned int irq_matrix_allocated(struct irq_matrix *m)
{
	struct cpumap *cm = this_cpu_ptr(m->maps);

	return cm->allocated;
}