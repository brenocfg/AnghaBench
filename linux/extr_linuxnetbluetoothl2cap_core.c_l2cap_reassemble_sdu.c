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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct l2cap_ctrl {int sar; } ;
struct l2cap_chan {scalar_t__ sdu_len; struct sk_buff* sdu_last_frag; struct sk_buff* sdu; TYPE_1__* ops; scalar_t__ imtu; } ;
struct TYPE_2__ {int (* recv ) (struct l2cap_chan*,struct sk_buff*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
#define  L2CAP_SAR_CONTINUE 131 
#define  L2CAP_SAR_END 130 
#define  L2CAP_SAR_START 129 
#define  L2CAP_SAR_UNSEGMENTED 128 
 int /*<<< orphan*/  L2CAP_SDULEN_SIZE ; 
 int /*<<< orphan*/  append_skb_frag (struct sk_buff*,struct sk_buff*,struct sk_buff**) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct l2cap_chan*,struct sk_buff*) ; 
 int stub2 (struct l2cap_chan*,struct sk_buff*) ; 

__attribute__((used)) static int l2cap_reassemble_sdu(struct l2cap_chan *chan, struct sk_buff *skb,
				struct l2cap_ctrl *control)
{
	int err = -EINVAL;

	switch (control->sar) {
	case L2CAP_SAR_UNSEGMENTED:
		if (chan->sdu)
			break;

		err = chan->ops->recv(chan, skb);
		break;

	case L2CAP_SAR_START:
		if (chan->sdu)
			break;

		if (!pskb_may_pull(skb, L2CAP_SDULEN_SIZE))
			break;

		chan->sdu_len = get_unaligned_le16(skb->data);
		skb_pull(skb, L2CAP_SDULEN_SIZE);

		if (chan->sdu_len > chan->imtu) {
			err = -EMSGSIZE;
			break;
		}

		if (skb->len >= chan->sdu_len)
			break;

		chan->sdu = skb;
		chan->sdu_last_frag = skb;

		skb = NULL;
		err = 0;
		break;

	case L2CAP_SAR_CONTINUE:
		if (!chan->sdu)
			break;

		append_skb_frag(chan->sdu, skb,
				&chan->sdu_last_frag);
		skb = NULL;

		if (chan->sdu->len >= chan->sdu_len)
			break;

		err = 0;
		break;

	case L2CAP_SAR_END:
		if (!chan->sdu)
			break;

		append_skb_frag(chan->sdu, skb,
				&chan->sdu_last_frag);
		skb = NULL;

		if (chan->sdu->len != chan->sdu_len)
			break;

		err = chan->ops->recv(chan, chan->sdu);

		if (!err) {
			/* Reassembly complete */
			chan->sdu = NULL;
			chan->sdu_last_frag = NULL;
			chan->sdu_len = 0;
		}
		break;
	}

	if (err) {
		kfree_skb(skb);
		kfree_skb(chan->sdu);
		chan->sdu = NULL;
		chan->sdu_last_frag = NULL;
		chan->sdu_len = 0;
	}

	return err;
}