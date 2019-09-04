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
struct TYPE_2__ {void* length; void* code; } ;
struct mwl8k_cmd_set_slot {int short_slot; TYPE_1__ header; void* action; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET ; 
 int MWL8K_CMD_SET_SLOT ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_slot*) ; 
 struct mwl8k_cmd_set_slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_set_slot(struct ieee80211_hw *hw, bool short_slot_time)
{
	struct mwl8k_cmd_set_slot *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_SLOT);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->short_slot = short_slot_time;

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}