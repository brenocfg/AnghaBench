#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_can {int /*<<< orphan*/  can_ifindex; int /*<<< orphan*/  can_family; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; struct sock* sk; TYPE_1__* dev; scalar_t__ cb; } ;
struct raw_sock {int count; scalar_t__ join_filters; TYPE_3__* uniq; int /*<<< orphan*/  fd_frames; int /*<<< orphan*/  recv_own_msgs; } ;
struct TYPE_8__ {scalar_t__ skbcnt; } ;
struct TYPE_7__ {int /*<<< orphan*/  join_rx_count; } ;
struct TYPE_6__ {scalar_t__ skbcnt; int join_rx_count; struct sk_buff* skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CAN ; 
 scalar_t__ CAN_MTU ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int MSG_CONFIRM ; 
 unsigned int MSG_DONTROUTE ; 
 TYPE_4__* can_skb_prv (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_can*,int /*<<< orphan*/ ,int) ; 
 unsigned int* raw_flags (struct sk_buff*) ; 
 struct raw_sock* raw_sk (struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_skb_cb_check_size (int) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 TYPE_2__* this_cpu_ptr (TYPE_3__*) ; 

__attribute__((used)) static void raw_rcv(struct sk_buff *oskb, void *data)
{
	struct sock *sk = (struct sock *)data;
	struct raw_sock *ro = raw_sk(sk);
	struct sockaddr_can *addr;
	struct sk_buff *skb;
	unsigned int *pflags;

	/* check the received tx sock reference */
	if (!ro->recv_own_msgs && oskb->sk == sk)
		return;

	/* do not pass non-CAN2.0 frames to a legacy socket */
	if (!ro->fd_frames && oskb->len != CAN_MTU)
		return;

	/* eliminate multiple filter matches for the same skb */
	if (this_cpu_ptr(ro->uniq)->skb == oskb &&
	    this_cpu_ptr(ro->uniq)->skbcnt == can_skb_prv(oskb)->skbcnt) {
		if (ro->join_filters) {
			this_cpu_inc(ro->uniq->join_rx_count);
			/* drop frame until all enabled filters matched */
			if (this_cpu_ptr(ro->uniq)->join_rx_count < ro->count)
				return;
		} else {
			return;
		}
	} else {
		this_cpu_ptr(ro->uniq)->skb = oskb;
		this_cpu_ptr(ro->uniq)->skbcnt = can_skb_prv(oskb)->skbcnt;
		this_cpu_ptr(ro->uniq)->join_rx_count = 1;
		/* drop first frame to check all enabled filters? */
		if (ro->join_filters && ro->count > 1)
			return;
	}

	/* clone the given skb to be able to enqueue it into the rcv queue */
	skb = skb_clone(oskb, GFP_ATOMIC);
	if (!skb)
		return;

	/*  Put the datagram to the queue so that raw_recvmsg() can
	 *  get it from there.  We need to pass the interface index to
	 *  raw_recvmsg().  We pass a whole struct sockaddr_can in skb->cb
	 *  containing the interface index.
	 */

	sock_skb_cb_check_size(sizeof(struct sockaddr_can));
	addr = (struct sockaddr_can *)skb->cb;
	memset(addr, 0, sizeof(*addr));
	addr->can_family  = AF_CAN;
	addr->can_ifindex = skb->dev->ifindex;

	/* add CAN specific message flags for raw_recvmsg() */
	pflags = raw_flags(skb);
	*pflags = 0;
	if (oskb->sk)
		*pflags |= MSG_DONTROUTE;
	if (oskb->sk == sk)
		*pflags |= MSG_CONFIRM;

	if (sock_queue_rcv_skb(sk, skb) < 0)
		kfree_skb(skb);
}