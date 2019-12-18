#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_state; } ;
struct TYPE_7__ {scalar_t__ expires; } ;
struct request_sock {struct request_sock* dl_next; TYPE_2__ rsk_timer; scalar_t__ sk; struct sock* rsk_listener; } ;
struct fastopen_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  qlen; struct request_sock* rskq_rst_tail; struct request_sock* rskq_rst_head; } ;
struct TYPE_6__ {struct fastopen_queue fastopenq; } ;
struct TYPE_10__ {TYPE_1__ icsk_accept_queue; } ;
struct TYPE_9__ {int tfo_listener; } ;
struct TYPE_8__ {int /*<<< orphan*/  fastopen_rsk; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_LISTEN ; 
 TYPE_5__* inet_csk (struct sock*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  reqsk_put (struct request_sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 TYPE_4__* tcp_rsk (struct request_sock*) ; 
 TYPE_3__* tcp_sk (struct sock*) ; 

void reqsk_fastopen_remove(struct sock *sk, struct request_sock *req,
			   bool reset)
{
	struct sock *lsk = req->rsk_listener;
	struct fastopen_queue *fastopenq;

	fastopenq = &inet_csk(lsk)->icsk_accept_queue.fastopenq;

	RCU_INIT_POINTER(tcp_sk(sk)->fastopen_rsk, NULL);
	spin_lock_bh(&fastopenq->lock);
	fastopenq->qlen--;
	tcp_rsk(req)->tfo_listener = false;
	if (req->sk)	/* the child socket hasn't been accepted yet */
		goto out;

	if (!reset || lsk->sk_state != TCP_LISTEN) {
		/* If the listener has been closed don't bother with the
		 * special RST handling below.
		 */
		spin_unlock_bh(&fastopenq->lock);
		reqsk_put(req);
		return;
	}
	/* Wait for 60secs before removing a req that has triggered RST.
	 * This is a simple defense against TFO spoofing attack - by
	 * counting the req against fastopen.max_qlen, and disabling
	 * TFO when the qlen exceeds max_qlen.
	 *
	 * For more details see CoNext'11 "TCP Fast Open" paper.
	 */
	req->rsk_timer.expires = jiffies + 60*HZ;
	if (fastopenq->rskq_rst_head == NULL)
		fastopenq->rskq_rst_head = req;
	else
		fastopenq->rskq_rst_tail->dl_next = req;

	req->dl_next = NULL;
	fastopenq->rskq_rst_tail = req;
	fastopenq->qlen++;
out:
	spin_unlock_bh(&fastopenq->lock);
}