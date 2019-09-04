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
struct tap_queue {int flags; int /*<<< orphan*/  sk; int /*<<< orphan*/  ring; } ;
struct tap_dev {int tap_features; int /*<<< orphan*/  (* count_rx_dropped ) (struct tap_dev*) ;} ;
struct sk_buff {scalar_t__ ip_summed; struct sk_buff* next; struct net_device* dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;
typedef  int netdev_features_t ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EPOLLIN ; 
 int EPOLLRDBAND ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int IFF_VNET_HDR ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NETIF_F_CSUM_MASK ; 
 int /*<<< orphan*/  RX_HANDLER_CONSUMED ; 
 int /*<<< orphan*/  RX_HANDLER_PASS ; 
 int TAP_FEATURES ; 
 struct sk_buff* __skb_gso_segment (struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb_list (struct sk_buff*) ; 
 scalar_t__ netif_needs_gso (struct sk_buff*,int) ; 
 scalar_t__ ptr_ring_produce (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_sleep (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_checksum_help (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tap_dev*) ; 
 struct tap_dev* tap_dev_get_rcu (struct net_device*) ; 
 struct tap_queue* tap_get_queue (struct tap_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ ,int) ; 

rx_handler_result_t tap_handle_frame(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct net_device *dev = skb->dev;
	struct tap_dev *tap;
	struct tap_queue *q;
	netdev_features_t features = TAP_FEATURES;

	tap = tap_dev_get_rcu(dev);
	if (!tap)
		return RX_HANDLER_PASS;

	q = tap_get_queue(tap, skb);
	if (!q)
		return RX_HANDLER_PASS;

	skb_push(skb, ETH_HLEN);

	/* Apply the forward feature mask so that we perform segmentation
	 * according to users wishes.  This only works if VNET_HDR is
	 * enabled.
	 */
	if (q->flags & IFF_VNET_HDR)
		features |= tap->tap_features;
	if (netif_needs_gso(skb, features)) {
		struct sk_buff *segs = __skb_gso_segment(skb, features, false);

		if (IS_ERR(segs))
			goto drop;

		if (!segs) {
			if (ptr_ring_produce(&q->ring, skb))
				goto drop;
			goto wake_up;
		}

		consume_skb(skb);
		while (segs) {
			struct sk_buff *nskb = segs->next;

			segs->next = NULL;
			if (ptr_ring_produce(&q->ring, segs)) {
				kfree_skb(segs);
				kfree_skb_list(nskb);
				break;
			}
			segs = nskb;
		}
	} else {
		/* If we receive a partial checksum and the tap side
		 * doesn't support checksum offload, compute the checksum.
		 * Note: it doesn't matter which checksum feature to
		 *	  check, we either support them all or none.
		 */
		if (skb->ip_summed == CHECKSUM_PARTIAL &&
		    !(features & NETIF_F_CSUM_MASK) &&
		    skb_checksum_help(skb))
			goto drop;
		if (ptr_ring_produce(&q->ring, skb))
			goto drop;
	}

wake_up:
	wake_up_interruptible_poll(sk_sleep(&q->sk), EPOLLIN | EPOLLRDNORM | EPOLLRDBAND);
	return RX_HANDLER_CONSUMED;

drop:
	/* Count errors/drops only here, thus don't care about args. */
	if (tap->count_rx_dropped)
		tap->count_rx_dropped(tap);
	kfree_skb(skb);
	return RX_HANDLER_CONSUMED;
}