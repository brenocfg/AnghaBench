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
struct tcp_sock {int reordering; int mss_cache; scalar_t__ snd_una; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tcp_highest_sack_seq (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static bool tcp_force_fast_retransmit(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	return after(tcp_highest_sack_seq(tp),
		     tp->snd_una + tp->reordering * tp->mss_cache);
}