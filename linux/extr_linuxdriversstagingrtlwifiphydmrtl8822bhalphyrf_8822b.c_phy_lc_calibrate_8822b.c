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
typedef  int /*<<< orphan*/  u64 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _phy_lc_calibrate_8822b (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_get_current_time (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_get_progressing_time (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void phy_lc_calibrate_8822b(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	bool is_start_cont_tx = false, is_single_tone = false,
	     is_carrier_suppression = false;
	u64 start_time;
	u64 progressing_time;

	if (is_start_cont_tx || is_single_tone || is_carrier_suppression) {
		ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
			     "[LCK]continues TX ing !!! LCK return\n");
		return;
	}

	start_time = odm_get_current_time(dm);
	_phy_lc_calibrate_8822b(dm);
	progressing_time = odm_get_progressing_time(dm, start_time);
	ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
		     "[LCK]LCK progressing_time = %lld\n", progressing_time);
}