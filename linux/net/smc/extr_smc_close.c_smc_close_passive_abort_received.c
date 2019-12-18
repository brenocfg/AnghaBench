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
struct sock {int sk_state; } ;
struct smc_cdc_conn_state_flags {int /*<<< orphan*/  peer_done_writing; } ;
struct TYPE_3__ {struct smc_cdc_conn_state_flags conn_state_flags; } ;
struct TYPE_4__ {TYPE_1__ local_tx_ctrl; } ;
struct smc_sock {TYPE_2__ conn; struct sock sk; } ;

/* Variables and functions */
#define  SMC_ACTIVE 137 
#define  SMC_APPCLOSEWAIT1 136 
#define  SMC_APPCLOSEWAIT2 135 
#define  SMC_APPFINCLOSEWAIT 134 
 void* SMC_CLOSED ; 
#define  SMC_INIT 133 
#define  SMC_PEERABORTWAIT 132 
#define  SMC_PEERCLOSEWAIT1 131 
#define  SMC_PEERCLOSEWAIT2 130 
#define  SMC_PEERFINCLOSEWAIT 129 
#define  SMC_PROCESSABORT 128 
 int /*<<< orphan*/  smc_close_sent_any_close (TYPE_2__*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static void smc_close_passive_abort_received(struct smc_sock *smc)
{
	struct smc_cdc_conn_state_flags *txflags =
		&smc->conn.local_tx_ctrl.conn_state_flags;
	struct sock *sk = &smc->sk;

	switch (sk->sk_state) {
	case SMC_INIT:
	case SMC_ACTIVE:
	case SMC_APPCLOSEWAIT1:
		sk->sk_state = SMC_PROCESSABORT;
		sock_put(sk); /* passive closing */
		break;
	case SMC_APPFINCLOSEWAIT:
		sk->sk_state = SMC_PROCESSABORT;
		break;
	case SMC_PEERCLOSEWAIT1:
	case SMC_PEERCLOSEWAIT2:
		if (txflags->peer_done_writing &&
		    !smc_close_sent_any_close(&smc->conn))
			/* just shutdown, but not yet closed locally */
			sk->sk_state = SMC_PROCESSABORT;
		else
			sk->sk_state = SMC_CLOSED;
		sock_put(sk); /* passive closing */
		break;
	case SMC_APPCLOSEWAIT2:
	case SMC_PEERFINCLOSEWAIT:
		sk->sk_state = SMC_CLOSED;
		sock_put(sk); /* passive closing */
		break;
	case SMC_PEERABORTWAIT:
		sk->sk_state = SMC_CLOSED;
		break;
	case SMC_PROCESSABORT:
	/* nothing to do, add tracing in future patch */
		break;
	}
}