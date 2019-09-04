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
typedef  int u32 ;
struct pcie_port {int dummy; } ;
struct keystone_pcie {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 scalar_t__ IRQ_EOI ; 
 scalar_t__ MSI0_IRQ_STATUS ; 
 scalar_t__ MSI_IRQ_OFFSET ; 
 int /*<<< orphan*/  ks_dw_app_writel (struct keystone_pcie*,scalar_t__,scalar_t__) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct keystone_pcie* to_keystone_pcie (struct dw_pcie*) ; 
 int /*<<< orphan*/  update_reg_offset_bit_pos (int,int*,int*) ; 

void ks_dw_pcie_msi_irq_ack(int irq, struct pcie_port *pp)
{
	u32 reg_offset, bit_pos;
	struct keystone_pcie *ks_pcie;
	struct dw_pcie *pci;

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);
	update_reg_offset_bit_pos(irq, &reg_offset, &bit_pos);

	ks_dw_app_writel(ks_pcie, MSI0_IRQ_STATUS + (reg_offset << 4),
			 BIT(bit_pos));
	ks_dw_app_writel(ks_pcie, IRQ_EOI, reg_offset + MSI_IRQ_OFFSET);
}