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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_check_reno_reordering (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_add_reno_sack(struct sock *sk, int num_dupack)
{
	if (num_dupack) {
		struct tcp_sock *tp = tcp_sk(sk);
		u32 prior_sacked = tp->sacked_out;
		s32 delivered;

		tp->sacked_out += num_dupack;
		tcp_check_reno_reordering(sk, 0);
		delivered = tp->sacked_out - prior_sacked;
		if (delivered > 0)
			tp->delivered += delivered;
		tcp_verify_left_out(tp);
	}
}