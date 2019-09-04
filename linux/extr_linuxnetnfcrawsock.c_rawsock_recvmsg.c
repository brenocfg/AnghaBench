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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 int /*<<< orphan*/  pr_debug (char*,struct socket*,struct sock*,size_t,int) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 

__attribute__((used)) static int rawsock_recvmsg(struct socket *sock, struct msghdr *msg, size_t len,
			   int flags)
{
	int noblock = flags & MSG_DONTWAIT;
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	int copied;
	int rc;

	pr_debug("sock=%p sk=%p len=%zu flags=%d\n", sock, sk, len, flags);

	skb = skb_recv_datagram(sk, flags, noblock, &rc);
	if (!skb)
		return rc;

	copied = skb->len;
	if (len < copied) {
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	}

	rc = skb_copy_datagram_msg(skb, 0, msg, copied);

	skb_free_datagram(sk, skb);

	return rc ? : copied;
}