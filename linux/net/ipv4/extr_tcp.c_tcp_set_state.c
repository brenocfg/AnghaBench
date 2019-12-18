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
struct sock {int sk_state; int sk_userlocks; TYPE_1__* sk_prot; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_bind_hash; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unhash ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCK_OPS_STATE_CB ; 
 int /*<<< orphan*/  BPF_SOCK_OPS_STATE_CB_FLAG ; 
 scalar_t__ BPF_SOCK_OPS_TEST_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_TCP_CLOSE ; 
 scalar_t__ BPF_TCP_CLOSE_WAIT ; 
 scalar_t__ BPF_TCP_CLOSING ; 
 scalar_t__ BPF_TCP_ESTABLISHED ; 
 scalar_t__ BPF_TCP_FIN_WAIT1 ; 
 scalar_t__ BPF_TCP_FIN_WAIT2 ; 
 scalar_t__ BPF_TCP_LAST_ACK ; 
 scalar_t__ BPF_TCP_LISTEN ; 
 scalar_t__ BPF_TCP_MAX_STATES ; 
 scalar_t__ BPF_TCP_NEW_SYN_RECV ; 
 scalar_t__ BPF_TCP_SYN_RECV ; 
 scalar_t__ BPF_TCP_SYN_SENT ; 
 scalar_t__ BPF_TCP_TIME_WAIT ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int SOCK_BINDPORT_LOCK ; 
#define  TCP_CLOSE 129 
 int TCP_CLOSE_WAIT ; 
 scalar_t__ TCP_CLOSING ; 
 int /*<<< orphan*/  TCP_DEC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TCP_ESTABLISHED 128 
 scalar_t__ TCP_FIN_WAIT1 ; 
 scalar_t__ TCP_FIN_WAIT2 ; 
 int /*<<< orphan*/  TCP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_LAST_ACK ; 
 scalar_t__ TCP_LISTEN ; 
 scalar_t__ TCP_MAX_STATES ; 
 int /*<<< orphan*/  TCP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  TCP_MIB_ESTABRESETS ; 
 scalar_t__ TCP_NEW_SYN_RECV ; 
 scalar_t__ TCP_SYN_RECV ; 
 scalar_t__ TCP_SYN_SENT ; 
 scalar_t__ TCP_TIME_WAIT ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 
 int /*<<< orphan*/  inet_sk_state_store (struct sock*,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_call_bpf_2arg (struct sock*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 

void tcp_set_state(struct sock *sk, int state)
{
	int oldstate = sk->sk_state;

	/* We defined a new enum for TCP states that are exported in BPF
	 * so as not force the internal TCP states to be frozen. The
	 * following checks will detect if an internal state value ever
	 * differs from the BPF value. If this ever happens, then we will
	 * need to remap the internal value to the BPF value before calling
	 * tcp_call_bpf_2arg.
	 */
	BUILD_BUG_ON((int)BPF_TCP_ESTABLISHED != (int)TCP_ESTABLISHED);
	BUILD_BUG_ON((int)BPF_TCP_SYN_SENT != (int)TCP_SYN_SENT);
	BUILD_BUG_ON((int)BPF_TCP_SYN_RECV != (int)TCP_SYN_RECV);
	BUILD_BUG_ON((int)BPF_TCP_FIN_WAIT1 != (int)TCP_FIN_WAIT1);
	BUILD_BUG_ON((int)BPF_TCP_FIN_WAIT2 != (int)TCP_FIN_WAIT2);
	BUILD_BUG_ON((int)BPF_TCP_TIME_WAIT != (int)TCP_TIME_WAIT);
	BUILD_BUG_ON((int)BPF_TCP_CLOSE != (int)TCP_CLOSE);
	BUILD_BUG_ON((int)BPF_TCP_CLOSE_WAIT != (int)TCP_CLOSE_WAIT);
	BUILD_BUG_ON((int)BPF_TCP_LAST_ACK != (int)TCP_LAST_ACK);
	BUILD_BUG_ON((int)BPF_TCP_LISTEN != (int)TCP_LISTEN);
	BUILD_BUG_ON((int)BPF_TCP_CLOSING != (int)TCP_CLOSING);
	BUILD_BUG_ON((int)BPF_TCP_NEW_SYN_RECV != (int)TCP_NEW_SYN_RECV);
	BUILD_BUG_ON((int)BPF_TCP_MAX_STATES != (int)TCP_MAX_STATES);

	if (BPF_SOCK_OPS_TEST_FLAG(tcp_sk(sk), BPF_SOCK_OPS_STATE_CB_FLAG))
		tcp_call_bpf_2arg(sk, BPF_SOCK_OPS_STATE_CB, oldstate, state);

	switch (state) {
	case TCP_ESTABLISHED:
		if (oldstate != TCP_ESTABLISHED)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_CURRESTAB);
		break;

	case TCP_CLOSE:
		if (oldstate == TCP_CLOSE_WAIT || oldstate == TCP_ESTABLISHED)
			TCP_INC_STATS(sock_net(sk), TCP_MIB_ESTABRESETS);

		sk->sk_prot->unhash(sk);
		if (inet_csk(sk)->icsk_bind_hash &&
		    !(sk->sk_userlocks & SOCK_BINDPORT_LOCK))
			inet_put_port(sk);
		/* fall through */
	default:
		if (oldstate == TCP_ESTABLISHED)
			TCP_DEC_STATS(sock_net(sk), TCP_MIB_CURRESTAB);
	}

	/* Change state AFTER socket is unhashed to avoid closed
	 * socket sitting in hash tables.
	 */
	inet_sk_state_store(sk, state);
}