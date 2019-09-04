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
struct sock {int /*<<< orphan*/  sk_priority; } ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct l2cap_chan {struct sock* data; } ;
struct TYPE_3__ {struct l2cap_chan* chan; } ;
struct TYPE_4__ {TYPE_1__ l2cap; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_send_alloc (struct sock*,unsigned long,int,int*) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 

__attribute__((used)) static struct sk_buff *l2cap_sock_alloc_skb_cb(struct l2cap_chan *chan,
					       unsigned long hdr_len,
					       unsigned long len, int nb)
{
	struct sock *sk = chan->data;
	struct sk_buff *skb;
	int err;

	l2cap_chan_unlock(chan);
	skb = bt_skb_send_alloc(sk, hdr_len + len, nb, &err);
	l2cap_chan_lock(chan);

	if (!skb)
		return ERR_PTR(err);

	skb->priority = sk->sk_priority;

	bt_cb(skb)->l2cap.chan = chan;

	return skb;
}