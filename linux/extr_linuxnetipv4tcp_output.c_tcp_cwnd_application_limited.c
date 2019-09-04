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
typedef  int u32 ;
struct tcp_sock {int snd_cwnd; int /*<<< orphan*/  snd_cwnd_stamp; scalar_t__ snd_cwnd_used; int /*<<< orphan*/  snd_ssthresh; } ;
struct sock {TYPE_1__* sk_socket; } ;
struct TYPE_4__ {scalar_t__ icsk_ca_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 scalar_t__ TCP_CA_Open ; 
 int /*<<< orphan*/  __sk_dst_get (struct sock*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int max (scalar_t__,int) ; 
 int /*<<< orphan*/  tcp_current_ssthresh (struct sock*) ; 
 int tcp_init_cwnd (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcp_cwnd_application_limited(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (inet_csk(sk)->icsk_ca_state == TCP_CA_Open &&
	    sk->sk_socket && !test_bit(SOCK_NOSPACE, &sk->sk_socket->flags)) {
		/* Limited by application or receiver window. */
		u32 init_win = tcp_init_cwnd(tp, __sk_dst_get(sk));
		u32 win_used = max(tp->snd_cwnd_used, init_win);
		if (win_used < tp->snd_cwnd) {
			tp->snd_ssthresh = tcp_current_ssthresh(sk);
			tp->snd_cwnd = (tp->snd_cwnd + win_used) >> 1;
		}
		tp->snd_cwnd_used = 0;
	}
	tp->snd_cwnd_stamp = tcp_jiffies32;
}