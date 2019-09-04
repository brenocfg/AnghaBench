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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;void* sk_err; } ;
struct smc_cdc_conn_state_flags {int /*<<< orphan*/  peer_conn_closed; } ;
struct TYPE_5__ {struct smc_cdc_conn_state_flags conn_state_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_work; TYPE_1__ local_tx_ctrl; } ;
struct smc_sock {TYPE_4__ conn; TYPE_2__* clcsock; struct sock sk; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* sk_state_change ) (TYPE_3__*) ;void* sk_err; } ;
struct TYPE_6__ {TYPE_3__* sk; } ;

/* Variables and functions */
 void* ECONNABORTED ; 
#define  SMC_ACTIVE 138 
#define  SMC_APPCLOSEWAIT1 137 
#define  SMC_APPCLOSEWAIT2 136 
#define  SMC_APPFINCLOSEWAIT 135 
#define  SMC_CLOSED 134 
#define  SMC_INIT 133 
#define  SMC_PEERABORTWAIT 132 
#define  SMC_PEERCLOSEWAIT1 131 
#define  SMC_PEERCLOSEWAIT2 130 
#define  SMC_PEERFINCLOSEWAIT 129 
#define  SMC_PROCESSABORT 128 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  smc_cdc_rxed_any_close (TYPE_4__*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static void smc_close_active_abort(struct smc_sock *smc)
{
	struct sock *sk = &smc->sk;

	struct smc_cdc_conn_state_flags *txflags =
		&smc->conn.local_tx_ctrl.conn_state_flags;

	if (sk->sk_state != SMC_INIT && smc->clcsock && smc->clcsock->sk) {
		sk->sk_err = ECONNABORTED;
		if (smc->clcsock && smc->clcsock->sk) {
			smc->clcsock->sk->sk_err = ECONNABORTED;
			smc->clcsock->sk->sk_state_change(smc->clcsock->sk);
		}
	}
	switch (sk->sk_state) {
	case SMC_ACTIVE:
		sk->sk_state = SMC_PEERABORTWAIT;
		release_sock(sk);
		cancel_delayed_work_sync(&smc->conn.tx_work);
		lock_sock(sk);
		sock_put(sk); /* passive closing */
		break;
	case SMC_APPCLOSEWAIT1:
	case SMC_APPCLOSEWAIT2:
		if (!smc_cdc_rxed_any_close(&smc->conn))
			sk->sk_state = SMC_PEERABORTWAIT;
		else
			sk->sk_state = SMC_CLOSED;
		release_sock(sk);
		cancel_delayed_work_sync(&smc->conn.tx_work);
		lock_sock(sk);
		break;
	case SMC_PEERCLOSEWAIT1:
	case SMC_PEERCLOSEWAIT2:
		if (!txflags->peer_conn_closed) {
			/* just SHUTDOWN_SEND done */
			sk->sk_state = SMC_PEERABORTWAIT;
		} else {
			sk->sk_state = SMC_CLOSED;
		}
		sock_put(sk); /* passive closing */
		break;
	case SMC_PROCESSABORT:
	case SMC_APPFINCLOSEWAIT:
		sk->sk_state = SMC_CLOSED;
		break;
	case SMC_PEERFINCLOSEWAIT:
		sock_put(sk); /* passive closing */
		break;
	case SMC_INIT:
	case SMC_PEERABORTWAIT:
	case SMC_CLOSED:
		break;
	}

	sock_set_flag(sk, SOCK_DEAD);
	sk->sk_state_change(sk);
}