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
struct tcp_sock {scalar_t__ frto; int /*<<< orphan*/  high_seq; int /*<<< orphan*/  snd_nxt; } ;
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int REXMIT_NONE ; 
 int /*<<< orphan*/  TCP_NAGLE_OFF ; 
 scalar_t__ TCP_SYN_SENT ; 
 int /*<<< orphan*/  __tcp_push_pending_frames (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_current_mss (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_xmit_retransmit_queue (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tcp_xmit_recovery(struct sock *sk, int rexmit)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (rexmit == REXMIT_NONE || sk->sk_state == TCP_SYN_SENT)
		return;

	if (unlikely(rexmit == 2)) {
		__tcp_push_pending_frames(sk, tcp_current_mss(sk),
					  TCP_NAGLE_OFF);
		if (after(tp->snd_nxt, tp->high_seq))
			return;
		tp->frto = 0;
	}
	tcp_xmit_retransmit_queue(sk);
}