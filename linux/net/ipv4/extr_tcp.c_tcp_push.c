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
struct tcp_sock {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_tsq_flags; } ;
struct sk_buff {scalar_t__ truesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPAUTOCORKING ; 
 int MSG_MORE ; 
 int /*<<< orphan*/  NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_NAGLE_CORK ; 
 int /*<<< orphan*/  TSQ_THROTTLED ; 
 int /*<<< orphan*/  __tcp_push_pending_frames (struct sock*,int,int) ; 
 scalar_t__ forced_push (struct tcp_sock*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_mark_push (struct tcp_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_mark_urg (struct tcp_sock*,int) ; 
 scalar_t__ tcp_should_autocork (struct sock*,struct sk_buff*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 struct sk_buff* tcp_write_queue_tail (struct sock*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcp_push(struct sock *sk, int flags, int mss_now,
		     int nonagle, int size_goal)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *skb;

	skb = tcp_write_queue_tail(sk);
	if (!skb)
		return;
	if (!(flags & MSG_MORE) || forced_push(tp))
		tcp_mark_push(tp, skb);

	tcp_mark_urg(tp, flags);

	if (tcp_should_autocork(sk, skb, size_goal)) {

		/* avoid atomic op if TSQ_THROTTLED bit is already set */
		if (!test_bit(TSQ_THROTTLED, &sk->sk_tsq_flags)) {
			NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPAUTOCORKING);
			set_bit(TSQ_THROTTLED, &sk->sk_tsq_flags);
		}
		/* It is possible TX completion already happened
		 * before we set TSQ_THROTTLED.
		 */
		if (refcount_read(&sk->sk_wmem_alloc) > skb->truesize)
			return;
	}

	if (flags & MSG_MORE)
		nonagle = TCP_NAGLE_CORK;

	__tcp_push_pending_frames(sk, mss_now, nonagle);
}