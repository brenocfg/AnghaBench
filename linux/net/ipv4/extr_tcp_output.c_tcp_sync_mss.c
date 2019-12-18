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
typedef  scalar_t__ u32 ;
struct tcp_sock {int mss_cache; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ search_high; scalar_t__ search_low; scalar_t__ enabled; } ;
struct inet_connection_sock {TYPE_1__ icsk_mtup; scalar_t__ icsk_pmtu_cookie; } ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int min (int,int) ; 
 int tcp_bound_to_half_wnd (struct tcp_sock*,int) ; 
 int tcp_mtu_to_mss (struct sock*,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

unsigned int tcp_sync_mss(struct sock *sk, u32 pmtu)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	int mss_now;

	if (icsk->icsk_mtup.search_high > pmtu)
		icsk->icsk_mtup.search_high = pmtu;

	mss_now = tcp_mtu_to_mss(sk, pmtu);
	mss_now = tcp_bound_to_half_wnd(tp, mss_now);

	/* And store cached results */
	icsk->icsk_pmtu_cookie = pmtu;
	if (icsk->icsk_mtup.enabled)
		mss_now = min(mss_now, tcp_mtu_to_mss(sk, icsk->icsk_mtup.search_low));
	tp->mss_cache = mss_now;

	return mss_now;
}