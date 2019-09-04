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
struct wmi_set_wmm_txop_cmd {int txop_enable; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
typedef  enum wmi_txop_cfg { ____Placeholder_wmi_txop_cfg } wmi_txop_cfg ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_WMM_TXOP_CMDID ; 
 int WMI_TXOP_DISABLED ; 
 int WMI_TXOP_ENABLED ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_set_wmm_txop(struct wmi *wmi, u8 if_idx, enum wmi_txop_cfg cfg)
{
	struct sk_buff *skb;
	struct wmi_set_wmm_txop_cmd *cmd;
	int ret;

	if (!((cfg == WMI_TXOP_DISABLED) || (cfg == WMI_TXOP_ENABLED)))
		return -EINVAL;

	skb = ath6kl_wmi_get_new_buf(sizeof(struct wmi_set_wmm_txop_cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_set_wmm_txop_cmd *) skb->data;
	cmd->txop_enable = cfg;

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SET_WMM_TXOP_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}