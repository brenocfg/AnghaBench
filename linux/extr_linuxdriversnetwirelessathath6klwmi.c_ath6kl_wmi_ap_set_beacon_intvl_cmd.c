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
typedef  int /*<<< orphan*/  u32 ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct set_beacon_int_cmd {int /*<<< orphan*/  beacon_intvl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_BEACON_INT_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_ap_set_beacon_intvl_cmd(struct wmi *wmi, u8 if_idx,
				       u32 beacon_intvl)
{
	struct sk_buff *skb;
	struct set_beacon_int_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct set_beacon_int_cmd *) skb->data;

	cmd->beacon_intvl = cpu_to_le32(beacon_intvl);
	return ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				   WMI_SET_BEACON_INT_CMDID, NO_SYNC_WMIFLAG);
}