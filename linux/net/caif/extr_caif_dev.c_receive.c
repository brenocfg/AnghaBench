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
struct sk_buff {int dummy; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;
struct cfpkt {int dummy; } ;
struct TYPE_3__ {TYPE_2__* up; } ;
struct caif_device_entry {TYPE_1__ layer; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {int (* receive ) (TYPE_2__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_DIR_IN ; 
 int EILSEQ ; 
 int NET_RX_DROP ; 
 struct caif_device_entry* caif_get (struct net_device*) ; 
 int /*<<< orphan*/  caifd_hold (struct caif_device_entry*) ; 
 int /*<<< orphan*/  caifd_put (struct caif_device_entry*) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 struct cfpkt* cfpkt_fromnative (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_oper_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (TYPE_2__*,struct cfpkt*) ; 

__attribute__((used)) static int receive(struct sk_buff *skb, struct net_device *dev,
		   struct packet_type *pkttype, struct net_device *orig_dev)
{
	struct cfpkt *pkt;
	struct caif_device_entry *caifd;
	int err;

	pkt = cfpkt_fromnative(CAIF_DIR_IN, skb);

	rcu_read_lock();
	caifd = caif_get(dev);

	if (!caifd || !caifd->layer.up || !caifd->layer.up->receive ||
			!netif_oper_up(caifd->netdev)) {
		rcu_read_unlock();
		kfree_skb(skb);
		return NET_RX_DROP;
	}

	/* Hold reference to netdevice while using CAIF stack */
	caifd_hold(caifd);
	rcu_read_unlock();

	err = caifd->layer.up->receive(caifd->layer.up, pkt);

	/* For -EILSEQ the packet is not freed so so it now */
	if (err == -EILSEQ)
		cfpkt_destroy(pkt);

	/* Release reference to stack upwards */
	caifd_put(caifd);

	if (err != 0)
		err = NET_RX_DROP;
	return err;
}