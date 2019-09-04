#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iproc_pcie {int /*<<< orphan*/  dev; } ;
struct iproc_msi {int nr_irqs; TYPE_1__* grps; scalar_t__ nr_cpus; struct iproc_pcie* pcie; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;
struct TYPE_2__ {int /*<<< orphan*/  gic_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_msi_handler ; 
 int /*<<< orphan*/  iproc_msi_irq_free (struct iproc_msi*,unsigned int) ; 
 int irq_set_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int iproc_msi_irq_setup(struct iproc_msi *msi, unsigned int cpu)
{
	int i, ret;
	cpumask_var_t mask;
	struct iproc_pcie *pcie = msi->pcie;

	for (i = cpu; i < msi->nr_irqs; i += msi->nr_cpus) {
		irq_set_chained_handler_and_data(msi->grps[i].gic_irq,
						 iproc_msi_handler,
						 &msi->grps[i]);
		/* Dedicate GIC interrupt to each CPU core */
		if (alloc_cpumask_var(&mask, GFP_KERNEL)) {
			cpumask_clear(mask);
			cpumask_set_cpu(cpu, mask);
			ret = irq_set_affinity(msi->grps[i].gic_irq, mask);
			if (ret)
				dev_err(pcie->dev,
					"failed to set affinity for IRQ%d\n",
					msi->grps[i].gic_irq);
			free_cpumask_var(mask);
		} else {
			dev_err(pcie->dev, "failed to alloc CPU mask\n");
			ret = -EINVAL;
		}

		if (ret) {
			/* Free all configured/unconfigured IRQs */
			iproc_msi_irq_free(msi, cpu);
			return ret;
		}
	}

	return 0;
}