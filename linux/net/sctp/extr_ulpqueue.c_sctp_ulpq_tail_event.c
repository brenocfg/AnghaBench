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
struct sk_buff_head {int dummy; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct sctp_ulpq {scalar_t__ pd_mode; TYPE_2__* asoc; } ;
struct sctp_ulpevent {int msg_flags; } ;
struct sctp_sock {int data_ready_signalled; struct sk_buff_head pd_lobby; scalar_t__ frag_interleave; int /*<<< orphan*/  pd_mode; } ;
struct TYPE_3__ {struct sock* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  subscribe; TYPE_1__ base; } ;

/* Variables and functions */
 int MSG_EOR ; 
 int MSG_NOTIFICATION ; 
 int RCV_SHUTDOWN ; 
 int SCTP_DATA_FRAG_MASK ; 
 int SCTP_DATA_NOT_FRAG ; 
 int SEND_SHUTDOWN ; 
 struct sk_buff* __skb_peek (struct sk_buff_head*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_queue_purge_ulpevents (struct sk_buff_head*) ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_ulpevent_free (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpevent_is_enabled (struct sctp_ulpevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_is_notification (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_ulpq_clear_pd (struct sctp_ulpq*) ; 
 int /*<<< orphan*/  sk_incoming_cpu_update (struct sock*) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int sctp_ulpq_tail_event(struct sctp_ulpq *ulpq, struct sk_buff_head *skb_list)
{
	struct sock *sk = ulpq->asoc->base.sk;
	struct sctp_sock *sp = sctp_sk(sk);
	struct sctp_ulpevent *event;
	struct sk_buff_head *queue;
	struct sk_buff *skb;
	int clear_pd = 0;

	skb = __skb_peek(skb_list);
	event = sctp_skb2event(skb);

	/* If the socket is just going to throw this away, do not
	 * even try to deliver it.
	 */
	if (sk->sk_shutdown & RCV_SHUTDOWN &&
	    (sk->sk_shutdown & SEND_SHUTDOWN ||
	     !sctp_ulpevent_is_notification(event)))
		goto out_free;

	if (!sctp_ulpevent_is_notification(event)) {
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	}
	/* Check if the user wishes to receive this event.  */
	if (!sctp_ulpevent_is_enabled(event, ulpq->asoc->subscribe))
		goto out_free;

	/* If we are in partial delivery mode, post to the lobby until
	 * partial delivery is cleared, unless, of course _this_ is
	 * the association the cause of the partial delivery.
	 */

	if (atomic_read(&sp->pd_mode) == 0) {
		queue = &sk->sk_receive_queue;
	} else {
		if (ulpq->pd_mode) {
			/* If the association is in partial delivery, we
			 * need to finish delivering the partially processed
			 * packet before passing any other data.  This is
			 * because we don't truly support stream interleaving.
			 */
			if ((event->msg_flags & MSG_NOTIFICATION) ||
			    (SCTP_DATA_NOT_FRAG ==
				    (event->msg_flags & SCTP_DATA_FRAG_MASK)))
				queue = &sp->pd_lobby;
			else {
				clear_pd = event->msg_flags & MSG_EOR;
				queue = &sk->sk_receive_queue;
			}
		} else {
			/*
			 * If fragment interleave is enabled, we
			 * can queue this to the receive queue instead
			 * of the lobby.
			 */
			if (sp->frag_interleave)
				queue = &sk->sk_receive_queue;
			else
				queue = &sp->pd_lobby;
		}
	}

	skb_queue_splice_tail_init(skb_list, queue);

	/* Did we just complete partial delivery and need to get
	 * rolling again?  Move pending data to the receive
	 * queue.
	 */
	if (clear_pd)
		sctp_ulpq_clear_pd(ulpq);

	if (queue == &sk->sk_receive_queue && !sp->data_ready_signalled) {
		if (!sock_owned_by_user(sk))
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