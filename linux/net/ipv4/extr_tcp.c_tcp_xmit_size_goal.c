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
typedef  unsigned int u32 ;
struct tcp_sock {unsigned int gso_segs; } ;
struct sock {int sk_gso_max_size; int /*<<< orphan*/  sk_gso_max_segs; } ;

/* Variables and functions */
 int MAX_TCP_HEADER ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int tcp_bound_to_half_wnd (struct tcp_sock*,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  u16 ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int tcp_xmit_size_goal(struct sock *sk, u32 mss_now,
				       int large_allowed)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 new_size_goal, size_goal;

	if (!large_allowed)
		return mss_now;

	/* Note : tcp_tso_autosize() will eventually split this later */
	new_size_goal = sk->sk_gso_max_size - 1 - MAX_TCP_HEADER;
	new_size_goal = tcp_bound_to_half_wnd(tp, new_size_goal);

	/* We try hard to avoid divides here */
	size_goal = tp->gso_segs * mss_now;
	if (unlikely(new_size_goal < size_goal ||
		     new_size_goal >= size_goal + mss_now)) {
		tp->gso_segs = min_t(u16, new_size_goal / mss_now,
				     sk->sk_gso_max_segs);
		size_goal = tp->gso_segs * mss_now;
	}

	return max(size_goal, mss_now);
}