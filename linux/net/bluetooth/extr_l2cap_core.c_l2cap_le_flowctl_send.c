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
struct l2cap_chan {int /*<<< orphan*/  tx_q; int /*<<< orphan*/  tx_credits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  l2cap_do_send (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_le_flowctl_send(struct l2cap_chan *chan)
{
	int sent = 0;

	BT_DBG("chan %p", chan);

	while (chan->tx_credits && !skb_queue_empty(&chan->tx_q)) {
		l2cap_do_send(chan, skb_dequeue(&chan->tx_q));
		chan->tx_credits--;
		sent++;
	}

	BT_DBG("Sent %d credits %u queued %u", sent, chan->tx_credits,
	       skb_queue_len(&chan->tx_q));
}