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
typedef  int /*<<< orphan*/  u32 ;
struct ufs_hba {int /*<<< orphan*/  dev; int /*<<< orphan*/  utmrdl_dma_addr; int /*<<< orphan*/  utrdl_dma_addr; scalar_t__ nutrs; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INT_AGGR_DEF_TO ; 
 int /*<<< orphan*/  REG_CONTROLLER_STATUS ; 
 int /*<<< orphan*/  REG_UTP_TASK_REQ_LIST_BASE_H ; 
 int /*<<< orphan*/  REG_UTP_TASK_REQ_LIST_BASE_L ; 
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_LIST_BASE_H ; 
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_LIST_BASE_L ; 
 int /*<<< orphan*/  UFSHCD_ENABLE_INTRS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_config_intr_aggr (struct ufs_hba*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_disable_intr_aggr (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_enable_intr (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_enable_run_stop_reg (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_get_lists_status (int /*<<< orphan*/ ) ; 
 scalar_t__ ufshcd_is_intr_aggr_allowed (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ufshcd_make_hba_operational(struct ufs_hba *hba)
{
	int err = 0;
	u32 reg;

	/* Enable required interrupts */
	ufshcd_enable_intr(hba, UFSHCD_ENABLE_INTRS);

	/* Configure interrupt aggregation */
	if (ufshcd_is_intr_aggr_allowed(hba))
		ufshcd_config_intr_aggr(hba, hba->nutrs - 1, INT_AGGR_DEF_TO);
	else
		ufshcd_disable_intr_aggr(hba);

	/* Configure UTRL and UTMRL base address registers */
	ufshcd_writel(hba, lower_32_bits(hba->utrdl_dma_addr),
			REG_UTP_TRANSFER_REQ_LIST_BASE_L);
	ufshcd_writel(hba, upper_32_bits(hba->utrdl_dma_addr),
			REG_UTP_TRANSFER_REQ_LIST_BASE_H);
	ufshcd_writel(hba, lower_32_bits(hba->utmrdl_dma_addr),
			REG_UTP_TASK_REQ_LIST_BASE_L);
	ufshcd_writel(hba, upper_32_bits(hba->utmrdl_dma_addr),
			REG_UTP_TASK_REQ_LIST_BASE_H);

	/*
	 * Make sure base address and interrupt setup are updated before
	 * enabling the run/stop registers below.
	 */
	wmb();

	/*
	 * UCRDY, UTMRLDY and UTRLRDY bits must be 1
	 */
	reg = ufshcd_readl(hba, REG_CONTROLLER_STATUS);
	if (!(ufshcd_get_lists_status(reg))) {
		ufshcd_enable_run_stop_reg(hba);
	} else {
		dev_err(hba->dev,
			"Host controller not ready to process requests");
		err = -EIO;
		goto out;
	}

out:
	return err;
}