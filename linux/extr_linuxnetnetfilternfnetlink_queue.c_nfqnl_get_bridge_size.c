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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ network_header; scalar_t__ mac_header; } ;
struct TYPE_2__ {scalar_t__ pf; } ;
struct nf_queue_entry {TYPE_1__ state; struct sk_buff* skb; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ PF_BRIDGE ; 
 int nla_total_size (int) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static u32 nfqnl_get_bridge_size(struct nf_queue_entry *entry)
{
	struct sk_buff *entskb = entry->skb;
	u32 nlalen = 0;

	if (entry->state.pf != PF_BRIDGE || !skb_mac_header_was_set(entskb))
		return 0;

	if (skb_vlan_tag_present(entskb))
		nlalen += nla_total_size(nla_total_size(sizeof(__be16)) +
					 nla_total_size(sizeof(__be16)));

	if (entskb->network_header > entskb->mac_header)
		nlalen += nla_total_size((entskb->network_header -
					  entskb->mac_header));

	return nlalen;
}