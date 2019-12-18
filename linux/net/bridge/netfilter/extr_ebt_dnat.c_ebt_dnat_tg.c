#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_action_param {struct ebt_nat_info* targinfo; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ebt_nat_info {unsigned int target; int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {TYPE_1__* br; } ;
struct TYPE_5__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_4__ {struct net_device* dev; } ;

/* Variables and functions */
 unsigned int EBT_DROP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
#define  NF_BR_BROUTING 129 
#define  NF_BR_PRE_ROUTING 128 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  PACKET_MULTICAST ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 TYPE_3__* br_port_get_rcu (struct net_device*) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int xt_hooknum (struct xt_action_param const*) ; 
 struct net_device* xt_in (struct xt_action_param const*) ; 

__attribute__((used)) static unsigned int
ebt_dnat_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ebt_nat_info *info = par->targinfo;

	if (skb_ensure_writable(skb, ETH_ALEN))
		return EBT_DROP;

	ether_addr_copy(eth_hdr(skb)->h_dest, info->mac);

	if (is_multicast_ether_addr(info->mac)) {
		if (is_broadcast_ether_addr(info->mac))
			skb->pkt_type = PACKET_BROADCAST;
		else
			skb->pkt_type = PACKET_MULTICAST;
	} else {
		const struct net_device *dev;

		switch (xt_hooknum(par)) {
		case NF_BR_BROUTING:
			dev = xt_in(par);
			break;
		case NF_BR_PRE_ROUTING:
			dev = br_port_get_rcu(xt_in(par))->br->dev;
			break;
		default:
			dev = NULL;
			break;
		}

		if (!dev) /* NF_BR_LOCAL_OUT */
			return info->target;

		if (ether_addr_equal(info->mac, dev->dev_addr))
			skb->pkt_type = PACKET_HOST;
		else
			skb->pkt_type = PACKET_OTHERHOST;
	}

	return info->target;
}