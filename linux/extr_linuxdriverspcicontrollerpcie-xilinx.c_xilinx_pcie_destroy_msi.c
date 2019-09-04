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
struct xilinx_pcie_port {int /*<<< orphan*/  dev; } ;
struct msi_desc {int dummy; } ;
struct irq_data {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 struct msi_desc* irq_get_msi_desc (unsigned int) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 struct xilinx_pcie_port* msi_desc_to_pci_sysdata (struct msi_desc*) ; 
 int /*<<< orphan*/  msi_irq_in_use ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xilinx_pcie_destroy_msi(unsigned int irq)
{
	struct msi_desc *msi;
	struct xilinx_pcie_port *port;
	struct irq_data *d = irq_get_irq_data(irq);
	irq_hw_number_t hwirq = irqd_to_hwirq(d);

	if (!test_bit(hwirq, msi_irq_in_use)) {
		msi = irq_get_msi_desc(irq);
		port = msi_desc_to_pci_sysdata(msi);
		dev_err(port->dev, "Trying to free unused MSI#%d\n", irq);
	} else {
		clear_bit(hwirq, msi_irq_in_use);
	}
}