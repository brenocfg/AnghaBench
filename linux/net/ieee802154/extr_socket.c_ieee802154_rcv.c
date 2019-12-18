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
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct packet_type {int dummy; } ;
struct net_device {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802154 ; 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int NET_RX_DROP ; 
 scalar_t__ PACKET_OTHERHOST ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int ieee802154_dgram_deliver (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee802154_raw_deliver (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee802154_rcv(struct sk_buff *skb, struct net_device *dev,
			  struct packet_type *pt, struct net_device *orig_dev)
{
	if (!netif_running(dev))
		goto drop;
	pr_debug("got frame, type %d, dev %p\n", dev->type, dev);
#ifdef DEBUG
	print_hex_dump_bytes("ieee802154_rcv ",
			     DUMP_PREFIX_NONE, skb->data, skb->len);
#endif

	if (!net_eq(dev_net(dev), &init_net))
		goto drop;

	ieee802154_raw_deliver(dev, skb);

	if (dev->type != ARPHRD_IEEE802154)
		goto drop;

	if (skb->pkt_type != PACKET_OTHERHOST)
		return ieee802154_dgram_deliver(dev, skb);

drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}