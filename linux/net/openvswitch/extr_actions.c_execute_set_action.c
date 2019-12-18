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
struct sw_flow_key {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ovs_tunnel_info {scalar_t__ tun_dst; } ;
struct nlattr {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OVS_KEY_ATTR_TUNNEL_INFO ; 
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 struct ovs_tunnel_info* nla_data (struct nlattr const*) ; 
 scalar_t__ nla_type (struct nlattr const*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 

__attribute__((used)) static int execute_set_action(struct sk_buff *skb,
			      struct sw_flow_key *flow_key,
			      const struct nlattr *a)
{
	/* Only tunnel set execution is supported without a mask. */
	if (nla_type(a) == OVS_KEY_ATTR_TUNNEL_INFO) {
		struct ovs_tunnel_info *tun = nla_data(a);

		skb_dst_drop(skb);
		dst_hold((struct dst_entry *)tun->tun_dst);
		skb_dst_set(skb, (struct dst_entry *)tun->tun_dst);
		return 0;
	}

	return -EINVAL;
}