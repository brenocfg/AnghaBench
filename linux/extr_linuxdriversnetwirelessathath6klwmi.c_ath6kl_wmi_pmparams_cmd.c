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
struct wmi_power_params_cmd {void* ps_fail_event_policy; void* num_tx_to_wakeup; void* tx_wakeup_policy; void* dtim_policy; void* pspoll_number; void* idle_period; } ;
struct wmi {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 int /*<<< orphan*/  WMI_SET_POWER_PARAMS_CMDID ; 
 int ath6kl_wmi_cmd_send (struct wmi*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath6kl_wmi_get_new_buf (int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

int ath6kl_wmi_pmparams_cmd(struct wmi *wmi, u8 if_idx, u16 idle_period,
			    u16 ps_poll_num, u16 dtim_policy,
			    u16 tx_wakeup_policy, u16 num_tx_to_wakeup,
			    u16 ps_fail_event_policy)
{
	struct sk_buff *skb;
	struct wmi_power_params_cmd *pm;
	int ret;

	skb = ath6kl_wmi_get_new_buf(sizeof(*pm));
	if (!skb)
		return -ENOMEM;

	pm = (struct wmi_power_params_cmd *)skb->data;
	pm->idle_period = cpu_to_le16(idle_period);
	pm->pspoll_number = cpu_to_le16(ps_poll_num);
	pm->dtim_policy = cpu_to_le16(dtim_policy);
	pm->tx_wakeup_policy = cpu_to_le16(tx_wakeup_policy);
	pm->num_tx_to_wakeup = cpu_to_le16(num_tx_to_wakeup);
	pm->ps_fail_event_policy = cpu_to_le16(ps_fail_event_policy);

	ret = ath6kl_wmi_cmd_send(wmi, if_idx, skb, WMI_SET_POWER_PARAMS_CMDID,
				  NO_SYNC_WMIFLAG);
	return ret;
}