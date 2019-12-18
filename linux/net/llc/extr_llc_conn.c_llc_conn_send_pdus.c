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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct llc_pdu_sn {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdu_unack_q; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_LOOPBACK ; 
 scalar_t__ LLC_PDU_TYPE_IS_I (struct llc_pdu_sn*) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 TYPE_2__* llc_sk (struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void llc_conn_send_pdus(struct sock *sk)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&sk->sk_write_queue)) != NULL) {
		struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

		if (LLC_PDU_TYPE_IS_I(pdu) &&
		    !(skb->dev->flags & IFF_LOOPBACK)) {
			struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

			skb_queue_tail(&llc_sk(sk)->pdu_unack_q, skb);
			if (!skb2)
				break;
			skb = skb2;
		}
		dev_queue_xmit(skb);
	}
}