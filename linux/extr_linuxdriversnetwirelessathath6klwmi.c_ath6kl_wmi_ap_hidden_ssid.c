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
struct wmi_ap_hidden_ssid_cmd {int hidden_ssid; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_AP_HIDDEN_SSID_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_ap_hidden_ssid(struct wmi *wmi, u8 if_idx, bool enable)
{
	struct sk_buff *skb;
	struct wmi_ap_hidden_ssid_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_ap_hidden_ssid_cmd *) skb->data;
	cmd->hidden_ssid = enable ? 1 : 0;

	return ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_AP_HIDDEN_SSID_CMDID,
				   NO_SYNC_WMIFLAG);
}