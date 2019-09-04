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
struct dm_iqk_info {int tmp1bcc; int lna_idx; int isbnd; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  GS_delay_8822B ; 
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ODM_delay_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int RXIQK1 ; 
 int RXIQK2 ; 
 int _iqk_check_cal_8822b (struct phy_dm_struct*,int) ; 
 int odm_get_rf_reg (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ) ; 
 int odm_read_4byte (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static bool _iqk_rx_iqk_gain_search_fail_8822b(struct phy_dm_struct *dm,
					       u8 path, u8 step)
{
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	bool fail = true;
	u32 IQK_CMD = 0x0, rf_reg0, tmp, bb_idx;
	u8 IQMUX[4] = {0x9, 0x12, 0x1b, 0x24};
	u8 idx;

	for (idx = 0; idx < 4; idx++)
		if (iqk_info->tmp1bcc == IQMUX[idx])
			break;

	odm_write_4byte(dm, 0x1b00, 0xf8000008 | path << 1);
	odm_write_4byte(dm, 0x1bcc, iqk_info->tmp1bcc);

	if (step == RXIQK1)
		ODM_RT_TRACE(
			dm, ODM_COMP_CALIBRATION,
			"[IQK]============ S%d RXIQK GainSearch ============\n",
			path);

	if (step == RXIQK1)
		IQK_CMD = 0xf8000208 | (1 << (path + 4));
	else
		IQK_CMD = 0xf8000308 | (1 << (path + 4));

	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION, "[IQK]S%d GS%d_Trigger = 0x%x\n",
		     path, step, IQK_CMD);

	odm_write_4byte(dm, 0x1b00, IQK_CMD);
	odm_write_4byte(dm, 0x1b00, IQK_CMD + 0x1);
	ODM_delay_ms(GS_delay_8822B);
	fail = _iqk_check_cal_8822b(dm, IQK_CMD);

	if (step == RXIQK2) {
		rf_reg0 = odm_get_rf_reg(dm, (enum odm_rf_radio_path)path, 0x0,
					 RFREGOFFSETMASK);
		odm_write_4byte(dm, 0x1b00, 0xf8000008 | path << 1);
		ODM_RT_TRACE(
			dm, ODM_COMP_CALIBRATION,
			"[IQK]S%d ==> RF0x0 = 0x%x, tmp1bcc = 0x%x, idx = %d, 0x1b3c = 0x%x\n",
			path, rf_reg0, iqk_info->tmp1bcc, idx,
			odm_read_4byte(dm, 0x1b3c));
		tmp = (rf_reg0 & 0x1fe0) >> 5;
		iqk_info->lna_idx = tmp >> 5;
		bb_idx = tmp & 0x1f;
		if (bb_idx == 0x1) {
			if (iqk_info->lna_idx != 0x0)
				iqk_info->lna_idx--;
			else if (idx != 3)
				idx++;
			else
				iqk_info->isbnd = true;
			fail = true;
		} else if (bb_idx == 0xa) {
			if (idx != 0)
				idx--;
			else if (iqk_info->lna_idx != 0x7)
				iqk_info->lna_idx++;
			else
				iqk_info->isbnd = true;
			fail = true;
		} else {
			fail = false;
		}

		if (iqk_info->isbnd)
			fail = false;

		iqk_info->tmp1bcc = IQMUX[idx];

		if (fail) {
			odm_write_4byte(dm, 0x1b00, 0xf8000008 | path << 1);
			odm_write_4byte(
				dm, 0x1b24,
				(odm_read_4byte(dm, 0x1b24) & 0xffffe3ff) |
					(iqk_info->lna_idx << 10));
		}
	}

	return fail;
}