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
typedef  int u32 ;
struct tcpnv {int cwnd_growth_factor; int /*<<< orphan*/  nv_allow_cwnd_growth; } ;
struct tcp_sock {int snd_cwnd; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct tcpnv* inet_csk_ca (struct sock*) ; 
 int max (unsigned int,int) ; 
 int /*<<< orphan*/  tcp_cong_avoid_ai (struct tcp_sock*,int,int) ; 
 scalar_t__ tcp_in_slow_start (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_is_cwnd_limited (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_slow_start (struct tcp_sock*,int) ; 

__attribute__((used)) static void tcpnv_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcpnv *ca = inet_csk_ca(sk);
	u32 cnt;

	if (!tcp_is_cwnd_limited(sk))
		return;

	/* Only grow cwnd if NV has not detected congestion */
	if (!ca->nv_allow_cwnd_growth)
		return;

	if (tcp_in_slow_start(tp)) {
		acked = tcp_slow_start(tp, acked);
		if (!acked)
			return;
	}

	if (ca->cwnd_growth_factor < 0) {
		cnt = tp->snd_cwnd << -ca->cwnd_growth_factor;
		tcp_cong_avoid_ai(tp, cnt, acked);
	} else {
		cnt = max(4U, tp->snd_cwnd >> ca->cwnd_growth_factor);
		tcp_cong_avoid_ai(tp, cnt, acked);
	}
}