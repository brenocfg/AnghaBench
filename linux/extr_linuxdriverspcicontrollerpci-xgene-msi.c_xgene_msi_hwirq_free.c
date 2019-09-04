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
struct xgene_msi_group {int /*<<< orphan*/  gic_irq; } ;
struct xgene_msi {struct xgene_msi_group* msi_groups; scalar_t__ num_cpus; } ;

/* Variables and functions */
 int NR_HW_IRQS ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct xgene_msi xgene_msi_ctrl ; 

__attribute__((used)) static int xgene_msi_hwirq_free(unsigned int cpu)
{
	struct xgene_msi *msi = &xgene_msi_ctrl;
	struct xgene_msi_group *msi_group;
	int i;

	for (i = cpu; i < NR_HW_IRQS; i += msi->num_cpus) {
		msi_group = &msi->msi_groups[i];
		if (!msi_group->gic_irq)
			continue;

		irq_set_chained_handler_and_data(msi_group->gic_irq, NULL,
						 NULL);
	}
	return 0;
}