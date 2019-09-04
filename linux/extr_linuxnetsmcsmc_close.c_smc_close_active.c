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
struct sock {long sk_lingertime; int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct smc_cdc_conn_state_flags {int /*<<< orphan*/  peer_done_writing; } ;
struct TYPE_5__ {struct smc_cdc_conn_state_flags conn_state_flags; } ;
struct smc_connection {int /*<<< orphan*/  tx_work; TYPE_1__ local_tx_ctrl; } ;
struct smc_sock {int /*<<< orphan*/  tcp_listen_work; TYPE_3__* clcsock; struct sock sk; struct smc_connection conn; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {TYPE_2__* sk; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* sk_data_ready ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int PF_EXITING ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
#define  SMC_ACTIVE 139 
#define  SMC_APPCLOSEWAIT1 138 
#define  SMC_APPCLOSEWAIT2 137 
#define  SMC_APPFINCLOSEWAIT 136 
#define  SMC_CLOSED 135 
#define  SMC_INIT 134 
#define  SMC_LISTEN 133 
 long SMC_MAX_STREAM_WAIT_TIMEOUT ; 
#define  SMC_PEERABORTWAIT 132 
#define  SMC_PEERCLOSEWAIT1 131 
#define  SMC_PEERCLOSEWAIT2 130 
#define  SMC_PEERFINCLOSEWAIT 129 
#define  SMC_PROCESSABORT 128 
 int /*<<< orphan*/  SOCK_LINGER ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int kernel_sock_shutdown (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  smc_cdc_rxed_any_close (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_close_abort (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_close_cleanup_listen (struct sock*) ; 
 int smc_close_final (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_close_sent_any_close (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_close_stream_wait (struct smc_sock*,long) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 

int smc_close_active(struct smc_sock *smc)
{
	struct smc_cdc_conn_state_flags *txflags =
		&smc->conn.local_tx_ctrl.conn_state_flags;
	struct smc_connection *conn = &smc->conn;
	struct sock *sk = &smc->sk;
	int old_state;
	long timeout;
	int rc = 0;

	timeout = current->flags & PF_EXITING ?
		  0 : sock_flag(sk, SOCK_LINGER) ?
		      sk->sk_lingertime : SMC_MAX_STREAM_WAIT_TIMEOUT;

	old_state = sk->sk_state;
again:
	switch (sk->sk_state) {
	case SMC_INIT:
		sk->sk_state = SMC_CLOSED;
		break;
	case SMC_LISTEN:
		sk->sk_state = SMC_CLOSED;
		sk->sk_state_change(sk); /* wake up accept */
		if (smc->clcsock && smc->clcsock->sk) {
			rc = kernel_sock_shutdown(smc->clcsock, SHUT_RDWR);
			/* wake up kernel_accept of smc_tcp_listen_worker */
			smc->clcsock->sk->sk_data_ready(smc->clcsock->sk);
		}
		smc_close_cleanup_listen(sk);
		release_sock(sk);
		flush_work(&smc->tcp_listen_work);
		lock_sock(sk);
		break;
	case SMC_ACTIVE:
		smc_close_stream_wait(smc, timeout);
		release_sock(sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(sk);
		if (sk->sk_state == SMC_ACTIVE) {
			/* send close request */
			rc = smc_close_final(conn);
			if (rc)
				break;
			sk->sk_state = SMC_PEERCLOSEWAIT1;
		} else {
			/* peer event has changed the state */
			goto again;
		}
		break;
	case SMC_APPFINCLOSEWAIT:
		/* socket already shutdown wr or both (active close) */
		if (txflags->peer_done_writing &&
		    !smc_close_sent_any_close(conn)) {
			/* just shutdown wr done, send close request */
			rc = smc_close_final(conn);
			if (rc)
				break;
		}
		sk->sk_state = SMC_CLOSED;
		break;
	case SMC_APPCLOSEWAIT1:
	case SMC_APPCLOSEWAIT2:
		if (!smc_cdc_rxed_any_close(conn))
			smc_close_stream_wait(smc, timeout);
		release_sock(sk);
		cancel_delayed_work_sync(&conn->tx_work);
		lock_sock(sk);
		if (sk->sk_state != SMC_APPCLOSEWAIT1 &&
		    sk->sk_state != SMC_APPCLOSEWAIT2)
			goto again;
		/* confirm close from peer */
		rc = smc_close_final(conn);
		if (rc)
			break;
		if (smc_cdc_rxed_any_close(conn)) {
			/* peer has closed the socket already */
			sk->sk_state = SMC_CLOSED;
			sock_put(sk); /* postponed passive closing */
		} else {
			/* peer has just issued a shutdown write */
			sk->sk_state = SMC_PEERFINCLOSEWAIT;
		}
		break;
	case SMC_PEERCLOSEWAIT1:
	case SMC_PEERCLOSEWAIT2:
		if (txflags->peer_done_writing &&
		    !smc_close_sent_any_close(conn)) {
			/* just shutdown wr done, send close request */
			rc = smc_close_final(conn);
			if (rc)
				break;
		}
		/* peer sending PeerConnectionClosed will cause transition */
		break;
	case SMC_PEERFINCLOSEWAIT:
		/* peer sending PeerConnectionClosed will cause transition */
		break;
	case SMC_PROCESSABORT:
		smc_close_abort(conn);
		sk->sk_state = SMC_CLOSED;
		break;
	case SMC_PEERABORTWAIT:
	case SMC_CLOSED:
		/* nothing to do, add tracing in future patch */
		break;
	}

	if (old_state != sk->sk_state)
		sk->sk_state_change(sk);
	return rc;
}