#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tm_trigger; } ;
struct phy_dm_struct {int support_ability; scalar_t__ support_ic_type; TYPE_1__ rf_calibrate_info; void* adapter; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ IS_HARDWARE_TYPE_8188E (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8188F (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8192E (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8703B (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8723B (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8723D (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8814A (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8821C (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_8822B (void*) ; 
 scalar_t__ IS_HARDWARE_TYPE_JAGUAR (void*) ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int ODM_RF_TX_PWR_TRACK ; 
 scalar_t__ ODM_RTL8710B ; 
 int RFREGOFFSETMASK ; 
 int /*<<< orphan*/  RF_T_METER_NEW ; 
 int /*<<< orphan*/  RF_T_METER_OLD ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  odm_txpowertracking_callback_thermal_meter (struct phy_dm_struct*) ; 

void odm_txpowertracking_check_ce(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	void *adapter = dm->adapter;

	if (!(dm->support_ability & ODM_RF_TX_PWR_TRACK))
		return;

	if (!dm->rf_calibrate_info.tm_trigger) {
		if (IS_HARDWARE_TYPE_8188E(adapter) ||
		    IS_HARDWARE_TYPE_8188F(adapter) ||
		    IS_HARDWARE_TYPE_8192E(adapter) ||
		    IS_HARDWARE_TYPE_8723B(adapter) ||
		    IS_HARDWARE_TYPE_JAGUAR(adapter) ||
		    IS_HARDWARE_TYPE_8814A(adapter) ||
		    IS_HARDWARE_TYPE_8703B(adapter) ||
		    IS_HARDWARE_TYPE_8723D(adapter) ||
		    IS_HARDWARE_TYPE_8822B(adapter) ||
		    IS_HARDWARE_TYPE_8821C(adapter) ||
		    (dm->support_ic_type == ODM_RTL8710B)) /* JJ ADD 20161014 */
			odm_set_rf_reg(dm, ODM_RF_PATH_A, RF_T_METER_NEW,
				       (BIT(17) | BIT(16)), 0x03);
		else
			odm_set_rf_reg(dm, ODM_RF_PATH_A, RF_T_METER_OLD,
				       RFREGOFFSETMASK, 0x60);

		dm->rf_calibrate_info.tm_trigger = 1;
		return;
	}

	odm_txpowertracking_callback_thermal_meter(dm);
	dm->rf_calibrate_info.tm_trigger = 0;
}