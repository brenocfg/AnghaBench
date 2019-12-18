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
struct sk_buff {int dummy; } ;
struct flow_keys {int dummy; } ;

/* Variables and functions */
#define  FLOW_KEY_DST 145 
#define  FLOW_KEY_IIF 144 
#define  FLOW_KEY_MARK 143 
#define  FLOW_KEY_NFCT 142 
#define  FLOW_KEY_NFCT_DST 141 
#define  FLOW_KEY_NFCT_PROTO_DST 140 
#define  FLOW_KEY_NFCT_PROTO_SRC 139 
#define  FLOW_KEY_NFCT_SRC 138 
#define  FLOW_KEY_PRIORITY 137 
#define  FLOW_KEY_PROTO 136 
#define  FLOW_KEY_PROTO_DST 135 
#define  FLOW_KEY_PROTO_SRC 134 
#define  FLOW_KEY_RTCLASSID 133 
#define  FLOW_KEY_RXHASH 132 
#define  FLOW_KEY_SKGID 131 
#define  FLOW_KEY_SKUID 130 
#define  FLOW_KEY_SRC 129 
#define  FLOW_KEY_VLAN_TAG 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  flow_get_dst (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_mark (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_nfct (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_nfct_dst (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_nfct_proto_dst (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_nfct_proto_src (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_nfct_src (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_priority (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_proto (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_proto_dst (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_proto_src (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_rtclassid (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_rxhash (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_skgid (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_skuid (struct sk_buff*) ; 
 int /*<<< orphan*/  flow_get_src (struct sk_buff*,struct flow_keys*) ; 
 int /*<<< orphan*/  flow_get_vlan_tag (struct sk_buff*) ; 

__attribute__((used)) static u32 flow_key_get(struct sk_buff *skb, int key, struct flow_keys *flow)
{
	switch (key) {
	case FLOW_KEY_SRC:
		return flow_get_src(skb, flow);
	case FLOW_KEY_DST:
		return flow_get_dst(skb, flow);
	case FLOW_KEY_PROTO:
		return flow_get_proto(skb, flow);
	case FLOW_KEY_PROTO_SRC:
		return flow_get_proto_src(skb, flow);
	case FLOW_KEY_PROTO_DST:
		return flow_get_proto_dst(skb, flow);
	case FLOW_KEY_IIF:
		return flow_get_iif(skb);
	case FLOW_KEY_PRIORITY:
		return flow_get_priority(skb);
	case FLOW_KEY_MARK:
		return flow_get_mark(skb);
	case FLOW_KEY_NFCT:
		return flow_get_nfct(skb);
	case FLOW_KEY_NFCT_SRC:
		return flow_get_nfct_src(skb, flow);
	case FLOW_KEY_NFCT_DST:
		return flow_get_nfct_dst(skb, flow);
	case FLOW_KEY_NFCT_PROTO_SRC:
		return flow_get_nfct_proto_src(skb, flow);
	case FLOW_KEY_NFCT_PROTO_DST:
		return flow_get_nfct_proto_dst(skb, flow);
	case FLOW_KEY_RTCLASSID:
		return flow_get_rtclassid(skb);
	case FLOW_KEY_SKUID:
		return flow_get_skuid(skb);
	case FLOW_KEY_SKGID:
		return flow_get_skgid(skb);
	case FLOW_KEY_VLAN_TAG:
		return flow_get_vlan_tag(skb);
	case FLOW_KEY_RXHASH:
		return flow_get_rxhash(skb);
	default:
		WARN_ON(1);
		return 0;
	}
}