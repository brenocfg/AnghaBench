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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct l2cap_chan {scalar_t__ imtu; scalar_t__ sdu_len; struct sk_buff* sdu_last_frag; struct sk_buff* sdu; TYPE_1__* ops; scalar_t__ rx_credits; } ;
struct TYPE_2__ {int (* recv ) (struct l2cap_chan*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  L2CAP_SDULEN_SIZE ; 
 int /*<<< orphan*/  append_skb_frag (struct sk_buff*,struct sk_buff*,struct sk_buff**) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_chan_le_send_credits (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct l2cap_chan*,struct sk_buff*) ; 
 int stub2 (struct l2cap_chan*,struct sk_buff*) ; 

__attribute__((used)) static int l2cap_le_data_rcv(struct l2cap_chan *chan, struct sk_buff *skb)
{
	int err;

	if (!chan->rx_credits) {
		BT_ERR("No credits to receive LE L2CAP data");
		l2cap_send_disconn_req(chan, ECONNRESET);
		return -ENOBUFS;
	}

	if (chan->imtu < skb->len) {
		BT_ERR("Too big LE L2CAP PDU");
		return -ENOBUFS;
	}

	chan->rx_credits--;
	BT_DBG("rx_credits %u -> %u", chan->rx_credits + 1, chan->rx_credits);

	l2cap_chan_le_send_credits(chan);

	err = 0;

	if (!chan->sdu) {
		u16 sdu_len;

		sdu_len = get_unaligned_le16(skb->data);
		skb_pull(skb, L2CAP_SDULEN_SIZE);

		BT_DBG("Start of new SDU. sdu_len %u skb->len %u imtu %u",
		       sdu_len, skb->len, chan->imtu);

		if (sdu_len > chan->imtu) {
			BT_ERR("Too big LE L2CAP SDU length received");
			err = -EMSGSIZE;
			goto failed;
		}

		if (skb->len > sdu_len) {
			BT_ERR("Too much LE L2CAP data received");
			err = -EINVAL;
			goto failed;
		}

		if (skb->len == sdu_len)
			return chan->ops->recv(chan, skb);

		chan->sdu = skb;
		chan->sdu_len = sdu_len;
		chan->sdu_last_frag = skb;

		return 0;
	}

	BT_DBG("SDU fragment. chan->sdu->len %u skb->len %u chan->sdu_len %u",
	       chan->sdu->len, skb->len, chan->sdu_len);

	if (chan->sdu->len + skb->len > chan->sdu_len) {
		BT_ERR("Too much LE L2CAP data received");
		err = -EINVAL;
		goto failed;
	}

	append_skb_frag(chan->sdu, skb, &chan->sdu_last_frag);
	skb = NULL;

	if (chan->sdu->len == chan->sdu_len) {
		err = chan->ops->recv(chan, chan->sdu);
		if (!err) {
			chan->sdu = NULL;
			chan->sdu_last_frag = NULL;
			chan->sdu_len = 0;
		}
	}

failed:
	if (err) {
		kfree_skb(skb);
		kfree_skb(chan->sdu);
		chan->sdu = NULL;
		chan->sdu_last_frag = NULL;
		chan->sdu_len = 0;
	}

	/* We can't return an error here since we took care of the skb
	 * freeing internally. An error return would cause the caller to
	 * do a double-free of the skb.
	 */
	return 0;
}