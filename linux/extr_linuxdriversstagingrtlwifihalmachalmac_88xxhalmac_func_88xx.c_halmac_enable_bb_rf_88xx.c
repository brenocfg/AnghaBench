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
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; } ;

/* Variables and functions */
 int BIT (int) ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_RF_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_WLRF1 ; 

void halmac_enable_bb_rf_88xx(struct halmac_adapter *halmac_adapter, u8 enable)
{
	u8 value8;
	u32 value32;
	struct halmac_api *halmac_api;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (enable == 1) {
		value8 = HALMAC_REG_READ_8(halmac_adapter, REG_SYS_FUNC_EN);
		value8 = value8 | BIT(0) | BIT(1);
		HALMAC_REG_WRITE_8(halmac_adapter, REG_SYS_FUNC_EN, value8);

		value8 = HALMAC_REG_READ_8(halmac_adapter, REG_RF_CTRL);
		value8 = value8 | BIT(0) | BIT(1) | BIT(2);
		HALMAC_REG_WRITE_8(halmac_adapter, REG_RF_CTRL, value8);

		value32 = HALMAC_REG_READ_32(halmac_adapter, REG_WLRF1);
		value32 = value32 | BIT(24) | BIT(25) | BIT(26);
		HALMAC_REG_WRITE_32(halmac_adapter, REG_WLRF1, value32);
	} else {
		value8 = HALMAC_REG_READ_8(halmac_adapter, REG_SYS_FUNC_EN);
		value8 = value8 & (~(BIT(0) | BIT(1)));
		HALMAC_REG_WRITE_8(halmac_adapter, REG_SYS_FUNC_EN, value8);

		value8 = HALMAC_REG_READ_8(halmac_adapter, REG_RF_CTRL);
		value8 = value8 & (~(BIT(0) | BIT(1) | BIT(2)));
		HALMAC_REG_WRITE_8(halmac_adapter, REG_RF_CTRL, value8);

		value32 = HALMAC_REG_READ_32(halmac_adapter, REG_WLRF1);
		value32 = value32 & (~(BIT(24) | BIT(25) | BIT(26)));
		HALMAC_REG_WRITE_32(halmac_adapter, REG_WLRF1, value32);
	}
}