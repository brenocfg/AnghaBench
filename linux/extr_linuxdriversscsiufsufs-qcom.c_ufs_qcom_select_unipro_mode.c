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
struct ufs_qcom_host {int /*<<< orphan*/  hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUNIPRO_SEL ; 
 int /*<<< orphan*/  REG_UFS_CFG1 ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ ufs_qcom_cap_qunipro (struct ufs_qcom_host*) ; 
 int /*<<< orphan*/  ufshcd_rmwl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufs_qcom_select_unipro_mode(struct ufs_qcom_host *host)
{
	ufshcd_rmwl(host->hba, QUNIPRO_SEL,
		   ufs_qcom_cap_qunipro(host) ? QUNIPRO_SEL : 0,
		   REG_UFS_CFG1);
	/* make sure above configuration is applied before we return */
	mb();
}