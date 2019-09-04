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
typedef  int u32 ;
struct sock {int sk_rcvbuf; int sk_sndbuf; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPBACKLOGDROP ; 
 int /*<<< orphan*/  __NET_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_add_backlog (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_condense (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

bool tcp_add_backlog(struct sock *sk, struct sk_buff *skb)
{
	u32 limit = sk->sk_rcvbuf + sk->sk_sndbuf;

	/* Only socket owner can try to collapse/prune rx queues
	 * to reduce memory overhead, so add a little headroom here.
	 * Few sockets backlog are possibly concurrently non empty.
	 */
	limit += 64*1024;

	/* In case all data was pulled from skb frags (in __pskb_pull_tail()),
	 * we can fix skb->truesize to its real value to avoid future drops.
	 * This is valid because skb is not yet charged to the socket.
	 * It has been noticed pure SACK packets were sometimes dropped
	 * (if cooked by drivers without copybreak feature).
	 */
	skb_condense(skb);

	if (unlikely(sk_add_backlog(sk, skb, limit))) {
		bh_unlock_sock(sk);
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPBACKLOGDROP);
		return true;
	}
	return false;
}