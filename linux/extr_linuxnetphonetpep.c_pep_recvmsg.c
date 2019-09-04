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
struct sock {int sk_state; } ;
struct sk_buff {size_t len; } ;
struct pep_sock {int /*<<< orphan*/  ctrlreq_queue; } ;
struct msghdr {int msg_flags; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSG_CMSG_COMPAT ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_NOSIGNAL ; 
 int MSG_OOB ; 
 int MSG_PEEK ; 
 int MSG_TRUNC ; 
 int MSG_WAITALL ; 
 int /*<<< orphan*/  PN_PIPE_NO_ERROR ; 
 int /*<<< orphan*/  SOCK_URGINLINE ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 scalar_t__ TCP_CLOSE_WAIT ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  pep_ctrlreq_error (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int /*<<< orphan*/  pipe_grant_credits (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pep_recvmsg(struct sock *sk, struct msghdr *msg, size_t len,
		       int noblock, int flags, int *addr_len)
{
	struct sk_buff *skb;
	int err;

	if (flags & ~(MSG_OOB|MSG_PEEK|MSG_TRUNC|MSG_DONTWAIT|MSG_WAITALL|
			MSG_NOSIGNAL|MSG_CMSG_COMPAT))
		return -EOPNOTSUPP;

	if (unlikely(1 << sk->sk_state & (TCPF_LISTEN | TCPF_CLOSE)))
		return -ENOTCONN;

	if ((flags & MSG_OOB) || sock_flag(sk, SOCK_URGINLINE)) {
		/* Dequeue and acknowledge control request */
		struct pep_sock *pn = pep_sk(sk);

		if (flags & MSG_PEEK)
			return -EOPNOTSUPP;
		skb = skb_dequeue(&pn->ctrlreq_queue);
		if (skb) {
			pep_ctrlreq_error(sk, skb, PN_PIPE_NO_ERROR,
						GFP_KERNEL);
			msg->msg_flags |= MSG_OOB;
			goto copy;
		}
		if (flags & MSG_OOB)
			return -EINVAL;
	}

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	lock_sock(sk);
	if (skb == NULL) {
		if (err == -ENOTCONN && sk->sk_state == TCP_CLOSE_WAIT)
			err = -ECONNRESET;
		release_sock(sk);
		return err;
	}

	if (sk->sk_state == TCP_ESTABLISHED)
		pipe_grant_credits(sk, GFP_KERNEL);
	release_sock(sk);
copy:
	msg->msg_flags |= MSG_EOR;
	if (skb->len > len)
		msg->msg_flags |= MSG_TRUNC;
	else
		len = skb->len;

	err = skb_copy_datagram_msg(skb, 0, msg, len);
	if (!err)
		err = (flags & MSG_TRUNC) ? skb->len : len;

	skb_free_datagram(sk, skb);
	return err;
}