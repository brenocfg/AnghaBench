#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void DBGUNDO(struct sock *sk, const char *msg)
{
#if FASTRETRANS_DEBUG > 1
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_sock *inet = inet_sk(sk);

	if (sk->sk_family == AF_INET) {
		pr_debug("Undo %s %pI4/%u c%u l%u ss%u/%u p%u\n",
			 msg,
			 &inet->inet_daddr, ntohs(inet->inet_dport),
			 tp->snd_cwnd, tcp_left_out(tp),
			 tp->snd_ssthresh, tp->prior_ssthresh,
			 tp->packets_out);
	}
#if IS_ENABLED(CONFIG_IPV6)
	else if (sk->sk_family == AF_INET6) {
		pr_debug("Undo %s %pI6/%u c%u l%u ss%u/%u p%u\n",
			 msg,
			 &sk->sk_v6_daddr, ntohs(inet->inet_dport),
			 tp->snd_cwnd, tcp_left_out(tp),
			 tp->snd_ssthresh, tp->prior_ssthresh,
			 tp->packets_out);
	}
#endif
#endif
}