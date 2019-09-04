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
struct msi_msg {int data; int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; } ;
struct mobiveil_pcie {TYPE_1__* pdev; scalar_t__ pcie_reg_base; } ;
struct irq_data {int hwirq; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mobiveil_pcie* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void mobiveil_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct mobiveil_pcie *pcie = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = pcie->pcie_reg_base + (data->hwirq * sizeof(int));

	msg->address_lo = lower_32_bits(addr);
	msg->address_hi = upper_32_bits(addr);
	msg->data = data->hwirq;

	dev_dbg(&pcie->pdev->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(int)data->hwirq, msg->address_hi, msg->address_lo);
}