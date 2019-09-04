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
typedef  int u8 ;
struct wmi_mcast_filter_add_del_cmd {int /*<<< orphan*/  mcast_mac; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_DEL_MCAST_FILTER_CMDID ; 
 int /*<<< orphan*/  WMI_SET_MCAST_FILTER_CMDID ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int ath6kl_wmi_add_del_mcast_filter_cmd(struct wmi *wmi, u8 if_idx,
					u8 *filter, bool add_filter)
{
	struct sk_buff *skb;
	struct wmi_mcast_filter_add_del_cmd *cmd;
	int ret;

	if ((filter[0] != 0x33 || filter[1] != 0x33) &&
	    (filter[0] != 0x01 || filter[1] != 0x00 ||
	    filter[2] != 0x5e || filter[3] > 0x7f)) {
		ath6kl_warn("invalid multicast filter address\n");
		return -EINVAL;
	}

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_mcast_filter_add_del_cmd *) skb->data;
	memcpy(cmd->mcast_mac, filter, ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE);
	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				  add_filter ? WMI_SET_MCAST_FILTER_CMDID :
				  WMI_DEL_MCAST_FILTER_CMDID,
				  NO_SYNC_WMIFLAG);

	return ret;
}