#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sctp_ulpq {scalar_t__ pd_mode; struct sctp_association* asoc; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_sock {int /*<<< orphan*/  pd_mode; scalar_t__ frag_interleave; } ;
struct TYPE_7__ {int /*<<< orphan*/  tsn_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  reasm; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; } ;
struct sctp_association {TYPE_3__ peer; TYPE_2__ ulpq; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  tsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSN_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 struct sctp_sock* sctp_sk (int /*<<< orphan*/ ) ; 
 TYPE_4__* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 
 struct sctp_ulpevent* sctp_ulpq_retrieve_first (struct sctp_ulpq*) ; 
 int /*<<< orphan*/  sctp_ulpq_set_pd (struct sctp_ulpq*) ; 
 int /*<<< orphan*/  sctp_ulpq_tail_event (struct sctp_ulpq*,struct sk_buff_head*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 

void sctp_ulpq_partial_delivery(struct sctp_ulpq *ulpq,
				gfp_t gfp)
{
	struct sctp_ulpevent *event;
	struct sctp_association *asoc;
	struct sctp_sock *sp;
	__u32 ctsn;
	struct sk_buff *skb;

	asoc = ulpq->asoc;
	sp = sctp_sk(asoc->base.sk);

	/* If the association is already in Partial Delivery mode
	 * we have nothing to do.
	 */
	if (ulpq->pd_mode)
		return;

	/* Data must be at or below the Cumulative TSN ACK Point to
	 * start partial delivery.
	 */
	skb = skb_peek(&asoc->ulpq.reasm);
	if (skb != NULL) {
		ctsn = sctp_skb2event(skb)->tsn;
		if (!TSN_lte(ctsn, sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map)))
			return;
	}

	/* If the user enabled fragment interleave socket option,
	 * multiple associations can enter partial delivery.
	 * Otherwise, we can only enter partial delivery if the
	 * socket is not in partial deliver mode.
	 */
	if (sp->frag_interleave || atomic_read(&sp->pd_mode) == 0) {
		/* Is partial delivery possible?  */
		event = sctp_ulpq_retrieve_first(ulpq);
		/* Send event to the ULP.   */
		if (event) {
			struct sk_buff_head temp;

			skb_queue_head_init(&temp);
			__skb_queue_tail(&temp, sctp_event2skb(event));
			sctp_ulpq_tail_event(ulpq, &temp);
			sctp_ulpq_set_pd(ulpq);
			return;
		}
	}
}