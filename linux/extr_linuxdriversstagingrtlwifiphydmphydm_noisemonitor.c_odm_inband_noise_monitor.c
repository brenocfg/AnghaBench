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
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int ODM_IC_11AC_SERIES ; 
 int /*<<< orphan*/  odm_inband_noise_monitor_ac_series (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_inband_noise_monitor_n_series (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s16 odm_inband_noise_monitor(void *dm_void, u8 is_pause_dig, u8 igi_value,
			     u32 max_time)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		return odm_inband_noise_monitor_ac_series(dm, is_pause_dig,
							  igi_value, max_time);
	else
		return odm_inband_noise_monitor_n_series(dm, is_pause_dig,
							 igi_value, max_time);
}