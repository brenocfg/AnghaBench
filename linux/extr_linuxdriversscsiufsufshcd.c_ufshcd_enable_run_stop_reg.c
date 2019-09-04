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
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UTP_TASK_REQ_LIST_RUN_STOP ; 
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_LIST_RUN_STOP ; 
 int /*<<< orphan*/  UTP_TASK_REQ_LIST_RUN_STOP_BIT ; 
 int /*<<< orphan*/  UTP_TRANSFER_REQ_LIST_RUN_STOP_BIT ; 
 int /*<<< orphan*/  ufshcd_writel (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_enable_run_stop_reg(struct ufs_hba *hba)
{
	ufshcd_writel(hba, UTP_TASK_REQ_LIST_RUN_STOP_BIT,
		      REG_UTP_TASK_REQ_LIST_RUN_STOP);
	ufshcd_writel(hba, UTP_TRANSFER_REQ_LIST_RUN_STOP_BIT,
		      REG_UTP_TRANSFER_REQ_LIST_RUN_STOP);
}