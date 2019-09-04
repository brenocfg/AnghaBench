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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_pdev_set_quiet_cmd {void* enabled; void* next_start; void* duration; void* period; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_pdev_set_quiet_mode(struct ath10k *ar, u32 period,
				      u32 duration, u32 next_offset,
				      u32 enabled)
{
	struct wmi_pdev_set_quiet_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_pdev_set_quiet_cmd *)skb->data;
	cmd->period = __cpu_to_le32(period);
	cmd->duration = __cpu_to_le32(duration);
	cmd->next_start = __cpu_to_le32(next_offset);
	cmd->enabled = __cpu_to_le32(enabled);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi quiet param: period %u duration %u enabled %d\n",
		   period, duration, enabled);
	return skb;
}