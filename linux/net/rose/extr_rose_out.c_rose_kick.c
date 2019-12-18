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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct rose_sock {scalar_t__ state; int condition; unsigned short va; unsigned short vs; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ROSE_COND_ACK_PENDING ; 
 int ROSE_COND_PEER_RX_BUSY ; 
 int ROSE_MODULUS ; 
 scalar_t__ ROSE_STATE_3 ; 
 int /*<<< orphan*/  rose_send_iframe (struct sock*,struct sk_buff*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_timer (struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 int sysctl_rose_window_size ; 

void rose_kick(struct sock *sk)
{
	struct rose_sock *rose = rose_sk(sk);
	struct sk_buff *skb, *skbn;
	unsigned short start, end;

	if (rose->state != ROSE_STATE_3)
		return;

	if (rose->condition & ROSE_COND_PEER_RX_BUSY)
		return;

	if (!skb_peek(&sk->sk_write_queue))
		return;

	start = (skb_peek(&rose->ack_queue) == NULL) ? rose->va : rose->vs;
	end   = (rose->va + sysctl_rose_window_size) % ROSE_MODULUS;

	if (start == end)
		return;

	rose->vs = start;

	/*
	 * Transmit data until either we're out of data to send or
	 * the window is full.
	 */

	skb  = skb_dequeue(&sk->sk_write_queue);

	do {
		if ((skbn = skb_clone(skb, GFP_ATOMIC)) == NULL) {
			skb_queue_head(&sk->sk_write_queue, skb);
			break;
		}

		skb_set_owner_w(skbn, sk);

		/*
		 * Transmit the frame copy.
		 */
		rose_send_iframe(sk, skbn);

		rose->vs = (rose->vs + 1) % ROSE_MODULUS;

		/*
		 * Requeue the original data frame.
		 */
		skb_queue_tail(&rose->ack_queue, skb);

	} while (rose->vs != end &&
		 (skb = skb_dequeue(&sk->sk_write_queue)) != NULL);

	rose->vl         = rose->vr;
	rose->condition &= ~ROSE_COND_ACK_PENDING;

	rose_stop_timer(sk);
}