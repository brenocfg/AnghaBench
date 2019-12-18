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
struct tcp_sock {scalar_t__ snd_ssthresh; scalar_t__ snd_cwnd; int /*<<< orphan*/  snd_cwnd_stamp; scalar_t__ undo_marker; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {scalar_t__ icsk_ca_state; TYPE_1__* icsk_ca_ops; } ;
struct TYPE_3__ {scalar_t__ cong_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_COMPLETE_CWR ; 
 scalar_t__ TCP_CA_CWR ; 
 scalar_t__ TCP_INFINITE_SSTHRESH ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static inline void tcp_end_cwnd_reduction(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (inet_csk(sk)->icsk_ca_ops->cong_control)
		return;

	/* Reset cwnd to ssthresh in CWR or Recovery (unless it's undone) */
	if (tp->snd_ssthresh < TCP_INFINITE_SSTHRESH &&
	    (inet_csk(sk)->icsk_ca_state == TCP_CA_CWR || tp->undo_marker)) {
		tp->snd_cwnd = tp->snd_ssthresh;
		tp->snd_cwnd_stamp = tcp_jiffies32;
	}
	tcp_ca_event(sk, CA_EVENT_COMPLETE_CWR);
}