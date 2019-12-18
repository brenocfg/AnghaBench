#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  write_queue; int /*<<< orphan*/  ack_queue; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 struct sk_buff* skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

void ax25_requeue_frames(ax25_cb *ax25)
{
	struct sk_buff *skb;

	/*
	 * Requeue all the un-ack-ed frames on the output queue to be picked
	 * up by ax25_kick called from the timer. This arrangement handles the
	 * possibility of an empty output queue.
	 */
	while ((skb = skb_dequeue_tail(&ax25->ack_queue)) != NULL)
		skb_queue_head(&ax25->write_queue, skb);
}