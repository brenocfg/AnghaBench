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
struct sock {int dummy; } ;
struct request_sock {int dummy; } ;
struct TYPE_4__ {scalar_t__ icsk_retransmits; } ;
struct TYPE_3__ {int /*<<< orphan*/  fastopen_rsk; scalar_t__ retrans_stamp; } ;

/* Variables and functions */
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  lockdep_sock_is_held (struct sock*) ; 
 struct request_sock* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reqsk_fastopen_remove (struct sock*,struct request_sock*,int) ; 
 int /*<<< orphan*/  tcp_rearm_rto (struct sock*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_undo_loss (struct sock*,int) ; 

__attribute__((used)) static void tcp_rcv_synrecv_state_fastopen(struct sock *sk)
{
	struct request_sock *req;

	tcp_try_undo_loss(sk, false);

	/* Reset rtx states to prevent spurious retransmits_timed_out() */
	tcp_sk(sk)->retrans_stamp = 0;
	inet_csk(sk)->icsk_retransmits = 0;

	/* Once we leave TCP_SYN_RECV or TCP_FIN_WAIT_1,
	 * we no longer need req so release it.
	 */
	req = rcu_dereference_protected(tcp_sk(sk)->fastopen_rsk,
					lockdep_sock_is_held(sk));
	reqsk_fastopen_remove(sk, req, false);

	/* Re-arm the timer because data may have been sent out.
	 * This is similar to the regular data transmission case
	 * when new data has just been ack'ed.
	 *
	 * (TFO) - we could try to be more aggressive and
	 * retransmitting any data sooner based on when they
	 * are sent out.
	 */
	tcp_rearm_rto(sk);
}