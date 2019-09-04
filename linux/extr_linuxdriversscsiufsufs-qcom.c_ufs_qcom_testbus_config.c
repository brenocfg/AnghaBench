#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int select_major; scalar_t__ select_minor; } ;
struct ufs_qcom_host {TYPE_2__* hba; TYPE_1__ testbus; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int REG_UFS_CFG1 ; 
 int TEST_BUS_SEL ; 
 int TEST_BUS_SUB_SEL_MASK ; 
#define  TSTBUS_COMBINED 139 
#define  TSTBUS_DFC 138 
#define  TSTBUS_OCSC 137 
#define  TSTBUS_RXUC 136 
#define  TSTBUS_TMRLUT 135 
#define  TSTBUS_TRLUT 134 
#define  TSTBUS_TXUC 133 
#define  TSTBUS_UARM 132 
#define  TSTBUS_UAWM 131 
#define  TSTBUS_UNIPRO 130 
#define  TSTBUS_UTP_HCI 129 
#define  TSTBUS_WRAPPER 128 
 int UFS_TEST_BUS_CTRL_0 ; 
 int UFS_TEST_BUS_CTRL_1 ; 
 int UFS_TEST_BUS_CTRL_2 ; 
 int UFS_UNIPRO_CFG ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_qcom_enable_test_bus (struct ufs_qcom_host*) ; 
 int /*<<< orphan*/  ufs_qcom_testbus_cfg_is_ok (struct ufs_qcom_host*) ; 
 int /*<<< orphan*/  ufshcd_hold (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ufshcd_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ufshcd_rmwl (TYPE_2__*,int,int,int) ; 

int ufs_qcom_testbus_config(struct ufs_qcom_host *host)
{
	int reg;
	int offset;
	u32 mask = TEST_BUS_SUB_SEL_MASK;

	if (!host)
		return -EINVAL;

	if (!ufs_qcom_testbus_cfg_is_ok(host))
		return -EPERM;

	switch (host->testbus.select_major) {
	case TSTBUS_UAWM:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 24;
		break;
	case TSTBUS_UARM:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 16;
		break;
	case TSTBUS_TXUC:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 8;
		break;
	case TSTBUS_RXUC:
		reg = UFS_TEST_BUS_CTRL_0;
		offset = 0;
		break;
	case TSTBUS_DFC:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 24;
		break;
	case TSTBUS_TRLUT:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 16;
		break;
	case TSTBUS_TMRLUT:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 8;
		break;
	case TSTBUS_OCSC:
		reg = UFS_TEST_BUS_CTRL_1;
		offset = 0;
		break;
	case TSTBUS_WRAPPER:
		reg = UFS_TEST_BUS_CTRL_2;
		offset = 16;
		break;
	case TSTBUS_COMBINED:
		reg = UFS_TEST_BUS_CTRL_2;
		offset = 8;
		break;
	case TSTBUS_UTP_HCI:
		reg = UFS_TEST_BUS_CTRL_2;
		offset = 0;
		break;
	case TSTBUS_UNIPRO:
		reg = UFS_UNIPRO_CFG;
		offset = 20;
		mask = 0xFFF;
		break;
	/*
	 * No need for a default case, since
	 * ufs_qcom_testbus_cfg_is_ok() checks that the configuration
	 * is legal
	 */
	}
	mask <<= offset;

	pm_runtime_get_sync(host->hba->dev);
	ufshcd_hold(host->hba, false);
	ufshcd_rmwl(host->hba, TEST_BUS_SEL,
		    (u32)host->testbus.select_major << 19,
		    REG_UFS_CFG1);
	ufshcd_rmwl(host->hba, mask,
		    (u32)host->testbus.select_minor << offset,
		    reg);
	ufs_qcom_enable_test_bus(host);
	/*
	 * Make sure the test bus configuration is
	 * committed before returning.
	 */
	mb();
	ufshcd_release(host->hba);
	pm_runtime_put_sync(host->hba->dev);

	return 0;
}