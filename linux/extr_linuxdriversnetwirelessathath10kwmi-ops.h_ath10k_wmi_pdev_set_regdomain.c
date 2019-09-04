#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {TYPE_3__* cmd; TYPE_1__* ops; } ;
struct ath10k {TYPE_2__ wmi; } ;
typedef  enum wmi_dfs_region { ____Placeholder_wmi_dfs_region } wmi_dfs_region ;
struct TYPE_6__ {int /*<<< orphan*/  pdev_set_regdomain_cmdid; } ;
struct TYPE_4__ {struct sk_buff* (* gen_pdev_set_rd ) (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
ath10k_wmi_pdev_set_regdomain(struct ath10k *ar, u16 rd, u16 rd2g, u16 rd5g,
			      u16 ctl2g, u16 ctl5g,
			      enum wmi_dfs_region dfs_reg)
{
	struct sk_buff *skb;

	if (!ar->wmi.ops->gen_pdev_set_rd)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_pdev_set_rd(ar, rd, rd2g, rd5g, ctl2g, ctl5g,
					   dfs_reg);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	return ath10k_wmi_cmd_send(ar, skb,
				   ar->wmi.cmd->pdev_set_regdomain_cmdid);
}