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
typedef  int /*<<< orphan*/  uint32_t ;
struct sw_flow_id {int dummy; } ;
struct sw_flow_actions {int dummy; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dp_flow_genl_family ; 
 struct sk_buff* genlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 size_t ovs_flow_cmd_msg_size (struct sw_flow_actions const*,struct sw_flow_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_must_notify (int /*<<< orphan*/ *,struct genl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ovs_flow_cmd_alloc_info(const struct sw_flow_actions *acts,
					       const struct sw_flow_id *sfid,
					       struct genl_info *info,
					       bool always,
					       uint32_t ufid_flags)
{
	struct sk_buff *skb;
	size_t len;

	if (!always && !ovs_must_notify(&dp_flow_genl_family, info, 0))
		return NULL;

	len = ovs_flow_cmd_msg_size(acts, sfid, ufid_flags);
	skb = genlmsg_new(len, GFP_KERNEL);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	return skb;
}