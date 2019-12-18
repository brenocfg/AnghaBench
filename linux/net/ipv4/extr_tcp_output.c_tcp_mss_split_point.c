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
typedef  unsigned int u32 ;
struct tcp_sock {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {unsigned int seq; } ;

/* Variables and functions */
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 scalar_t__ likely (int) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ tcp_nagle_check (int,struct tcp_sock const*,int) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 
 unsigned int tcp_wnd_end (struct tcp_sock const*) ; 
 struct sk_buff const* tcp_write_queue_tail (struct sock const*) ; 

__attribute__((used)) static unsigned int tcp_mss_split_point(const struct sock *sk,
					const struct sk_buff *skb,
					unsigned int mss_now,
					unsigned int max_segs,
					int nonagle)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	u32 partial, needed, window, max_len;

	window = tcp_wnd_end(tp) - TCP_SKB_CB(skb)->seq;
	max_len = mss_now * max_segs;

	if (likely(max_len <= window && skb != tcp_write_queue_tail(sk)))
		return max_len;

	needed = min(skb->len, window);

	if (max_len <= needed)
		return max_len;

	partial = needed % mss_now;
	/* If last segment is not a full MSS, check if Nagle rules allow us
	 * to include this last segment in this skb.
	 * Otherwise, we'll split the skb at last MSS boundary
	 */
	if (tcp_nagle_check(partial != 0, tp, nonagle))
		return needed - partial;

	return needed;
}