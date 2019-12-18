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
struct tcp_sock {scalar_t__ reordering; scalar_t__ lost_out; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ tcp_dupack_heuristics (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_is_rack (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static bool tcp_time_to_recover(struct sock *sk, int flag)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/* Trick#1: The loss is proven. */
	if (tp->lost_out)
		return true;

	/* Not-A-Trick#2 : Classic rule... */
	if (!tcp_is_rack(sk) && tcp_dupack_heuristics(tp) > tp->reordering)
		return true;

	return false;
}