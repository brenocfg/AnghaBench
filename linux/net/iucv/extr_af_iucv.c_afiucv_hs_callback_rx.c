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
struct sock {scalar_t__ sk_state; int sk_shutdown; int /*<<< orphan*/  sk_drops; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct iucv_sock {TYPE_1__ message_q; int /*<<< orphan*/  backlog_skb_q; } ;
struct af_iucv_trans_hdr {int dummy; } ;
struct TYPE_4__ {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ IUCV_CONNECTED ; 
 TYPE_2__* IUCV_SKB_CB (struct sk_buff*) ; 
 int NET_RX_SUCCESS ; 
 int RCV_SHUTDOWN ; 
 scalar_t__ __sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ sk_filter (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afiucv_hs_callback_rx(struct sock *sk, struct sk_buff *skb)
{
	struct iucv_sock *iucv = iucv_sk(sk);

	if (!iucv) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	if (sk->sk_state != IUCV_CONNECTED) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	if (sk->sk_shutdown & RCV_SHUTDOWN) {
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	/* write stuff from iucv_msg to skb cb */
	skb_pull(skb, sizeof(struct af_iucv_trans_hdr));
	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	IUCV_SKB_CB(skb)->offset = 0;
	if (sk_filter(sk, skb)) {
		atomic_inc(&sk->sk_drops);	/* skb rejected by filter */
		kfree_skb(skb);
		return NET_RX_SUCCESS;
	}

	spin_lock(&iucv->message_q.lock);
	if (skb_queue_empty(&iucv->backlog_skb_q)) {
		if (__sock_queue_rcv_skb(sk, skb))
			/* handle rcv queue full */
			skb_queue_tail(&iucv->backlog_skb_q, skb);
	} else
		skb_queue_tail(&iucv_sk(sk)->backlog_skb_q, skb);
	spin_unlock(&iucv->message_q.lock);
	return NET_RX_SUCCESS;
}