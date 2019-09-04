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
typedef  size_t u32 ;
struct rtl_sta_info {int dummy; } ;
struct phy_dm_struct {scalar_t__* band_width; int* sec_ch_offset; int is_one_entry_only; size_t one_entry_macid; int pre_number_linked_client; int number_linked_client; int pre_number_active_client; int number_active_client; scalar_t__ phydm_period; int /*<<< orphan*/  phydm_sys_up_time; struct rtl_sta_info** odm_sta_info; scalar_t__* channel; scalar_t__ control_channel; } ;

/* Variables and functions */
 scalar_t__ IS_STA_VALID (struct rtl_sta_info*) ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 scalar_t__ ODM_BW40M ; 
 int /*<<< orphan*/  odm_update_mp_driver_status (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_traffic_load_decision (struct phy_dm_struct*) ; 

__attribute__((used)) static void odm_common_info_self_update(struct phy_dm_struct *dm)
{
	u8 entry_cnt = 0, num_active_client = 0;
	u32 i, one_entry_macid = 0;
	struct rtl_sta_info *entry;

	/* THis variable cannot be used because it is wrong*/
	if (*dm->band_width == ODM_BW40M) {
		if (*dm->sec_ch_offset == 1)
			dm->control_channel = *dm->channel - 2;
		else if (*dm->sec_ch_offset == 2)
			dm->control_channel = *dm->channel + 2;
	} else {
		dm->control_channel = *dm->channel;
	}

	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) {
		entry = dm->odm_sta_info[i];
		if (IS_STA_VALID(entry)) {
			entry_cnt++;
			if (entry_cnt == 1)
				one_entry_macid = i;
		}
	}

	if (entry_cnt == 1) {
		dm->is_one_entry_only = true;
		dm->one_entry_macid = one_entry_macid;
	} else {
		dm->is_one_entry_only = false;
	}

	dm->pre_number_linked_client = dm->number_linked_client;
	dm->pre_number_active_client = dm->number_active_client;

	dm->number_linked_client = entry_cnt;
	dm->number_active_client = num_active_client;

	/* Update MP driver status*/
	odm_update_mp_driver_status(dm);

	/*Traffic load information update*/
	phydm_traffic_load_decision(dm);

	dm->phydm_sys_up_time += dm->phydm_period;
}