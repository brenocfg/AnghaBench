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
struct tcp_sock {int /*<<< orphan*/  snd_cwnd; } ;
struct sock {int dummy; } ;
struct bbr {int /*<<< orphan*/  prior_cwnd; int /*<<< orphan*/  min_rtt_stamp; scalar_t__ probe_rtt_done_stamp; } ;

/* Variables and functions */
 scalar_t__ after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bbr_reset_mode (struct sock*) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bbr_check_probe_rtt_done(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bbr *bbr = inet_csk_ca(sk);

	if (!(bbr->probe_rtt_done_stamp &&
	      after(tcp_jiffies32, bbr->probe_rtt_done_stamp)))
		return;

	bbr->min_rtt_stamp = tcp_jiffies32;  /* wait a while until PROBE_RTT */
	tp->snd_cwnd = max(tp->snd_cwnd, bbr->prior_cwnd);
	bbr_reset_mode(sk);
}