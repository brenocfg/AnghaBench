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
typedef  int /*<<< orphan*/  u8 ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct roam_ctrl_cmd {int /*<<< orphan*/  roam_ctrl; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_FORCE_ROAM ; 
 int /*<<< orphan*/  WMI_SET_ROAM_CTRL_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ath6kl_wmi_force_roam_cmd(struct wmi *wmi, const u8 *bssid)
{
	struct sk_buff *skb;
	struct roam_ctrl_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct roam_ctrl_cmd *) skb->data;

	memcpy(cmd->info.bssid, bssid, ETH_ALEN);
	cmd->roam_ctrl = WMI_FORCE_ROAM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "force roam to %pM\n", bssid);
	return ath6kl_wmi_cmd_send(wmi, 0, skb, WMI_SET_ROAM_CTRL_CMDID,
				   NO_SYNC_WMIFLAG);
}