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
struct sock {int sk_shutdown; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sctp_ulpq {TYPE_2__* asoc; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_sock {int data_ready_signalled; } ;
struct TYPE_3__ {struct sock* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  subscribe; TYPE_1__ base; } ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 struct sk_buff* __skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_queue_purge_ulpevents (struct sk_buff_head*) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_free (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpevent_is_enabled (struct sctp_ulpevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_is_notification (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sk_incoming_cpu_update (struct sock*) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int sctp_enqueue_event(struct sctp_ulpq *ulpq,
			      struct sk_buff_head *skb_list)
{
	struct sock *sk = ulpq->asoc->base.sk;
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_ulpevent *event;
	struct sk_buff *skb;

	skb = __skb_peek(skb_list);
	event = sctp_skb2event(skb);

	if (sk->sk_shutdown & RCV_SHUTDOWN &&
	    (sk->sk_shutdown & SEND_SHUTDOWN ||
	     !sctp_ulpevent_is_notification(event)))
		goto out_free;

	if (!sctp_ulpevent_is_notification(event)) {
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	}

	if (!sctp_ulpevent_is_enabled(event, ulpq->asoc->subscribe))
		goto out_free;

	if (skb_list)
		skb_queue_splice_tail_init(skb_list,
					   &sk->sk_receive_queue);
	else
		__skb_queue_tail(&sk->sk_receive_queue, skb);

	if (!sp->data_ready_signalled) {
		sp->data_ready_signalled = 1;
		sk->sk_data_ready(sk);
	}

	return 1;

out_free:
	if (skb_list)
		sctp_queue_purge_ulpevents(skb_list);
	else
		sctp_ulpevent_free(event);

	return 0;
}