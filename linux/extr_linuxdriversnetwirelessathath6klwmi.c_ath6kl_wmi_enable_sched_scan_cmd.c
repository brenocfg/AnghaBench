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
struct wmi_enable_sched_scan_cmd {int enable; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_ENABLE_SCHED_SCAN_CMDID ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 

int ath6kl_wmi_enable_sched_scan_cmd(struct wmi *wmi, u8 if_idx, bool enable)
{
	struct sk_buff *skb;
	struct wmi_enable_sched_scan_cmd *sc;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(*sc));
	if (!skb)
		return -ENOMEM;

	ath6kl_dbg(ATH6KL_DBG_WMI, "%s scheduled scan on vif %d\n",
		   enable ? "enabling" : "disabling", if_idx);
	sc = (struct wmi_enable_sched_scan_cmd *) skb->data;
	sc->enable = enable ? 1 : 0;

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb,
				  WMI_ENABLE_SCHED_SCAN_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}