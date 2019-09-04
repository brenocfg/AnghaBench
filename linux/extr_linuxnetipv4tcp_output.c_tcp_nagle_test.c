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
struct tcp_sock {int dummy; } ;
struct sk_buff {unsigned int len; } ;
struct TYPE_2__ {int tcp_flags; } ;

/* Variables and functions */
 int TCPHDR_FIN ; 
 int TCP_NAGLE_PUSH ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  tcp_nagle_check (int,struct tcp_sock const*,int) ; 
 scalar_t__ tcp_urg_mode (struct tcp_sock const*) ; 

__attribute__((used)) static inline bool tcp_nagle_test(const struct tcp_sock *tp, const struct sk_buff *skb,
				  unsigned int cur_mss, int nonagle)
{
	/* Nagle rule does not apply to frames, which sit in the middle of the
	 * write_queue (they have no chances to get new data).
	 *
	 * This is implemented in the callers, where they modify the 'nonagle'
	 * argument based upon the location of SKB in the send queue.
	 */
	if (nonagle & TCP_NAGLE_PUSH)
		return true;

	/* Don't use the nagle rule for urgent data (or for the final FIN). */
	if (tcp_urg_mode(tp) || (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN))
		return true;

	if (!tcp_nagle_check(skb->len < cur_mss, tp, nonagle))
		return true;

	return false;
}