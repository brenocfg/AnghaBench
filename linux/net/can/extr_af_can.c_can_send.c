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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  pkt_type; void* ip_summed; int /*<<< orphan*/  sk; TYPE_3__* dev; void* protocol; scalar_t__ data; } ;
struct canfd_frame {scalar_t__ len; } ;
struct can_pkg_stats {int /*<<< orphan*/  tx_frames_delta; int /*<<< orphan*/  tx_frames; } ;
struct TYPE_6__ {scalar_t__ mtu; scalar_t__ type; int flags; } ;
struct TYPE_4__ {struct can_pkg_stats* pkg_stats; } ;
struct TYPE_5__ {TYPE_1__ can; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 scalar_t__ CANFD_MAX_DLEN ; 
 scalar_t__ CANFD_MTU ; 
 scalar_t__ CAN_MAX_DLEN ; 
 scalar_t__ CAN_MTU ; 
 void* CHECKSUM_UNNECESSARY ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  ETH_P_CAN ; 
 int /*<<< orphan*/  ETH_P_CANFD ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_ECHO ; 
 int IFF_UP ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int /*<<< orphan*/  PACKET_LOOPBACK ; 
 int /*<<< orphan*/  can_skb_set_owner (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dev_net (TYPE_3__*) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int can_send(struct sk_buff *skb, int loop)
{
	struct sk_buff *newskb = NULL;
	struct canfd_frame *cfd = (struct canfd_frame *)skb->data;
	struct can_pkg_stats *pkg_stats = dev_net(skb->dev)->can.pkg_stats;
	int err = -EINVAL;

	if (skb->len == CAN_MTU) {
		skb->protocol = htons(ETH_P_CAN);
		if (unlikely(cfd->len > CAN_MAX_DLEN))
			goto inval_skb;
	} else if (skb->len == CANFD_MTU) {
		skb->protocol = htons(ETH_P_CANFD);
		if (unlikely(cfd->len > CANFD_MAX_DLEN))
			goto inval_skb;
	} else {
		goto inval_skb;
	}

	/* Make sure the CAN frame can pass the selected CAN netdevice.
	 * As structs can_frame and canfd_frame are similar, we can provide
	 * CAN FD frames to legacy CAN drivers as long as the length is <= 8
	 */
	if (unlikely(skb->len > skb->dev->mtu && cfd->len > CAN_MAX_DLEN)) {
		err = -EMSGSIZE;
		goto inval_skb;
	}

	if (unlikely(skb->dev->type != ARPHRD_CAN)) {
		err = -EPERM;
		goto inval_skb;
	}

	if (unlikely(!(skb->dev->flags & IFF_UP))) {
		err = -ENETDOWN;
		goto inval_skb;
	}

	skb->ip_summed = CHECKSUM_UNNECESSARY;

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);

	if (loop) {
		/* local loopback of sent CAN frames */

		/* indication for the CAN driver: do loopback */
		skb->pkt_type = PACKET_LOOPBACK;

		/* The reference to the originating sock may be required
		 * by the receiving socket to check whether the frame is
		 * its own. Example: can_raw sockopt CAN_RAW_RECV_OWN_MSGS
		 * Therefore we have to ensure that skb->sk remains the
		 * reference to the originating sock by restoring skb->sk
		 * after each skb_clone() or skb_orphan() usage.
		 */

		if (!(skb->dev->flags & IFF_ECHO)) {
			/* If the interface is not capable to do loopback
			 * itself, we do it here.
			 */
			newskb = skb_clone(skb, GFP_ATOMIC);
			if (!newskb) {
				kfree_skb(skb);
				return -ENOMEM;
			}

			can_skb_set_owner(newskb, skb->sk);
			newskb->ip_summed = CHECKSUM_UNNECESSARY;
			newskb->pkt_type = PACKET_BROADCAST;
		}
	} else {
		/* indication for the CAN driver: no loopback required */
		skb->pkt_type = PACKET_HOST;
	}

	/* send to netdevice */
	err = dev_queue_xmit(skb);
	if (err > 0)
		err = net_xmit_errno(err);

	if (err) {
		kfree_skb(newskb);
		return err;
	}

	if (newskb)
		netif_rx_ni(newskb);

	/* update statistics */
	pkg_stats->tx_frames++;
	pkg_stats->tx_frames_delta++;

	return 0;

inval_skb:
	kfree_skb(skb);
	return err;
}