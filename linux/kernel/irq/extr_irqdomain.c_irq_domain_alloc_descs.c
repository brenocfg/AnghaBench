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
struct irq_affinity_desc {int dummy; } ;
typedef  unsigned int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int __irq_alloc_descs (int,int,unsigned int,int,int /*<<< orphan*/ ,struct irq_affinity_desc const*) ; 
 unsigned int nr_irqs ; 

int irq_domain_alloc_descs(int virq, unsigned int cnt, irq_hw_number_t hwirq,
			   int node, const struct irq_affinity_desc *affinity)
{
	unsigned int hint;

	if (virq >= 0) {
		virq = __irq_alloc_descs(virq, virq, cnt, node, THIS_MODULE,
					 affinity);
	} else {
		hint = hwirq % nr_irqs;
		if (hint == 0)
			hint++;
		virq = __irq_alloc_descs(-1, hint, cnt, node, THIS_MODULE,
					 affinity);
		if (virq <= 0 && hint > 1) {
			virq = __irq_alloc_descs(-1, 1, cnt, node, THIS_MODULE,
						 affinity);
		}
	}

	return virq;
}