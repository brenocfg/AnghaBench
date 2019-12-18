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
struct flow_dissector_key_tags {int /*<<< orphan*/  flow_label; } ;
struct flow_dissector_key_ports {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct flow_dissector_key_control {void* addr_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  thoff; } ;
struct flow_dissector_key_basic {int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct flow_dissector_key_addrs {int /*<<< orphan*/  v6addrs; TYPE_1__ v4addrs; } ;
struct flow_dissector {int dummy; } ;
struct bpf_flow_keys {scalar_t__ addr_proto; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  ipv6_src; int /*<<< orphan*/  ipv4_dst; int /*<<< orphan*/  ipv4_src; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; scalar_t__ is_encap; scalar_t__ is_first_frag; scalar_t__ is_frag; int /*<<< orphan*/  thoff; } ;

/* Variables and functions */
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 void* FLOW_DISSECTOR_KEY_BASIC ; 
 void* FLOW_DISSECTOR_KEY_CONTROL ; 
 void* FLOW_DISSECTOR_KEY_FLOW_LABEL ; 
 void* FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 void* FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 void* FLOW_DISSECTOR_KEY_PORTS ; 
 int /*<<< orphan*/  FLOW_DIS_ENCAPSULATION ; 
 int /*<<< orphan*/  FLOW_DIS_FIRST_FRAG ; 
 int /*<<< orphan*/  FLOW_DIS_IS_FRAGMENT ; 
 scalar_t__ dissector_uses_key (struct flow_dissector*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (struct flow_dissector*,void*,void*) ; 

__attribute__((used)) static void __skb_flow_bpf_to_target(const struct bpf_flow_keys *flow_keys,
				     struct flow_dissector *flow_dissector,
				     void *target_container)
{
	struct flow_dissector_key_control *key_control;
	struct flow_dissector_key_basic *key_basic;
	struct flow_dissector_key_addrs *key_addrs;
	struct flow_dissector_key_ports *key_ports;
	struct flow_dissector_key_tags *key_tags;

	key_control = skb_flow_dissector_target(flow_dissector,
						FLOW_DISSECTOR_KEY_CONTROL,
						target_container);
	key_control->thoff = flow_keys->thoff;
	if (flow_keys->is_frag)
		key_control->flags |= FLOW_DIS_IS_FRAGMENT;
	if (flow_keys->is_first_frag)
		key_control->flags |= FLOW_DIS_FIRST_FRAG;
	if (flow_keys->is_encap)
		key_control->flags |= FLOW_DIS_ENCAPSULATION;

	key_basic = skb_flow_dissector_target(flow_dissector,
					      FLOW_DISSECTOR_KEY_BASIC,
					      target_container);
	key_basic->n_proto = flow_keys->n_proto;
	key_basic->ip_proto = flow_keys->ip_proto;

	if (flow_keys->addr_proto == ETH_P_IP &&
	    dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) {
		key_addrs = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						      target_container);
		key_addrs->v4addrs.src = flow_keys->ipv4_src;
		key_addrs->v4addrs.dst = flow_keys->ipv4_dst;
		key_control->addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
	} else if (flow_keys->addr_proto == ETH_P_IPV6 &&
		   dissector_uses_key(flow_dissector,
				      FLOW_DISSECTOR_KEY_IPV6_ADDRS)) {
		key_addrs = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						      target_container);
		memcpy(&key_addrs->v6addrs, &flow_keys->ipv6_src,
		       sizeof(key_addrs->v6addrs));
		key_control->addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
	}

	if (dissector_uses_key(flow_dissector, FLOW_DISSECTOR_KEY_PORTS)) {
		key_ports = skb_flow_dissector_target(flow_dissector,
						      FLOW_DISSECTOR_KEY_PORTS,
						      target_container);
		key_ports->src = flow_keys->sport;
		key_ports->dst = flow_keys->dport;
	}

	if (dissector_uses_key(flow_dissector,
			       FLOW_DISSECTOR_KEY_FLOW_LABEL)) {
		key_tags = skb_flow_dissector_target(flow_dissector,
						     FLOW_DISSECTOR_KEY_FLOW_LABEL,
						     target_container);
		key_tags->flow_label = ntohl(flow_keys->flow_label);
	}
}