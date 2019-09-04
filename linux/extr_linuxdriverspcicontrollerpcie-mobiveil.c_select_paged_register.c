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
struct mobiveil_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAB_CTRL ; 
 int PAGE_SEL_MASK ; 
 int PAGE_SEL_OFFSET_SHIFT ; 
 int PAGE_SEL_SHIFT ; 
 int csr_readl (struct mobiveil_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csr_writel (struct mobiveil_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void select_paged_register(struct mobiveil_pcie *pcie, u32 offset)
{
	int pab_ctrl_dw, pg_sel;

	/* clear pg_sel field */
	pab_ctrl_dw = csr_readl(pcie, PAB_CTRL);
	pab_ctrl_dw = (pab_ctrl_dw & ~(PAGE_SEL_MASK << PAGE_SEL_SHIFT));

	/* set pg_sel field */
	pg_sel = (offset >> PAGE_SEL_OFFSET_SHIFT) & PAGE_SEL_MASK;
	pab_ctrl_dw |= ((pg_sel << PAGE_SEL_SHIFT));
	csr_writel(pcie, pab_ctrl_dw, PAB_CTRL);
}