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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sctp_ulpq {TYPE_2__* asoc; } ;
struct sctp_ulpevent {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {int data_ready_signalled; int /*<<< orphan*/  subscribe; } ;
struct TYPE_4__ {struct sock* sk; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARTIAL_DELIVERY_ABORTED ; 
 int /*<<< orphan*/  SCTP_PARTIAL_DELIVERY_EVENT ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_event2skb (struct sctp_ulpevent*) ; 
 TYPE_3__* sctp_sk (struct sock*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_pdapi (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_type_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void sctp_intl_stream_abort_pd(struct sctp_ulpq *ulpq, __u16 sid,
				      __u32 mid, __u16 flags, gfp_t gfp)
{
	struct sock *sk = ulpq->asoc->base.sk;
	struct sctp_ulpevent *ev = NULL;

	if (!sctp_ulpevent_type_enabled(SCTP_PARTIAL_DELIVERY_EVENT,
					&sctp_sk(sk)->subscribe))
		return;

	ev = sctp_ulpevent_make_pdapi(ulpq->asoc, SCTP_PARTIAL_DELIVERY_ABORTED,
				      sid, mid, flags, gfp);
	if (ev) {
		__skb_queue_tail(&sk->sk_receive_queue, sctp_event2skb(ev));

		if (!sctp_sk(sk)->data_ready_signalled) {
			sctp_sk(sk)->data_ready_signalled = 1;
			sk->sk_data_ready(sk);
		}
	}
}