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
struct pcie_port {int* irq_status; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct irq_data {unsigned int hwirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* msi_set_irq ) (struct pcie_port*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int MAX_MSI_IRQS_PER_CTRL ; 
 unsigned int MSI_REG_CTRL_BLOCK_SIZE ; 
 scalar_t__ PCIE_MSI_INTR0_MASK ; 
 int /*<<< orphan*/  dw_pcie_wr_own_conf (struct pcie_port*,scalar_t__,int,int) ; 
 struct pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pcie_port*,unsigned int) ; 

__attribute__((used)) static void dw_pci_bottom_unmask(struct irq_data *data)
{
	struct pcie_port *pp = irq_data_get_irq_chip_data(data);
	unsigned int res, bit, ctrl;
	unsigned long flags;

	raw_spin_lock_irqsave(&pp->lock, flags);

	if (pp->ops->msi_set_irq) {
		pp->ops->msi_set_irq(pp, data->hwirq);
	} else {
		ctrl = data->hwirq / MAX_MSI_IRQS_PER_CTRL;
		res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
		bit = data->hwirq % MAX_MSI_IRQS_PER_CTRL;

		pp->irq_status[ctrl] |= 1 << bit;
		dw_pcie_wr_own_conf(pp, PCIE_MSI_INTR0_MASK + res, 4,
				    ~pp->irq_status[ctrl]);
	}

	raw_spin_unlock_irqrestore(&pp->lock, flags);
}