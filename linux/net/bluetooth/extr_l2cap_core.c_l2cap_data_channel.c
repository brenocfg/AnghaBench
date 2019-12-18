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
typedef  scalar_t__ u16 ;
struct sk_buff {int len; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_chan {scalar_t__ chan_type; scalar_t__ state; int mode; int imtu; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* recv ) (struct l2cap_chan*,struct sk_buff*) ;} ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 scalar_t__ L2CAP_CHAN_FIXED ; 
 scalar_t__ L2CAP_CID_A2MP ; 
#define  L2CAP_MODE_BASIC 131 
#define  L2CAP_MODE_ERTM 130 
#define  L2CAP_MODE_LE_FLOWCTL 129 
#define  L2CAP_MODE_STREAMING 128 
 struct l2cap_chan* a2mp_channel_create (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_ready (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_data_rcv (struct l2cap_chan*,struct sk_buff*) ; 
 struct l2cap_chan* l2cap_get_chan_by_scid (struct l2cap_conn*,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_le_data_rcv (struct l2cap_chan*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*,struct sk_buff*) ; 

__attribute__((used)) static void l2cap_data_channel(struct l2cap_conn *conn, u16 cid,
			       struct sk_buff *skb)
{
	struct l2cap_chan *chan;

	chan = l2cap_get_chan_by_scid(conn, cid);
	if (!chan) {
		if (cid == L2CAP_CID_A2MP) {
			chan = a2mp_channel_create(conn, skb);
			if (!chan) {
				kfree_skb(skb);
				return;
			}

			l2cap_chan_lock(chan);
		} else {
			BT_DBG("unknown cid 0x%4.4x", cid);
			/* Drop packet and return */
			kfree_skb(skb);
			return;
		}
	}

	BT_DBG("chan %p, len %d", chan, skb->len);

	/* If we receive data on a fixed channel before the info req/rsp
	 * procdure is done simply assume that the channel is supported
	 * and mark it as ready.
	 */
	if (chan->chan_type == L2CAP_CHAN_FIXED)
		l2cap_chan_ready(chan);

	if (chan->state != BT_CONNECTED)
		goto drop;

	switch (chan->mode) {
	case L2CAP_MODE_LE_FLOWCTL:
		if (l2cap_le_data_rcv(chan, skb) < 0)
			goto drop;

		goto done;

	case L2CAP_MODE_BASIC:
		/* If socket recv buffers overflows we drop data here
		 * which is *bad* because L2CAP has to be reliable.
		 * But we don't have any other choice. L2CAP doesn't
		 * provide flow control mechanism. */

		if (chan->imtu < skb->len) {
			BT_ERR("Dropping L2CAP data: receive buffer overflow");
			goto drop;
		}

		if (!chan->ops->recv(chan, skb))
			goto done;
		break;

	case L2CAP_MODE_ERTM:
	case L2CAP_MODE_STREAMING:
		l2cap_data_rcv(chan, skb);
		goto done;

	default:
		BT_DBG("chan %p: bad mode 0x%2.2x", chan, chan->mode);
		break;
	}

drop:
	kfree_skb(skb);

done:
	l2cap_chan_unlock(chan);
}