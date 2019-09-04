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
typedef  scalar_t__ u32 ;
struct tcp_sock {scalar_t__ sacked_out; int /*<<< orphan*/  delivered; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_check_reno_reordering (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_add_reno_sack(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 prior_sacked = tp->sacked_out;

	tp->sacked_out++;
	tcp_check_reno_reordering(sk, 0);
	if (tp->sacked_out > prior_sacked)
		tp->delivered++; /* Some out-of-order packet is delivered */
	tcp_verify_left_out(tp);
}