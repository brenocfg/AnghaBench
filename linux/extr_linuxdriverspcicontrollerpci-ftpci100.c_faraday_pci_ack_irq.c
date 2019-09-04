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
struct irq_data {int dummy; } ;
struct faraday_pci {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (scalar_t__) ; 
 int /*<<< orphan*/  FARADAY_PCI_CTRL2 ; 
 int PCI_CTRL2_INTSTS_SHIFT ; 
 int /*<<< orphan*/  faraday_raw_pci_read_config (struct faraday_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  faraday_raw_pci_write_config (struct faraday_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct faraday_pci* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static void faraday_pci_ack_irq(struct irq_data *d)
{
	struct faraday_pci *p = irq_data_get_irq_chip_data(d);
	unsigned int reg;

	faraday_raw_pci_read_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, &reg);
	reg &= ~(0xF << PCI_CTRL2_INTSTS_SHIFT);
	reg |= BIT(irqd_to_hwirq(d) + PCI_CTRL2_INTSTS_SHIFT);
	faraday_raw_pci_write_config(p, 0, 0, FARADAY_PCI_CTRL2, 4, reg);
}