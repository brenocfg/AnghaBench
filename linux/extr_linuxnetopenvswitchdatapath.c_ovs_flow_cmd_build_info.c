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
typedef  int /*<<< orphan*/  u32 ;
struct sw_flow {int /*<<< orphan*/  id; int /*<<< orphan*/  sf_acts; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct sk_buff*) ; 
 struct sk_buff* ovs_flow_cmd_alloc_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct genl_info*,int,int /*<<< orphan*/ ) ; 
 int ovs_flow_cmd_fill_info (struct sw_flow const*,int,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovsl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ovs_flow_cmd_build_info(const struct sw_flow *flow,
					       int dp_ifindex,
					       struct genl_info *info, u8 cmd,
					       bool always, u32 ufid_flags)
{
	struct sk_buff *skb;
	int retval;

	skb = ovs_flow_cmd_alloc_info(ovsl_dereference(flow->sf_acts),
				      &flow->id, info, always, ufid_flags);
	if (IS_ERR_OR_NULL(skb))
		return skb;

	retval = ovs_flow_cmd_fill_info(flow, dp_ifindex, skb,
					info->snd_portid, info->snd_seq, 0,
					cmd, ufid_flags);
	BUG_ON(retval < 0);
	return skb;
}