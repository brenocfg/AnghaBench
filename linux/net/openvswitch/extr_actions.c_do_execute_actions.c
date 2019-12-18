#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sw_flow_key {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct ovs_action_trunc {scalar_t__ max_len; } ;
struct nshhdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct datapath {int dummy; } ;
struct TYPE_2__ {scalar_t__ cutlen; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NSH_HDR_MAX_LEN ; 
#define  OVS_ACTION_ATTR_CHECK_PKT_LEN 149 
#define  OVS_ACTION_ATTR_CLONE 148 
#define  OVS_ACTION_ATTR_CT 147 
#define  OVS_ACTION_ATTR_CT_CLEAR 146 
#define  OVS_ACTION_ATTR_HASH 145 
#define  OVS_ACTION_ATTR_METER 144 
#define  OVS_ACTION_ATTR_OUTPUT 143 
#define  OVS_ACTION_ATTR_POP_ETH 142 
#define  OVS_ACTION_ATTR_POP_MPLS 141 
#define  OVS_ACTION_ATTR_POP_NSH 140 
#define  OVS_ACTION_ATTR_POP_VLAN 139 
#define  OVS_ACTION_ATTR_PUSH_ETH 138 
#define  OVS_ACTION_ATTR_PUSH_MPLS 137 
#define  OVS_ACTION_ATTR_PUSH_NSH 136 
#define  OVS_ACTION_ATTR_PUSH_VLAN 135 
#define  OVS_ACTION_ATTR_RECIRC 134 
#define  OVS_ACTION_ATTR_SAMPLE 133 
#define  OVS_ACTION_ATTR_SET 132 
#define  OVS_ACTION_ATTR_SET_MASKED 131 
#define  OVS_ACTION_ATTR_SET_TO_MASKED 130 
#define  OVS_ACTION_ATTR_TRUNC 129 
#define  OVS_ACTION_ATTR_USERSPACE 128 
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 int clone (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  do_output (struct datapath*,struct sk_buff*,int,struct sw_flow_key*) ; 
 int execute_check_pkt_len (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 int /*<<< orphan*/  execute_hash (struct sk_buff*,struct sw_flow_key*,struct nlattr const*) ; 
 int execute_masked_set_action (struct sk_buff*,struct sw_flow_key*,struct ovs_action_trunc*) ; 
 int execute_recirc (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 int execute_set_action (struct sk_buff*,struct sw_flow_key*,struct ovs_action_trunc*) ; 
 int /*<<< orphan*/  is_flow_key_valid (struct sw_flow_key*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ovs_action_trunc* nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr const*) ; 
 int nla_get_u32 (struct nlattr const*) ; 
 int nla_is_last (struct nlattr const*,int) ; 
 struct nlattr* nla_next (struct nlattr const*,int*) ; 
 int nla_type (struct nlattr const*) ; 
 int nsh_hdr_from_nlattr (struct ovs_action_trunc*,struct nshhdr*,int) ; 
 int /*<<< orphan*/  output_userspace (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,struct nlattr const*,int,scalar_t__) ; 
 int ovs_ct_clear (struct sk_buff*,struct sw_flow_key*) ; 
 int ovs_ct_execute (int /*<<< orphan*/ ,struct sk_buff*,struct sw_flow_key*,struct ovs_action_trunc*) ; 
 int /*<<< orphan*/  ovs_dp_get_net (struct datapath*) ; 
 int ovs_flow_key_update (struct sk_buff*,struct sw_flow_key*) ; 
 int /*<<< orphan*/  ovs_meter_execute (struct datapath*,struct sk_buff*,struct sw_flow_key*,int) ; 
 int pop_eth (struct sk_buff*,struct sw_flow_key*) ; 
 int pop_mpls (struct sk_buff*,struct sw_flow_key*,int /*<<< orphan*/ ) ; 
 int pop_nsh (struct sk_buff*,struct sw_flow_key*) ; 
 int pop_vlan (struct sk_buff*,struct sw_flow_key*) ; 
 int push_eth (struct sk_buff*,struct sw_flow_key*,struct ovs_action_trunc*) ; 
 int push_mpls (struct sk_buff*,struct sw_flow_key*,struct ovs_action_trunc*) ; 
 int push_nsh (struct sk_buff*,struct sw_flow_key*,struct nshhdr*) ; 
 int push_vlan (struct sk_buff*,struct sw_flow_key*,struct ovs_action_trunc*) ; 
 int sample (struct datapath*,struct sk_buff*,struct sw_flow_key*,struct nlattr const*,int) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_execute_actions(struct datapath *dp, struct sk_buff *skb,
			      struct sw_flow_key *key,
			      const struct nlattr *attr, int len)
{
	const struct nlattr *a;
	int rem;

	for (a = attr, rem = len; rem > 0;
	     a = nla_next(a, &rem)) {
		int err = 0;

		switch (nla_type(a)) {
		case OVS_ACTION_ATTR_OUTPUT: {
			int port = nla_get_u32(a);
			struct sk_buff *clone;

			/* Every output action needs a separate clone
			 * of 'skb', In case the output action is the
			 * last action, cloning can be avoided.
			 */
			if (nla_is_last(a, rem)) {
				do_output(dp, skb, port, key);
				/* 'skb' has been used for output.
				 */
				return 0;
			}

			clone = skb_clone(skb, GFP_ATOMIC);
			if (clone)
				do_output(dp, clone, port, key);
			OVS_CB(skb)->cutlen = 0;
			break;
		}

		case OVS_ACTION_ATTR_TRUNC: {
			struct ovs_action_trunc *trunc = nla_data(a);

			if (skb->len > trunc->max_len)
				OVS_CB(skb)->cutlen = skb->len - trunc->max_len;
			break;
		}

		case OVS_ACTION_ATTR_USERSPACE:
			output_userspace(dp, skb, key, a, attr,
						     len, OVS_CB(skb)->cutlen);
			OVS_CB(skb)->cutlen = 0;
			break;

		case OVS_ACTION_ATTR_HASH:
			execute_hash(skb, key, a);
			break;

		case OVS_ACTION_ATTR_PUSH_MPLS:
			err = push_mpls(skb, key, nla_data(a));
			break;

		case OVS_ACTION_ATTR_POP_MPLS:
			err = pop_mpls(skb, key, nla_get_be16(a));
			break;

		case OVS_ACTION_ATTR_PUSH_VLAN:
			err = push_vlan(skb, key, nla_data(a));
			break;

		case OVS_ACTION_ATTR_POP_VLAN:
			err = pop_vlan(skb, key);
			break;

		case OVS_ACTION_ATTR_RECIRC: {
			bool last = nla_is_last(a, rem);

			err = execute_recirc(dp, skb, key, a, last);
			if (last) {
				/* If this is the last action, the skb has
				 * been consumed or freed.
				 * Return immediately.
				 */
				return err;
			}
			break;
		}

		case OVS_ACTION_ATTR_SET:
			err = execute_set_action(skb, key, nla_data(a));
			break;

		case OVS_ACTION_ATTR_SET_MASKED:
		case OVS_ACTION_ATTR_SET_TO_MASKED:
			err = execute_masked_set_action(skb, key, nla_data(a));
			break;

		case OVS_ACTION_ATTR_SAMPLE: {
			bool last = nla_is_last(a, rem);

			err = sample(dp, skb, key, a, last);
			if (last)
				return err;

			break;
		}

		case OVS_ACTION_ATTR_CT:
			if (!is_flow_key_valid(key)) {
				err = ovs_flow_key_update(skb, key);
				if (err)
					return err;
			}

			err = ovs_ct_execute(ovs_dp_get_net(dp), skb, key,
					     nla_data(a));

			/* Hide stolen IP fragments from user space. */
			if (err)
				return err == -EINPROGRESS ? 0 : err;
			break;

		case OVS_ACTION_ATTR_CT_CLEAR:
			err = ovs_ct_clear(skb, key);
			break;

		case OVS_ACTION_ATTR_PUSH_ETH:
			err = push_eth(skb, key, nla_data(a));
			break;

		case OVS_ACTION_ATTR_POP_ETH:
			err = pop_eth(skb, key);
			break;

		case OVS_ACTION_ATTR_PUSH_NSH: {
			u8 buffer[NSH_HDR_MAX_LEN];
			struct nshhdr *nh = (struct nshhdr *)buffer;

			err = nsh_hdr_from_nlattr(nla_data(a), nh,
						  NSH_HDR_MAX_LEN);
			if (unlikely(err))
				break;
			err = push_nsh(skb, key, nh);
			break;
		}

		case OVS_ACTION_ATTR_POP_NSH:
			err = pop_nsh(skb, key);
			break;

		case OVS_ACTION_ATTR_METER:
			if (ovs_meter_execute(dp, skb, key, nla_get_u32(a))) {
				consume_skb(skb);
				return 0;
			}
			break;

		case OVS_ACTION_ATTR_CLONE: {
			bool last = nla_is_last(a, rem);

			err = clone(dp, skb, key, a, last);
			if (last)
				return err;

			break;
		}

		case OVS_ACTION_ATTR_CHECK_PKT_LEN: {
			bool last = nla_is_last(a, rem);

			err = execute_check_pkt_len(dp, skb, key, a, last);
			if (last)
				return err;

			break;
		}
		}

		if (unlikely(err)) {
			kfree_skb(skb);
			return err;
		}
	}

	consume_skb(skb);
	return 0;
}