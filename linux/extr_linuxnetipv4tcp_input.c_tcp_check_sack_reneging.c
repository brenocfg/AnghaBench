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
struct tcp_sock {int srtt_us; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int FLAG_SACK_RENEGING ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  TCP_RTO_MAX ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static bool tcp_check_sack_reneging(struct sock *sk, int flag)
{
	if (flag & FLAG_SACK_RENEGING) {
		struct tcp_sock *tp = tcp_sk(sk);
		unsigned long delay = max(usecs_to_jiffies(tp->srtt_us >> 4),
					  msecs_to_jiffies(10));

		inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
					  delay, TCP_RTO_MAX);
		return true;
	}
	return false;
}