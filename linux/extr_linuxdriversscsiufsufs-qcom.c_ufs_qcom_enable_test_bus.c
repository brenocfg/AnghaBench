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
struct ufs_qcom_host {int dbg_print_en; int /*<<< orphan*/  hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UFS_CFG1 ; 
 int /*<<< orphan*/  TEST_BUS_EN ; 
 int UFS_QCOM_DBG_PRINT_TEST_BUS_EN ; 
 int /*<<< orphan*/  UFS_REG_TEST_BUS_EN ; 
 int /*<<< orphan*/  ufshcd_rmwl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufs_qcom_enable_test_bus(struct ufs_qcom_host *host)
{
	if (host->dbg_print_en & UFS_QCOM_DBG_PRINT_TEST_BUS_EN) {
		ufshcd_rmwl(host->hba, UFS_REG_TEST_BUS_EN,
				UFS_REG_TEST_BUS_EN, REG_UFS_CFG1);
		ufshcd_rmwl(host->hba, TEST_BUS_EN, TEST_BUS_EN, REG_UFS_CFG1);
	} else {
		ufshcd_rmwl(host->hba, UFS_REG_TEST_BUS_EN, 0, REG_UFS_CFG1);
		ufshcd_rmwl(host->hba, TEST_BUS_EN, 0, REG_UFS_CFG1);
	}
}