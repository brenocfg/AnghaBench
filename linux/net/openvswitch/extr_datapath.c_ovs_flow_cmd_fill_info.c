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
struct sw_flow {int /*<<< orphan*/  id; } ;
struct sk_buff {int len; } ;
struct ovs_header {int dp_ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  dp_flow_genl_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,struct ovs_header*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,struct ovs_header*) ; 
 struct ovs_header* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_flow_cmd_fill_actions (struct sw_flow const*,struct sk_buff*,int const) ; 
 int ovs_flow_cmd_fill_stats (struct sw_flow const*,struct sk_buff*) ; 
 int ovs_nla_put_identifier (struct sw_flow const*,struct sk_buff*) ; 
 int ovs_nla_put_mask (struct sw_flow const*,struct sk_buff*) ; 
 int ovs_nla_put_masked_key (struct sw_flow const*,struct sk_buff*) ; 
 scalar_t__ should_fill_actions (int /*<<< orphan*/ ) ; 
 scalar_t__ should_fill_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ should_fill_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovs_flow_cmd_fill_info(const struct sw_flow *flow, int dp_ifindex,
				  struct sk_buff *skb, u32 portid,
				  u32 seq, u32 flags, u8 cmd, u32 ufid_flags)
{
	const int skb_orig_len = skb->len;
	struct ovs_header *ovs_header;
	int err;

	ovs_header = genlmsg_put(skb, portid, seq, &dp_flow_genl_family,
				 flags, cmd);
	if (!ovs_header)
		return -EMSGSIZE;

	ovs_header->dp_ifindex = dp_ifindex;

	err = ovs_nla_put_identifier(flow, skb);
	if (err)
		goto error;

	if (should_fill_key(&flow->id, ufid_flags)) {
		err = ovs_nla_put_masked_key(flow, skb);
		if (err)
			goto error;
	}

	if (should_fill_mask(ufid_flags)) {
		err = ovs_nla_put_mask(flow, skb);
		if (err)
			goto error;
	}

	err = ovs_flow_cmd_fill_stats(flow, skb);
	if (err)
		goto error;

	if (should_fill_actions(ufid_flags)) {
		err = ovs_flow_cmd_fill_actions(flow, skb, skb_orig_len);
		if (err)
			goto error;
	}

	genlmsg_end(skb, ovs_header);
	return 0;

error:
	genlmsg_cancel(skb, ovs_header);
	return err;
}