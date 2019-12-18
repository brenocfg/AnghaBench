#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; } ;
struct l2cap_chan {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* recv ) (struct l2cap_chan*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_le_send_credits (struct l2cap_chan*) ; 
 int stub1 (struct l2cap_chan*,struct sk_buff*) ; 

__attribute__((used)) static int l2cap_le_recv(struct l2cap_chan *chan, struct sk_buff *skb)
{
	int err;

	BT_DBG("SDU reassemble complete: chan %p skb->len %u", chan, skb->len);

	/* Wait recv to confirm reception before updating the credits */
	err = chan->ops->recv(chan, skb);

	/* Update credits whenever an SDU is received */
	l2cap_chan_le_send_credits(chan);

	return err;
}