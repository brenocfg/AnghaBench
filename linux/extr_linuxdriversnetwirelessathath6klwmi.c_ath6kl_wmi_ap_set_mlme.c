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
typedef  int /*<<< orphan*/  u16 ;
struct wmi_ap_set_mlme_cmd {int /*<<< orphan*/  reason; int /*<<< orphan*/  cmd; int /*<<< orphan*/  mac; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_AP_SET_MLME_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ath6kl_wmi_ap_set_mlme(struct wmi *wmip, u8 if_idx, u8 cmd, const u8 *mac,
			   u16 reason)
{
	struct sk_buff *skb;
	struct wmi_ap_set_mlme_cmd *cm;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cm));
	if (!skb)
		return -ENOMEM;

	cm = (struct wmi_ap_set_mlme_cmd *) skb->data;
	memcpy(cm->mac, mac, ETH_ALEN);
	cm->reason = cpu_to_le16(reason);
	cm->cmd = cmd;

	ath6kl_dbg(ATH6KL_DBG_WMI, "ap_set_mlme: cmd=%d reason=%d\n", cm->cmd,
		   cm->reason);

	return ath6kl_wmi_cmd_send(wmip, if_idx, skb, WMI_AP_SET_MLME_CMDID,
				   NO_SYNC_WMIFLAG);
}