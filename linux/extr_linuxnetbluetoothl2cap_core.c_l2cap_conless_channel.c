#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_chan {scalar_t__ state; scalar_t__ imtu; TYPE_2__* ops; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  psm; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_6__ {TYPE_1__ l2cap; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* recv ) (struct l2cap_chan*,struct sk_buff*) ;} ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 scalar_t__ BT_BOUND ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,scalar_t__) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 struct l2cap_chan* l2cap_global_chan_by_psm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*,struct sk_buff*) ; 

__attribute__((used)) static void l2cap_conless_channel(struct l2cap_conn *conn, __le16 psm,
				  struct sk_buff *skb)
{
	struct hci_conn *hcon = conn->hcon;
	struct l2cap_chan *chan;

	if (hcon->type != ACL_LINK)
		goto free_skb;

	chan = l2cap_global_chan_by_psm(0, psm, &hcon->src, &hcon->dst,
					ACL_LINK);
	if (!chan)
		goto free_skb;

	BT_DBG("chan %p, len %d", chan, skb->len);

	if (chan->state != BT_BOUND && chan->state != BT_CONNECTED)
		goto drop;

	if (chan->imtu < skb->len)
		goto drop;

	/* Store remote BD_ADDR and PSM for msg_name */
	bacpy(&bt_cb(skb)->l2cap.bdaddr, &hcon->dst);
	bt_cb(skb)->l2cap.psm = psm;

	if (!chan->ops->recv(chan, skb)) {
		l2cap_chan_put(chan);
		return;
	}

drop:
	l2cap_chan_put(chan);
free_skb:
	kfree_skb(skb);
}