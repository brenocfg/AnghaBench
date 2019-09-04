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
struct tcp_sock {int /*<<< orphan*/  snd_nxt; } ;
struct sock {int dummy; } ;
struct bictcp {scalar_t__ sample_cnt; scalar_t__ curr_rtt; int /*<<< orphan*/  end_seq; int /*<<< orphan*/  last_ack; int /*<<< orphan*/  round_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  bictcp_clock () ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static inline void bictcp_hystart_reset(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct bictcp *ca = inet_csk_ca(sk);

	ca->round_start = ca->last_ack = bictcp_clock();
	ca->end_seq = tp->snd_nxt;
	ca->curr_rtt = 0;
	ca->sample_cnt = 0;
}