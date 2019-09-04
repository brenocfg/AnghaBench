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
struct dm_iqk_info {int* lok_fail; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int LOK_delay_8822B ; 
 scalar_t__ ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  ODM_delay_ms (int) ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int odm_get_rf_reg (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ) ; 
 int odm_read_4byte (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static bool _lok_one_shot_8822b(void *dm_void, u8 path)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	u8 delay_count = 0;
	bool LOK_notready = false;
	u32 LOK_temp = 0;
	u32 IQK_CMD = 0x0;

	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
		     "[IQK]==========S%d LOK ==========\n", path);

	IQK_CMD = 0xf8000008 | (1 << (4 + path));

	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION, "[IQK]LOK_Trigger = 0x%x\n",
		     IQK_CMD);

	odm_write_4byte(dm, 0x1b00, IQK_CMD);
	odm_write_4byte(dm, 0x1b00, IQK_CMD + 1);
	/*LOK: CMD ID = 0	{0xf8000018, 0xf8000028}*/
	/*LOK: CMD ID = 0	{0xf8000019, 0xf8000029}*/
	ODM_delay_ms(LOK_delay_8822B);

	delay_count = 0;
	LOK_notready = true;

	while (LOK_notready) {
		if (odm_read_4byte(dm, 0x1b00) == (IQK_CMD & 0xffffff0f))
			LOK_notready = false;
		else
			LOK_notready = true;

		if (LOK_notready) {
			ODM_delay_ms(1);
			delay_count++;
		}

		if (delay_count >= 50) {
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]S%d LOK timeout!!!\n", path);
			break;
		}
	}

	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
		     "[IQK]S%d ==> delay_count = 0x%x\n", path, delay_count);
	if (ODM_COMP_CALIBRATION) {
		if (!LOK_notready) {
			LOK_temp =
				odm_get_rf_reg(dm, (enum odm_rf_radio_path)path,
					       0x58, RFREGOFFSETMASK);
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]0x58 = 0x%x\n", LOK_temp);
		} else {
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]==>S%d LOK Fail!!!\n", path);
		}
	}
	iqk_info->lok_fail[path] = LOK_notready;
	return LOK_notready;
}