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
typedef  int u32 ;
struct tcp_sock {int snd_cwnd; scalar_t__ snd_cwnd_used; int /*<<< orphan*/  snd_cwnd_stamp; int /*<<< orphan*/  snd_ssthresh; } ;
struct sock {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {scalar_t__ icsk_rto; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_CWND_RESTART ; 
 int /*<<< orphan*/  __sk_dst_get (struct sock*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int max (int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_current_ssthresh (struct sock*) ; 
 int tcp_init_cwnd (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_cwnd_restart(struct sock *sk, s32 delta)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 restart_cwnd = tcp_init_cwnd(tp, __sk_dst_get(sk));
	u32 cwnd = tp->snd_cwnd;

	tcp_ca_event(sk, CA_EVENT_CWND_RESTART);

	tp->snd_ssthresh = tcp_current_ssthresh(sk);
	restart_cwnd = min(restart_cwnd, cwnd);

	while ((delta -= inet_csk(sk)->icsk_rto) > 0 && cwnd > restart_cwnd)
		cwnd >>= 1;
	tp->snd_cwnd = max(cwnd, restart_cwnd);
	tp->snd_cwnd_stamp = tcp_jiffies32;
	tp->snd_cwnd_used = 0;
}