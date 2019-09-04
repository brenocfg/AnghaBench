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
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int roam_mode; } ;
struct roam_ctrl_cmd {int /*<<< orphan*/  roam_ctrl; TYPE_1__ info; } ;
typedef  enum wmi_roam_mode { ____Placeholder_wmi_roam_mode } wmi_roam_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_ROAM_CTRL_CMDID ; 
 int /*<<< orphan*/  WMI_SET_ROAM_MODE ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_set_roam_mode_cmd(struct wmi *wmi, enum wmi_roam_mode mode)
{
	struct sk_buff *skb;
	struct roam_ctrl_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct roam_ctrl_cmd *) skb->data;

	cmd->info.roam_mode = mode;
	cmd->roam_ctrl = WMI_SET_ROAM_MODE;

	ath6kl_dbg(ATH6KL_DBG_WMI, "set roam mode %d\n", mode);
	return ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_ROAM_CTRL_CMDID,
				   NO_SYNC_WMIFLAG);
}