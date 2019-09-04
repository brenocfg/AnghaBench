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
struct wmi_tlv_mgmt_tx_compl_ev_arg {int /*<<< orphan*/  status; int /*<<< orphan*/  desc_id; } ;
struct sk_buff {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_pull_mgmt_tx_compl (struct ath10k*,struct sk_buff*,struct wmi_tlv_mgmt_tx_compl_ev_arg*) ; 
 int /*<<< orphan*/  wmi_process_mgmt_tx_comp (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_wmi_event_mgmt_tx_compl(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_tlv_mgmt_tx_compl_ev_arg arg;
	int ret;

	ret = ath10k_wmi_pull_mgmt_tx_compl(ar, skb, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to parse mgmt comp event: %d\n", ret);
		return ret;
	}

	wmi_process_mgmt_tx_comp(ar, __le32_to_cpu(arg.desc_id),
				 __le32_to_cpu(arg.status));

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv evnt mgmt tx completion\n");

	return 0;
}