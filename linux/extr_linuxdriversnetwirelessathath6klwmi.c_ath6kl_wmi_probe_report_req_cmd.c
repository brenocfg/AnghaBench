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
struct wmi_probe_req_report_cmd {int enable; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_PROBE_REQ_REPORT_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_probe_report_req_cmd(struct wmi *wmi, u8 if_idx, bool enable)
{
	struct sk_buff *skb;
	struct wmi_probe_req_report_cmd *p;

	skb = ath6kl_wmi_get_new_buf(sizeof(*p));
	if (!skb)
		return -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "probe_report_req_cmd: enable=%u\n",
		   enable);
	p = (struct wmi_probe_req_report_cmd *) skb->data;
	p->enable = enable ? 1 : 0;
	return ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_PROBE_REQ_REPORT_CMDID,
				   NO_SYNC_WMIFLAG);
}