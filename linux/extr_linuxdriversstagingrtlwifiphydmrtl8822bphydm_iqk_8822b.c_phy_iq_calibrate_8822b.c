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
struct TYPE_2__ {int is_iqk_in_progress; void* iqk_progressing_time; void* iqk_start_time; } ;
struct phy_dm_struct {TYPE_1__ rf_calibrate_info; scalar_t__ mp_mode; scalar_t__ iqk_fw_offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  RT_IQK_SPINLOCK ; 
 int /*<<< orphan*/  _iq_calibrate_8822b_init (void*) ; 
 int /*<<< orphan*/  _phy_iq_calibrate_8822b (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  _phy_iq_calibrate_by_fw_8822b (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_acquire_spin_lock (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 void* odm_get_current_time (struct phy_dm_struct*) ; 
 void* odm_get_progressing_time (struct phy_dm_struct*,void*) ; 
 int /*<<< orphan*/  odm_read_4byte (struct phy_dm_struct*,int) ; 
 int /*<<< orphan*/  odm_release_spin_lock (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  phydm_get_read_counter (struct phy_dm_struct*) ; 

void phy_iq_calibrate_8822b(void *dm_void, bool clear)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	dm->iqk_fw_offload = 0;

	/*FW IQK*/
	if (dm->iqk_fw_offload) {
		if (!dm->rf_calibrate_info.is_iqk_in_progress) {
			odm_acquire_spin_lock(dm, RT_IQK_SPINLOCK);
			dm->rf_calibrate_info.is_iqk_in_progress = true;
			odm_release_spin_lock(dm, RT_IQK_SPINLOCK);

			dm->rf_calibrate_info.iqk_start_time =
				odm_get_current_time(dm);

			odm_write_4byte(dm, 0x1b00, 0xf8000008);
			odm_set_bb_reg(dm, 0x1bf0, 0xff000000, 0xff);
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]0x1bf0 = 0x%x\n",
				     odm_read_4byte(dm, 0x1bf0));

			_phy_iq_calibrate_by_fw_8822b(dm, clear);
			phydm_get_read_counter(dm);

			dm->rf_calibrate_info.iqk_progressing_time =
				odm_get_progressing_time(
					dm,
					dm->rf_calibrate_info.iqk_start_time);

			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]IQK progressing_time = %lld ms\n",
				dm->rf_calibrate_info.iqk_progressing_time);

			odm_acquire_spin_lock(dm, RT_IQK_SPINLOCK);
			dm->rf_calibrate_info.is_iqk_in_progress = false;
			odm_release_spin_lock(dm, RT_IQK_SPINLOCK);
		} else {
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"== Return the IQK CMD, because the IQK in Progress ==\n");
		}

	} else {
		_iq_calibrate_8822b_init(dm_void);

		if (!dm->rf_calibrate_info.is_iqk_in_progress) {
			odm_acquire_spin_lock(dm, RT_IQK_SPINLOCK);
			dm->rf_calibrate_info.is_iqk_in_progress = true;
			odm_release_spin_lock(dm, RT_IQK_SPINLOCK);
			if (dm->mp_mode)
				dm->rf_calibrate_info.iqk_start_time =
					odm_get_current_time(dm);

			_phy_iq_calibrate_8822b(dm, clear);
			if (dm->mp_mode) {
				dm->rf_calibrate_info.iqk_progressing_time =
					odm_get_progressing_time(
						dm, dm->rf_calibrate_info
							    .iqk_start_time);
				ODM_RT_TRACE(
					dm, ODM_COMP_CALIBRATION,
					"[IQK]IQK progressing_time = %lld ms\n",
					dm->rf_calibrate_info
						.iqk_progressing_time);
			}
			odm_acquire_spin_lock(dm, RT_IQK_SPINLOCK);
			dm->rf_calibrate_info.is_iqk_in_progress = false;
			odm_release_spin_lock(dm, RT_IQK_SPINLOCK);
		} else {
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]== Return the IQK CMD, because the IQK in Progress ==\n");
		}
	}
}