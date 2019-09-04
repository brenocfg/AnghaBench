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
typedef  int /*<<< orphan*/  u16 ;
struct wmi_pdev_set_regdomain_cmd {void* conformance_test_limit_5G; void* conformance_test_limit_2G; void* reg_domain_5G; void* reg_domain_2G; void* reg_domain; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  enum wmi_dfs_region { ____Placeholder_wmi_dfs_region } wmi_dfs_region ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_op_gen_pdev_set_rd(struct ath10k *ar, u16 rd, u16 rd2g, u16 rd5g,
			      u16 ctl2g, u16 ctl5g,
			      enum wmi_dfs_region dfs_reg)
{
	struct wmi_pdev_set_regdomain_cmd *cmd;
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, sizeof(*cmd));
	if (!skb)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_pdev_set_regdomain_cmd *)skb->data;
	cmd->reg_domain = __cpu_to_le32(rd);
	cmd->reg_domain_2G = __cpu_to_le32(rd2g);
	cmd->reg_domain_5G = __cpu_to_le32(rd5g);
	cmd->conformance_test_limit_2G = __cpu_to_le32(ctl2g);
	cmd->conformance_test_limit_5G = __cpu_to_le32(ctl5g);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi pdev regdomain rd %x rd2g %x rd5g %x ctl2g %x ctl5g %x\n",
		   rd, rd2g, rd5g, ctl2g, ctl5g);
	return skb;
}