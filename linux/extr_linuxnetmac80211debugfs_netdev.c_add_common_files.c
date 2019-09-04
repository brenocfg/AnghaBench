#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sub_if_data {TYPE_2__* local; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ wake_tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aqm ; 
 int /*<<< orphan*/  hw_queues ; 
 int /*<<< orphan*/  rc_rateidx_mask_2ghz ; 
 int /*<<< orphan*/  rc_rateidx_mask_5ghz ; 
 int /*<<< orphan*/  rc_rateidx_mcs_mask_2ghz ; 
 int /*<<< orphan*/  rc_rateidx_mcs_mask_5ghz ; 
 int /*<<< orphan*/  rc_rateidx_vht_mcs_mask_2ghz ; 
 int /*<<< orphan*/  rc_rateidx_vht_mcs_mask_5ghz ; 

__attribute__((used)) static void add_common_files(struct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(rc_rateidx_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_mask_5ghz);
	DEBUGFS_ADD(rc_rateidx_mcs_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_mcs_mask_5ghz);
	DEBUGFS_ADD(rc_rateidx_vht_mcs_mask_2ghz);
	DEBUGFS_ADD(rc_rateidx_vht_mcs_mask_5ghz);
	DEBUGFS_ADD(hw_queues);

	if (sdata->local->ops->wake_tx_queue)
		DEBUGFS_ADD(aqm);
}