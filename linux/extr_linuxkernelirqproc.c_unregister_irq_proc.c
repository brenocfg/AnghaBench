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
struct irq_desc {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int MAX_NAMELEN ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_irq_dir ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

void unregister_irq_proc(unsigned int irq, struct irq_desc *desc)
{
	char name [MAX_NAMELEN];

	if (!root_irq_dir || !desc->dir)
		return;
#ifdef CONFIG_SMP
	remove_proc_entry("smp_affinity", desc->dir);
	remove_proc_entry("affinity_hint", desc->dir);
	remove_proc_entry("smp_affinity_list", desc->dir);
	remove_proc_entry("node", desc->dir);
# ifdef CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	remove_proc_entry("effective_affinity", desc->dir);
	remove_proc_entry("effective_affinity_list", desc->dir);
# endif
#endif
	remove_proc_entry("spurious", desc->dir);

	sprintf(name, "%u", irq);
	remove_proc_entry(name, root_irq_dir);
}