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
struct sk_buff {scalar_t__ sk; } ;
struct lapb_cb {int mode; unsigned short va; unsigned short vs; unsigned short window; int condition; int /*<<< orphan*/  ack_queue; int /*<<< orphan*/  write_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LAPB_ACK_PENDING_CONDITION ; 
 unsigned short LAPB_EMODULUS ; 
 int LAPB_EXTENDED ; 
 int LAPB_PEER_RX_BUSY_CONDITION ; 
 int /*<<< orphan*/  LAPB_POLLOFF ; 
 unsigned short LAPB_SMODULUS ; 
 int /*<<< orphan*/  lapb_send_iframe (struct lapb_cb*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_start_t1timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_t1timer_running (struct lapb_cb*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 

void lapb_kick(struct lapb_cb *lapb)
{
	struct sk_buff *skb, *skbn;
	unsigned short modulus, start, end;

	modulus = (lapb->mode & LAPB_EXTENDED) ? LAPB_EMODULUS : LAPB_SMODULUS;
	start = !skb_peek(&lapb->ack_queue) ? lapb->va : lapb->vs;
	end   = (lapb->va + lapb->window) % modulus;

	if (!(lapb->condition & LAPB_PEER_RX_BUSY_CONDITION) &&
	    start != end && skb_peek(&lapb->write_queue)) {
		lapb->vs = start;

		/*
		 * Dequeue the frame and copy it.
		 */
		skb = skb_dequeue(&lapb->write_queue);

		do {
			if ((skbn = skb_clone(skb, GFP_ATOMIC)) == NULL) {
				skb_queue_head(&lapb->write_queue, skb);
				break;
			}

			if (skb->sk)
				skb_set_owner_w(skbn, skb->sk);

			/*
			 * Transmit the frame copy.
			 */
			lapb_send_iframe(lapb, skbn, LAPB_POLLOFF);

			lapb->vs = (lapb->vs + 1) % modulus;

			/*
			 * Requeue the original data frame.
			 */
			skb_queue_tail(&lapb->ack_queue, skb);

		} while (lapb->vs != end && (skb = skb_dequeue(&lapb->write_queue)) != NULL);

		lapb->condition &= ~LAPB_ACK_PENDING_CONDITION;

		if (!lapb_t1timer_running(lapb))
			lapb_start_t1timer(lapb);
	}
}