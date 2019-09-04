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
struct mwl8k_cmd_set_rate_adapt_mode {TYPE_1__ header; void* mode; void* action; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MWL8K_CMD_SET ; 
 int MWL8K_CMD_SET_RATEADAPT_MODE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct mwl8k_cmd_set_rate_adapt_mode*) ; 
 struct mwl8k_cmd_set_rate_adapt_mode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mwl8k_post_cmd (struct ieee80211_hw*,TYPE_1__*) ; 

__attribute__((used)) static int mwl8k_cmd_set_rateadapt_mode(struct ieee80211_hw *hw, __u16 mode)
{
	struct mwl8k_cmd_set_rate_adapt_mode *cmd;
	int rc;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	cmd->header.code = cpu_to_le16(MWL8K_CMD_SET_RATEADAPT_MODE);
	cmd->header.length = cpu_to_le16(sizeof(*cmd));
	cmd->action = cpu_to_le16(MWL8K_CMD_SET);
	cmd->mode = cpu_to_le16(mode);

	rc = mwl8k_post_cmd(hw, &cmd->header);
	kfree(cmd);

	return rc;
}