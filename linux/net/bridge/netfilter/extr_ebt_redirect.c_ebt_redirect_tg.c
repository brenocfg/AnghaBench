#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xt_action_param {struct ebt_redirect_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; } ;
struct ebt_redirect_info {unsigned int target; } ;
struct TYPE_11__ {TYPE_2__* br; } ;
struct TYPE_10__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_8__ {TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 unsigned int EBT_DROP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NF_BR_BROUTING ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 TYPE_5__* br_port_get_rcu (TYPE_3__*) ; 
 TYPE_4__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ xt_hooknum (struct xt_action_param const*) ; 
 TYPE_3__* xt_in (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
ebt_redirect_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ebt_redirect_info *info = par->targinfo;

	if (skb_ensure_writable(skb, ETH_ALEN))
		return EBT_DROP;

	if (xt_hooknum(par) != NF_BR_BROUTING)
		/* rcu_read_lock()ed by nf_hook_thresh */
		ether_addr_copy(eth_hdr(skb)->h_dest,
				br_port_get_rcu(xt_in(par))->br->dev->dev_addr);
	else
		ether_addr_copy(eth_hdr(skb)->h_dest, xt_in(par)->dev_addr);
	skb->pkt_type = PACKET_HOST;
	return info->target;
}