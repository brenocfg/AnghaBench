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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct phy_dm_struct {int support_ic_type; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int ODM_RTL8821C ; 
 int ODM_RTL8822B ; 
 int config_phydm_write_txagc_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int phydm_write_txagc_1byte_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool phydm_api_set_txagc(struct phy_dm_struct *dm, u32 power_index,
			 enum odm_rf_radio_path path, u8 hw_rate,
			 bool is_single_rate)
{
	bool ret = false;

	if (dm->support_ic_type & (ODM_RTL8822B | ODM_RTL8821C)) {
		if (is_single_rate) {
			if (dm->support_ic_type == ODM_RTL8822B)
				ret = phydm_write_txagc_1byte_8822b(
					dm, power_index, path, hw_rate);

		} else {
			if (dm->support_ic_type == ODM_RTL8822B)
				ret = config_phydm_write_txagc_8822b(
					dm, power_index, path, hw_rate);
		}
	}

	return ret;
}