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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  thermal_value_iqk; } ;
struct phy_dm_struct {TYPE_1__ rf_calibrate_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_reset_iqk_result (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phy_iq_calibrate_8822b (struct phy_dm_struct*,int) ; 

void do_iqk_8822b(void *dm_void, u8 delta_thermal_index, u8 thermal_value,
		  u8 threshold)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	odm_reset_iqk_result(dm);

	dm->rf_calibrate_info.thermal_value_iqk = thermal_value;

	phy_iq_calibrate_8822b(dm, true);
}