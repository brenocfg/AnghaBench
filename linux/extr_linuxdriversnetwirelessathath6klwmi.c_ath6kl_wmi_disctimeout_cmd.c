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
struct wmi_disc_timeout_cmd {int /*<<< orphan*/  discon_timeout; } ;
struct wmi {int /*<<< orphan*/  parent_dev; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_DISC_TIMEOUT_CMDID ; 
 int /*<<< orphan*/  ath6kl_debug_set_disconnect_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_disctimeout_cmd(struct wmi *wmi, u8 if_idx, u8 timeout)
{
	struct sk_buff *skb;
	struct wmi_disc_timeout_cmd *cmd;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_disc_timeout_cmd *) skb->data;
	cmd->discon_timeout = timeout;

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SET_DISC_TIMEOUT_CMDID,
				  NO_SYNC_WMIFLAG);

	if (ret == 0)
		ath6kl_debug_set_disconnect_timeout(wmi->parent_dev, timeout);

	return ret;
}