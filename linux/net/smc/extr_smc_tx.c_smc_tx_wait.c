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
struct sock {int sk_shutdown; scalar_t__ sk_err; TYPE_3__* sk_socket; } ;
struct TYPE_4__ {scalar_t__ peer_done_writing; } ;
struct TYPE_5__ {TYPE_1__ conn_state_flags; } ;
struct smc_connection {int /*<<< orphan*/  urg_tx_pend; int /*<<< orphan*/  sndbuf_space; TYPE_2__ local_tx_ctrl; } ;
struct smc_sock {struct sock sk; struct smc_connection conn; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ECONNRESET ; 
 int EPIPE ; 
 int MSG_DONTWAIT ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ smc_cdc_rxed_any_close (struct smc_connection*) ; 
 int sock_intr_errno (long) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int smc_tx_wait(struct smc_sock *smc, int flags)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct smc_connection *conn = &smc->conn;
	struct sock *sk = &smc->sk;
	long timeo;
	int rc = 0;

	/* similar to sk_stream_wait_memory */
	timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);
	add_wait_queue(sk_sleep(sk), &wait);
	while (1) {
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		if (sk->sk_err ||
		    (sk->sk_shutdown & SEND_SHUTDOWN) ||
		    conn->local_tx_ctrl.conn_state_flags.peer_done_writing) {
			rc = -EPIPE;
			break;
		}
		if (smc_cdc_rxed_any_close(conn)) {
			rc = -ECONNRESET;
			break;
		}
		if (!timeo) {
			/* ensure EPOLLOUT is subsequently generated */
			set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
			rc = -EAGAIN;
			break;
		}
		if (signal_pending(current)) {
			rc = sock_intr_errno(timeo);
			break;
		}
		sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);
		if (atomic_read(&conn->sndbuf_space) && !conn->urg_tx_pend)
			break; /* at least 1 byte of free & no urgent data */
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		sk_wait_event(sk, &timeo,
			      sk->sk_err ||
			      (sk->sk_shutdown & SEND_SHUTDOWN) ||
			      smc_cdc_rxed_any_close(conn) ||
			      (atomic_read(&conn->sndbuf_space) &&
			       !conn->urg_tx_pend),
			      &wait);
	}
	remove_wait_queue(sk_sleep(sk), &wait);
	return rc;
}