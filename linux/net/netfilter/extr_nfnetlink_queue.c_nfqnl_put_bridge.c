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
struct sk_buff {scalar_t__ mac_header; scalar_t__ network_header; int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan_tci; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {scalar_t__ pf; } ;
struct nf_queue_entry {TYPE_1__ state; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFQA_L2HDR ; 
 int /*<<< orphan*/  NFQA_VLAN ; 
 int /*<<< orphan*/  NFQA_VLAN_PROTO ; 
 int /*<<< orphan*/  NFQA_VLAN_TCI ; 
 scalar_t__ PF_BRIDGE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int nfqnl_put_bridge(struct nf_queue_entry *entry, struct sk_buff *skb)
{
	struct sk_buff *entskb = entry->skb;

	if (entry->state.pf != PF_BRIDGE || !skb_mac_header_was_set(entskb))
		return 0;

	if (skb_vlan_tag_present(entskb)) {
		struct nlattr *nest;

		nest = nla_nest_start(skb, NFQA_VLAN);
		if (!nest)
			goto nla_put_failure;

		if (nla_put_be16(skb, NFQA_VLAN_TCI, htons(entskb->vlan_tci)) ||
		    nla_put_be16(skb, NFQA_VLAN_PROTO, entskb->vlan_proto))
			goto nla_put_failure;

		nla_nest_end(skb, nest);
	}

	if (entskb->mac_header < entskb->network_header) {
		int len = (int)(entskb->network_header - entskb->mac_header);

		if (nla_put(skb, NFQA_L2HDR, len, skb_mac_header(entskb)))
			goto nla_put_failure;
	}

	return 0;

nla_put_failure:
	return -1;
}