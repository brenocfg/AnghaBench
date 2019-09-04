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
typedef  int u32 ;
struct exynos_pcie {TYPE_1__* mem_res; } ;
struct TYPE_2__ {int /*<<< orphan*/  elbi_base; } ;

/* Variables and functions */
 int IRQ_INTA_ASSERT ; 
 int IRQ_INTB_ASSERT ; 
 int IRQ_INTC_ASSERT ; 
 int IRQ_INTD_ASSERT ; 
 int /*<<< orphan*/  PCIE_IRQ_EN_PULSE ; 
 int /*<<< orphan*/  exynos_pcie_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_pcie_enable_irq_pulse(struct exynos_pcie *ep)
{
	u32 val;

	/* enable INTX interrupt */
	val = IRQ_INTA_ASSERT | IRQ_INTB_ASSERT |
		IRQ_INTC_ASSERT | IRQ_INTD_ASSERT;
	exynos_pcie_writel(ep->mem_res->elbi_base, val, PCIE_IRQ_EN_PULSE);
}