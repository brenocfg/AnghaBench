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
struct wmi_rx_frame_format_cmd {int dot11_hdr; int defrag_on_host; int /*<<< orphan*/  meta_ver; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_RX_FRAME_FORMAT_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_set_rx_frame_format_cmd(struct wmi *wmi, u8 if_idx,
				       u8 rx_meta_ver,
				       bool rx_dot11_hdr, bool defrag_on_host)
{
	struct sk_buff *skb;
	struct wmi_rx_frame_format_cmd *cmd;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(*cmd));
	if (!skb)
		return -ENOMEM;

	cmd = (struct wmi_rx_frame_format_cmd *) skb->data;
	cmd->dot11_hdr = rx_dot11_hdr ? 1 : 0;
	cmd->defrag_on_host = defrag_on_host ? 1 : 0;
	cmd->meta_ver = rx_meta_ver;

	/* Delete the local aggr state, on host */
	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_RX_FRAME_FORMAT_CMDID,
				  NO_SYNC_WMIFLAG);

	return ret;
}