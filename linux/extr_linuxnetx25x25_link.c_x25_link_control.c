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
struct x25_neigh {scalar_t__ state; int /*<<< orphan*/  queue; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
#define  X25_DIAGNOSTIC 130 
 scalar_t__ X25_LINK_STATE_3 ; 
#define  X25_RESTART_CONFIRMATION 129 
#define  X25_RESTART_REQUEST 128 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned short,...) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_send_frame (struct sk_buff*,struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_stop_t20timer (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_t20timer_pending (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_transmit_restart_confirmation (struct x25_neigh*) ; 

void x25_link_control(struct sk_buff *skb, struct x25_neigh *nb,
		      unsigned short frametype)
{
	struct sk_buff *skbn;
	int confirm;

	switch (frametype) {
	case X25_RESTART_REQUEST:
		confirm = !x25_t20timer_pending(nb);
		x25_stop_t20timer(nb);
		nb->state = X25_LINK_STATE_3;
		if (confirm)
			x25_transmit_restart_confirmation(nb);
		break;

	case X25_RESTART_CONFIRMATION:
		x25_stop_t20timer(nb);
		nb->state = X25_LINK_STATE_3;
		break;

	case X25_DIAGNOSTIC:
		if (!pskb_may_pull(skb, X25_STD_MIN_LEN + 4))
			break;

		pr_warn("diagnostic #%d - %02X %02X %02X\n",
		       skb->data[3], skb->data[4],
		       skb->data[5], skb->data[6]);
		break;

	default:
		pr_warn("received unknown %02X with LCI 000\n",
		       frametype);
		break;
	}

	if (nb->state == X25_LINK_STATE_3)
		while ((skbn = skb_dequeue(&nb->queue)) != NULL)
			x25_send_frame(skbn, nb);
}