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
struct iproc_pcie {scalar_t__ ep_is_internal; } ;

/* Variables and functions */
 int EP_MODE_SURVIVE_PERST ; 
 int EP_PERST_SOURCE_SELECT ; 
 int /*<<< orphan*/  IPROC_PCIE_CLK_CTRL ; 
 int RC_PCIE_RST_OUTPUT ; 
 int iproc_pcie_read_reg (struct iproc_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pcie_write_reg (struct iproc_pcie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void iproc_pcie_perst_ctrl(struct iproc_pcie *pcie, bool assert)
{
	u32 val;

	/*
	 * PAXC and the internal emulated endpoint device downstream should not
	 * be reset.  If firmware has been loaded on the endpoint device at an
	 * earlier boot stage, reset here causes issues.
	 */
	if (pcie->ep_is_internal)
		return;

	if (assert) {
		val = iproc_pcie_read_reg(pcie, IPROC_PCIE_CLK_CTRL);
		val &= ~EP_PERST_SOURCE_SELECT & ~EP_MODE_SURVIVE_PERST &
			~RC_PCIE_RST_OUTPUT;
		iproc_pcie_write_reg(pcie, IPROC_PCIE_CLK_CTRL, val);
		udelay(250);
	} else {
		val = iproc_pcie_read_reg(pcie, IPROC_PCIE_CLK_CTRL);
		val |= RC_PCIE_RST_OUTPUT;
		iproc_pcie_write_reg(pcie, IPROC_PCIE_CLK_CTRL, val);
		msleep(100);
	}
}