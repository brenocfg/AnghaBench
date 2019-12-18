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
struct socket {struct sock* sk; } ;
struct sock {int sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dump; } ;
struct pfkey_sock {TYPE_1__ dump; } ;
struct msghdr {int msg_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int MSG_CMSG_COMPAT ; 
 int MSG_DONTWAIT ; 
 int MSG_PEEK ; 
 int MSG_TRUNC ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfkey_do_dump (struct pfkey_sock*) ; 
 struct pfkey_sock* pfkey_sk (struct sock*) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_recv_ts_and_drops (struct msghdr*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int pfkey_recvmsg(struct socket *sock, struct msghdr *msg, size_t len,
			 int flags)
{
	struct sock *sk = sock->sk;
	struct pfkey_sock *pfk = pfkey_sk(sk);
	struct sk_buff *skb;
	int copied, err;

	err = -EINVAL;
	if (flags & ~(MSG_PEEK|MSG_DONTWAIT|MSG_TRUNC|MSG_CMSG_COMPAT))
		goto out;

	skb = skb_recv_datagram(sk, flags, flags & MSG_DONTWAIT, &err);
	if (skb == NULL)
		goto out;

	copied = skb->len;
	if (copied > len) {
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	}

	skb_reset_transport_header(skb);
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	if (err)
		goto out_free;

	sock_recv_ts_and_drops(msg, sk, skb);

	err = (flags & MSG_TRUNC) ? skb->len : copied;

	if (pfk->dump.dump != NULL &&
	    3 * atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf)
		pfkey_do_dump(pfk);

out_free:
	skb_free_datagram(sk, skb);
out:
	return err;
}