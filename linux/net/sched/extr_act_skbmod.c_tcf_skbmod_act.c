#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcf_skbmod_params {int flags; int /*<<< orphan*/  eth_type; int /*<<< orphan*/ * eth_src; int /*<<< orphan*/ * eth_dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_skbmod {TYPE_1__ common; int /*<<< orphan*/  skbmod_p; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_tm; } ;
struct tcf_result {int dummy; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * h_source; int /*<<< orphan*/ * h_dest; int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MAX_EDIT_LEN ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int SKBMOD_F_DMAC ; 
 int SKBMOD_F_ETYPE ; 
 int SKBMOD_F_SMAC ; 
 int SKBMOD_F_SWAPMAC ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qstats_overlimit_inc (int /*<<< orphan*/ ) ; 
 struct tcf_skbmod_params* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_skbmod* to_skbmod (struct tc_action const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_skbmod_act(struct sk_buff *skb, const struct tc_action *a,
			  struct tcf_result *res)
{
	struct tcf_skbmod *d = to_skbmod(a);
	int action;
	struct tcf_skbmod_params *p;
	u64 flags;
	int err;

	tcf_lastuse_update(&d->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(d->common.cpu_bstats), skb);

	/* XXX: if you are going to edit more fields beyond ethernet header
	 * (example when you add IP header replacement or vlan swap)
	 * then MAX_EDIT_LEN needs to change appropriately
	*/
	err = skb_ensure_writable(skb, MAX_EDIT_LEN);
	if (unlikely(err)) /* best policy is to drop on the floor */
		goto drop;

	action = READ_ONCE(d->tcf_action);
	if (unlikely(action == TC_ACT_SHOT))
		goto drop;

	p = rcu_dereference_bh(d->skbmod_p);
	flags = p->flags;
	if (flags & SKBMOD_F_DMAC)
		ether_addr_copy(eth_hdr(skb)->h_dest, p->eth_dst);
	if (flags & SKBMOD_F_SMAC)
		ether_addr_copy(eth_hdr(skb)->h_source, p->eth_src);
	if (flags & SKBMOD_F_ETYPE)
		eth_hdr(skb)->h_proto = p->eth_type;

	if (flags & SKBMOD_F_SWAPMAC) {
		u16 tmpaddr[ETH_ALEN / 2]; /* ether_addr_copy() requirement */
		/*XXX: I am sure we can come up with more efficient swapping*/
		ether_addr_copy((u8 *)tmpaddr, eth_hdr(skb)->h_dest);
		ether_addr_copy(eth_hdr(skb)->h_dest, eth_hdr(skb)->h_source);
		ether_addr_copy(eth_hdr(skb)->h_source, (u8 *)tmpaddr);
	}

	return action;

drop:
	qstats_overlimit_inc(this_cpu_ptr(d->common.cpu_qstats));
	return TC_ACT_SHOT;
}