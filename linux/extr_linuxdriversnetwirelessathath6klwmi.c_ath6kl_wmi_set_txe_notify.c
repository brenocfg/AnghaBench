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
struct wmi_txe_notify_cmd {void* intvl; void* pkts; void* rate; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_TXE_NOTIFY_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_set_txe_notify(struct wmi *wmi, u8 idx,
			      u32 rate, u32 pkts, u32 intvl)
{
	struct sk_buff *skb;
	struct wmi_txe_notify_cmd *cmd;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_txe_notify_cmd *) skb->data;
	cmd->rate = cpu_to_le32(rate);
	cmd->pkts = cpu_to_le32(pkts);
	cmd->intvl = cpu_to_le32(intvl);

	return ath6kl_wmi_cmd_send(wmi, idx, skb, WMI_SET_TXE_NOTIFY_CMDID,
				   NO_SYNC_WMIFLAG);
}