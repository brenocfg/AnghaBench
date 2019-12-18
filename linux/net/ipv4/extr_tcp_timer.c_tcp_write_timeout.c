#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {int dummy; } ;
struct sock {int sk_state; } ;
struct TYPE_2__ {int sysctl_tcp_syn_retries; int sysctl_tcp_retries1; int sysctl_tcp_retries2; } ;
struct net {TYPE_1__ ipv4; } ;
struct inet_connection_sock {int icsk_retransmits; scalar_t__ icsk_rto; int /*<<< orphan*/  icsk_user_timeout; scalar_t__ icsk_syn_retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCK_OPS_RTO_CB ; 
 int /*<<< orphan*/  BPF_SOCK_OPS_RTO_CB_FLAG ; 
 scalar_t__ BPF_SOCK_OPS_TEST_FLAG (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int TCPF_SYN_RECV ; 
 int TCPF_SYN_SENT ; 
 scalar_t__ TCP_RTO_MAX ; 
 int /*<<< orphan*/  dst_negative_advice (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int retransmits_timed_out (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_rethink_txhash (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_call_bpf_3arg (struct sock*,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  tcp_fastopen_active_detect_blackhole (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_mtu_probing (struct inet_connection_sock*,struct sock*) ; 
 int tcp_orphan_retries (struct sock*,int const) ; 
 scalar_t__ tcp_out_of_resources (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_err (struct sock*) ; 

__attribute__((used)) static int tcp_write_timeout(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct net *net = sock_net(sk);
	bool expired = false, do_reset;
	int retry_until;

	if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
		if (icsk->icsk_retransmits) {
			dst_negative_advice(sk);
		} else {
			sk_rethink_txhash(sk);
		}
		retry_until = icsk->icsk_syn_retries ? : net->ipv4.sysctl_tcp_syn_retries;
		expired = icsk->icsk_retransmits >= retry_until;
	} else {
		if (retransmits_timed_out(sk, net->ipv4.sysctl_tcp_retries1, 0)) {
			/* Black hole detection */
			tcp_mtu_probing(icsk, sk);

			dst_negative_advice(sk);
		} else {
			sk_rethink_txhash(sk);
		}

		retry_until = net->ipv4.sysctl_tcp_retries2;
		if (sock_flag(sk, SOCK_DEAD)) {
			const bool alive = icsk->icsk_rto < TCP_RTO_MAX;

			retry_until = tcp_orphan_retries(sk, alive);
			do_reset = alive ||
				!retransmits_timed_out(sk, retry_until, 0);

			if (tcp_out_of_resources(sk, do_reset))
				return 1;
		}
	}
	if (!expired)
		expired = retransmits_timed_out(sk, retry_until,
						icsk->icsk_user_timeout);
	tcp_fastopen_active_detect_blackhole(sk, expired);

	if (BPF_SOCK_OPS_TEST_FLAG(tp, BPF_SOCK_OPS_RTO_CB_FLAG))
		tcp_call_bpf_3arg(sk, BPF_SOCK_OPS_RTO_CB,
				  icsk->icsk_retransmits,
				  icsk->icsk_rto, (int)expired);

	if (expired) {
		/* Has it gone just too far? */
		tcp_write_err(sk);
		return 1;
	}

	return 0;
}