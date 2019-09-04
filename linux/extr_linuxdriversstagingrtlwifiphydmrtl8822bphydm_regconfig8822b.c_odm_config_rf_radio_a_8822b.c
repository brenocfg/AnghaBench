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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  odm_config_rf_reg_8822b (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ,int) ; 

void odm_config_rf_radio_a_8822b(struct phy_dm_struct *dm, u32 addr, u32 data)
{
	u32 content = 0x1000; /* RF_Content: radioa_txt */
	u32 maskfor_phy_set = (u32)(content & 0xE000);

	odm_config_rf_reg_8822b(dm, addr, data, ODM_RF_PATH_A,
				addr | maskfor_phy_set);

	ODM_RT_TRACE(
		dm, ODM_COMP_INIT,
		"===> odm_config_rf_with_header_file: [RadioA] %08X %08X\n",
		addr, data);
}