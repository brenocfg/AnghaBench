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
struct wmi_del_wow_pattern_cmd {void* filter_id; void* filter_list_id; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_DEL_WOW_PATTERN_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_del_wow_pattern_cmd(struct wmi *wmi, u8 if_idx,
				   u16 list_id, u16 filter_id)
{
	struct sk_buff *skb;
	struct wmi_del_wow_pattern_cmd *cmd;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_del_wow_pattern_cmd *) skb->data;
	cmd->filter_list_id = cpu_to_le16(list_id);
	cmd->filter_id = cpu_to_le16(filter_id);

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_DEL_WOW_PATTERN_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}