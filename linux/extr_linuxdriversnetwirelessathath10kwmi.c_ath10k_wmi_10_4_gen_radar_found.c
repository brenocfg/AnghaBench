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
struct wmi_radar_found_info {void* sidx_max; void* sidx_min; void* width_max; void* width_min; void* pri_max; void* pri_min; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k_radar_found_info {int /*<<< orphan*/  sidx_max; int /*<<< orphan*/  sidx_min; int /*<<< orphan*/  width_max; int /*<<< orphan*/  width_min; int /*<<< orphan*/  pri_max; int /*<<< orphan*/  pri_min; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_10_4_gen_radar_found(struct ath10k *ar,
				const struct ath10k_radar_found_info *arg)
{
	struct wmi_radar_found_info *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_radar_found_info *)skb->data;
	cmd->pri_min   = __cpu_to_le32(arg->pri_min);
	cmd->pri_max   = __cpu_to_le32(arg->pri_max);
	cmd->width_min = __cpu_to_le32(arg->width_min);
	cmd->width_max = __cpu_to_le32(arg->width_max);
	cmd->sidx_min  = __cpu_to_le32(arg->sidx_min);
	cmd->sidx_max  = __cpu_to_le32(arg->sidx_max);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi radar found pri_min %d pri_max %d width_min %d width_max %d sidx_min %d sidx_max %d\n",
		   arg->pri_min, arg->pri_max, arg->width_min,
		   arg->width_max, arg->sidx_min, arg->sidx_max);
	return skb;
}