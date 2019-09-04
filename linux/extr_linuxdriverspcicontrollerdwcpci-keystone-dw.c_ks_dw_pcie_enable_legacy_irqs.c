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
struct keystone_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ IRQ_ENABLE_SET ; 
 int PCI_NUM_INTX ; 
 int /*<<< orphan*/  ks_dw_app_writel (struct keystone_pcie*,scalar_t__,int) ; 

void ks_dw_pcie_enable_legacy_irqs(struct keystone_pcie *ks_pcie)
{
	int i;

	for (i = 0; i < PCI_NUM_INTX; i++)
		ks_dw_app_writel(ks_pcie, IRQ_ENABLE_SET + (i << 4), 0x1);
}