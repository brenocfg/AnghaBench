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
struct TYPE_5__ {int /*<<< orphan*/  seq; int /*<<< orphan*/  time; int /*<<< orphan*/  space; } ;
struct tcp_sock {int advmss; int window_clamp; int /*<<< orphan*/  snd_cwnd_stamp; int /*<<< orphan*/  rcv_ssthresh; int /*<<< orphan*/  copied_seq; TYPE_2__ rcvq_space; int /*<<< orphan*/  tcp_mstamp; int /*<<< orphan*/  rcv_wnd; } ;
struct sock {int sk_userlocks; } ;
struct TYPE_4__ {int sysctl_tcp_app_win; } ;
struct TYPE_6__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int SOCK_SNDBUF_LOCK ; 
 int TCP_INIT_CWND ; 
 void* max (int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* sock_net (struct sock*) ; 
 int tcp_full_space (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sndbuf_expand (struct sock*) ; 
 int /*<<< orphan*/  u32 ; 

void tcp_init_buffer_space(struct sock *sk)
{
	int tcp_app_win = sock_net(sk)->ipv4.sysctl_tcp_app_win;
	struct tcp_sock *tp = tcp_sk(sk);
	int maxwin;

	if (!(sk->sk_userlocks & SOCK_SNDBUF_LOCK))
		tcp_sndbuf_expand(sk);

	tp->rcvq_space.space = min_t(u32, tp->rcv_wnd, TCP_INIT_CWND * tp->advmss);
	tcp_mstamp_refresh(tp);
	tp->rcvq_space.time = tp->tcp_mstamp;
	tp->rcvq_space.seq = tp->copied_seq;

	maxwin = tcp_full_space(sk);

	if (tp->window_clamp >= maxwin) {
		tp->window_clamp = maxwin;

		if (tcp_app_win && maxwin > 4 * tp->advmss)
			tp->window_clamp = max(maxwin -
					       (maxwin >> tcp_app_win),
					       4 * tp->advmss);
	}

	/* Force reservation of one segment. */
	if (tcp_app_win &&
	    tp->window_clamp > 2 * tp->advmss &&
	    tp->window_clamp + tp->advmss > maxwin)
		tp->window_clamp = max(2 * tp->advmss, maxwin - tp->advmss);

	tp->rcv_ssthresh = min(tp->rcv_ssthresh, tp->window_clamp);
	tp->snd_cwnd_stamp = tcp_jiffies32;
}