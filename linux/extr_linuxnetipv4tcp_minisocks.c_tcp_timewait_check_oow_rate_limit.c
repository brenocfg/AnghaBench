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
struct tcp_timewait_sock {int /*<<< orphan*/  tw_last_oow_ack_time; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_timewait_sock {int dummy; } ;
typedef  enum tcp_tw_status { ____Placeholder_tcp_tw_status } tcp_tw_status ;

/* Variables and functions */
 int TCP_TW_ACK ; 
 int TCP_TW_SUCCESS ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  tcp_oow_rate_limited (int /*<<< orphan*/ ,struct sk_buff const*,int,int /*<<< orphan*/ *) ; 
 struct tcp_timewait_sock* tcp_twsk (struct sock*) ; 
 int /*<<< orphan*/  twsk_net (struct inet_timewait_sock*) ; 

__attribute__((used)) static enum tcp_tw_status
tcp_timewait_check_oow_rate_limit(struct inet_timewait_sock *tw,
				  const struct sk_buff *skb, int mib_idx)
{
	struct tcp_timewait_sock *tcptw = tcp_twsk((struct sock *)tw);

	if (!tcp_oow_rate_limited(twsk_net(tw), skb, mib_idx,
				  &tcptw->tw_last_oow_ack_time)) {
		/* Send ACK. Note, we do not put the bucket,
		 * it will be released by caller.
		 */
		return TCP_TW_ACK;
	}

	/* We are rate-limiting, so just release the tw sock and drop skb. */
	inet_twsk_put(tw);
	return TCP_TW_SUCCESS;
}