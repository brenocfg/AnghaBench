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
typedef  scalar_t__ u8 ;
struct txpwrtrack_cfg {scalar_t__ rf_path_count; int /*<<< orphan*/  (* odm_tx_pwr_track_set_pwr ) (struct phy_dm_struct*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;
struct phy_dm_struct {scalar_t__ support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBSWING ; 
 int /*<<< orphan*/  MIX_MODE ; 
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 scalar_t__ ODM_RF_PATH_A ; 
 scalar_t__ ODM_RTL8188E ; 
 scalar_t__ ODM_RTL8188F ; 
 scalar_t__ ODM_RTL8192E ; 
 scalar_t__ ODM_RTL8703B ; 
 scalar_t__ ODM_RTL8710B ; 
 scalar_t__ ODM_RTL8723B ; 
 scalar_t__ ODM_RTL8723D ; 
 scalar_t__ ODM_RTL8812 ; 
 scalar_t__ ODM_RTL8814A ; 
 scalar_t__ ODM_RTL8821 ; 
 scalar_t__ ODM_RTL8821C ; 
 scalar_t__ ODM_RTL8822B ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct phy_dm_struct*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct phy_dm_struct*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct phy_dm_struct*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void phydm_odm_tx_power_set(struct phy_dm_struct *dm,
					  struct txpwrtrack_cfg *c,
					  u8 indexforchannel, u8 flag)
{
	u8 p = 0;

	if (dm->support_ic_type == ODM_RTL8188E ||
	    dm->support_ic_type == ODM_RTL8192E ||
	    dm->support_ic_type == ODM_RTL8821 ||
	    dm->support_ic_type == ODM_RTL8812 ||
	    dm->support_ic_type == ODM_RTL8723B ||
	    dm->support_ic_type == ODM_RTL8814A ||
	    dm->support_ic_type == ODM_RTL8703B ||
	    dm->support_ic_type == ODM_RTL8188F ||
	    dm->support_ic_type == ODM_RTL8822B ||
	    dm->support_ic_type == ODM_RTL8723D ||
	    dm->support_ic_type == ODM_RTL8821C ||
	    dm->support_ic_type == ODM_RTL8710B) { /* JJ ADD 20161014 */

		ODM_RT_TRACE(
			dm, ODM_COMP_TX_PWR_TRACK,
			"**********Enter POWER Tracking MIX_MODE**********\n");
		for (p = ODM_RF_PATH_A; p < c->rf_path_count; p++) {
			if (flag == 0)
				(*c->odm_tx_pwr_track_set_pwr)(dm, MIX_MODE, p,
							       0);
			else
				(*c->odm_tx_pwr_track_set_pwr)(dm, MIX_MODE, p,
							       indexforchannel);
		}
	} else {
		ODM_RT_TRACE(
			dm, ODM_COMP_TX_PWR_TRACK,
			"**********Enter POWER Tracking BBSWING_MODE**********\n");
		for (p = ODM_RF_PATH_A; p < c->rf_path_count; p++)
			(*c->odm_tx_pwr_track_set_pwr)(dm, BBSWING, p,
						       indexforchannel);
	}
}