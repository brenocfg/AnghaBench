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
typedef  int /*<<< orphan*/  u8 ;
struct vport {TYPE_2__* ops; TYPE_3__* dev; } ;
struct sk_buff {TYPE_3__* dev; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_6__ {int mtu; int type; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* send ) (struct sk_buff*) ;} ;

/* Variables and functions */
#define  ARPHRD_ETHER 129 
#define  ARPHRD_NONE 128 
 int /*<<< orphan*/  ETH_P_TEB ; 
 int /*<<< orphan*/  MAC_PROTO_ETHERNET ; 
 int /*<<< orphan*/  MAC_PROTO_NONE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ,int,int) ; 
 int packet_length (struct sk_buff*,TYPE_3__*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void ovs_vport_send(struct vport *vport, struct sk_buff *skb, u8 mac_proto)
{
	int mtu = vport->dev->mtu;

	switch (vport->dev->type) {
	case ARPHRD_NONE:
		if (mac_proto == MAC_PROTO_ETHERNET) {
			skb_reset_network_header(skb);
			skb_reset_mac_len(skb);
			skb->protocol = htons(ETH_P_TEB);
		} else if (mac_proto != MAC_PROTO_NONE) {
			WARN_ON_ONCE(1);
			goto drop;
		}
		break;
	case ARPHRD_ETHER:
		if (mac_proto != MAC_PROTO_ETHERNET)
			goto drop;
		break;
	default:
		goto drop;
	}

	if (unlikely(packet_length(skb, vport->dev) > mtu &&
		     !skb_is_gso(skb))) {
		net_warn_ratelimited("%s: dropped over-mtu packet: %d > %d\n",
				     vport->dev->name,
				     packet_length(skb, vport->dev), mtu);
		vport->dev->stats.tx_errors++;
		goto drop;
	}

	skb->dev = vport->dev;
	vport->ops->send(skb);
	return;

drop:
	kfree_skb(skb);
}