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
struct westwood {int reset_rtt_min; int first_ack; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  rtt_win_sx; int /*<<< orphan*/  rtt; int /*<<< orphan*/  rtt_min; scalar_t__ cumul_ack; scalar_t__ accounted; scalar_t__ bw_est; scalar_t__ bw_ns_est; scalar_t__ bk; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_una; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_WESTWOOD_INIT_RTT ; 
 struct westwood* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_westwood_init(struct sock *sk)
{
	struct westwood *w = inet_csk_ca(sk);

	w->bk = 0;
	w->bw_ns_est = 0;
	w->bw_est = 0;
	w->accounted = 0;
	w->cumul_ack = 0;
	w->reset_rtt_min = 1;
	w->rtt_min = w->rtt = TCP_WESTWOOD_INIT_RTT;
	w->rtt_win_sx = tcp_jiffies32;
	w->snd_una = tcp_sk(sk)->snd_una;
	w->first_ack = 1;
}