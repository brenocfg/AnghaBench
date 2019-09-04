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
struct iwl_mvm {int dummy; } ;
struct iwl_mu_group_mgmt_cmd {int /*<<< orphan*/  user_position; int /*<<< orphan*/  membership_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  position; int /*<<< orphan*/  membership; } ;
struct TYPE_4__ {TYPE_1__ mu_group; } ;
struct ieee80211_vif {TYPE_2__ bss_conf; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PATH_GROUP ; 
 int /*<<< orphan*/  UPDATE_MU_GROUPS_CMD ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_MEMBERSHIP_LEN ; 
 int /*<<< orphan*/  WLAN_USER_POSITION_LEN ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mu_group_mgmt_cmd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_update_mu_groups(struct iwl_mvm *mvm,
				    struct ieee80211_vif *vif)
{
	struct iwl_mu_group_mgmt_cmd cmd = {};

	memcpy(cmd.membership_status, vif->bss_conf.mu_group.membership,
	       WLAN_MEMBERSHIP_LEN);
	memcpy(cmd.user_position, vif->bss_conf.mu_group.position,
	       WLAN_USER_POSITION_LEN);

	return iwl_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(DATA_PATH_GROUP,
					    UPDATE_MU_GROUPS_CMD),
				    0, sizeof(cmd), &cmd);
}