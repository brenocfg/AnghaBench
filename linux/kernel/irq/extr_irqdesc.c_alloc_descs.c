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
typedef  unsigned int u32 ;
struct module {int dummy; } ;
struct irq_desc {struct module* owner; } ;
struct irq_affinity_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_irqs ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

__attribute__((used)) static inline int alloc_descs(unsigned int start, unsigned int cnt, int node,
			      const struct irq_affinity_desc *affinity,
			      struct module *owner)
{
	u32 i;

	for (i = 0; i < cnt; i++) {
		struct irq_desc *desc = irq_to_desc(start + i);

		desc->owner = owner;
	}
	bitmap_set(allocated_irqs, start, cnt);
	return start;
}