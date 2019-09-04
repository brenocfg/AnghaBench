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
typedef  int u8 ;
typedef  int u32 ;
struct dra7xx_pcie {int dummy; } ;

/* Variables and functions */
 int MSI_REQ_GRANT ; 
 int MSI_VECTOR_SHIFT ; 
 int /*<<< orphan*/  PCIECTRL_TI_CONF_MSI_XMT ; 
 int /*<<< orphan*/  dra7xx_pcie_writel (struct dra7xx_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dra7xx_pcie_raise_msi_irq(struct dra7xx_pcie *dra7xx,
				      u8 interrupt_num)
{
	u32 reg;

	reg = (interrupt_num - 1) << MSI_VECTOR_SHIFT;
	reg |= MSI_REQ_GRANT;
	dra7xx_pcie_writel(dra7xx, PCIECTRL_TI_CONF_MSI_XMT, reg);
}