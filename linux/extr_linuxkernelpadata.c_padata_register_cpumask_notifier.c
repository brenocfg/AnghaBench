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
struct padata_instance {int /*<<< orphan*/  cpumask_change_notifier; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int padata_register_cpumask_notifier(struct padata_instance *pinst,
				     struct notifier_block *nblock)
{
	return blocking_notifier_chain_register(&pinst->cpumask_change_notifier,
						nblock);
}