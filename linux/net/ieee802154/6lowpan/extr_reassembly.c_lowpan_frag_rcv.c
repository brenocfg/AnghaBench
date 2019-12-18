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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct lowpan_frag_queue {TYPE_1__ q; } ;
struct lowpan_802154_cb {scalar_t__ d_size; } ;
struct ieee802154_hdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 scalar_t__ IPV6_MIN_MTU ; 
 int /*<<< orphan*/  LOWPAN_DISPATCH_FRAG1 ; 
 int NET_RX_DROP ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 struct lowpan_frag_queue* fq_find (struct net*,struct lowpan_802154_cb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee802154_hdr_peek_addrs (struct sk_buff*,struct ieee802154_hdr*) ; 
 int /*<<< orphan*/  inet_frag_put (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct lowpan_802154_cb* lowpan_802154_cb (struct sk_buff*) ; 
 int lowpan_frag_queue (struct lowpan_frag_queue*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int lowpan_get_cb (struct sk_buff*,int /*<<< orphan*/ ,struct lowpan_802154_cb*) ; 
 int lowpan_invoke_frag_rx_handlers (struct sk_buff*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int lowpan_frag_rcv(struct sk_buff *skb, u8 frag_type)
{
	struct lowpan_frag_queue *fq;
	struct net *net = dev_net(skb->dev);
	struct lowpan_802154_cb *cb = lowpan_802154_cb(skb);
	struct ieee802154_hdr hdr = {};
	int err;

	if (ieee802154_hdr_peek_addrs(skb, &hdr) < 0)
		goto err;

	err = lowpan_get_cb(skb, frag_type, cb);
	if (err < 0)
		goto err;

	if (frag_type == LOWPAN_DISPATCH_FRAG1) {
		err = lowpan_invoke_frag_rx_handlers(skb);
		if (err == NET_RX_DROP)
			goto err;
	}

	if (cb->d_size > IPV6_MIN_MTU) {
		net_warn_ratelimited("lowpan_frag_rcv: datagram size exceeds MTU\n");
		goto err;
	}

	fq = fq_find(net, cb, &hdr.source, &hdr.dest);
	if (fq != NULL) {
		int ret;

		spin_lock(&fq->q.lock);
		ret = lowpan_frag_queue(fq, skb, frag_type);
		spin_unlock(&fq->q.lock);

		inet_frag_put(&fq->q);
		return ret;
	}

err:
	kfree_skb(skb);
	return -1;
}