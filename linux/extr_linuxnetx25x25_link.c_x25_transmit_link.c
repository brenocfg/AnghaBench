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
struct x25_neigh {int state; int /*<<< orphan*/  queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
#define  X25_LINK_STATE_0 131 
#define  X25_LINK_STATE_1 130 
#define  X25_LINK_STATE_2 129 
#define  X25_LINK_STATE_3 128 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  x25_establish_link (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_send_frame (struct sk_buff*,struct x25_neigh*) ; 

void x25_transmit_link(struct sk_buff *skb, struct x25_neigh *nb)
{
	switch (nb->state) {
	case X25_LINK_STATE_0:
		skb_queue_tail(&nb->queue, skb);
		nb->state = X25_LINK_STATE_1;
		x25_establish_link(nb);
		break;
	case X25_LINK_STATE_1:
	case X25_LINK_STATE_2:
		skb_queue_tail(&nb->queue, skb);
		break;
	case X25_LINK_STATE_3:
		x25_send_frame(skb, nb);
		break;
	}
}