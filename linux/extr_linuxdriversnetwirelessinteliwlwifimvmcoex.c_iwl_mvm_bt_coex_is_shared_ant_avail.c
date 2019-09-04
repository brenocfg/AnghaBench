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
struct TYPE_4__ {int /*<<< orphan*/  bt_activity_grading; } ;
struct iwl_mvm {TYPE_2__ last_bt_notif; TYPE_1__* cfg; } ;
struct TYPE_3__ {scalar_t__ bt_shared_single_ant; } ;

/* Variables and functions */
 scalar_t__ BT_HIGH_TRAFFIC ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

bool iwl_mvm_bt_coex_is_shared_ant_avail(struct iwl_mvm *mvm)
{
	/* there is no other antenna, shared antenna is always available */
	if (mvm->cfg->bt_shared_single_ant)
		return true;

	return le32_to_cpu(mvm->last_bt_notif.bt_activity_grading) < BT_HIGH_TRAFFIC;
}