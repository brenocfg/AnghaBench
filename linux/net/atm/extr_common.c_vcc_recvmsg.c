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
struct socket {scalar_t__ state; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int len; int /*<<< orphan*/  truesize; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct atm_vcc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  ATM_VF_CLOSE ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int MSG_DONTWAIT ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 scalar_t__ SS_CONNECTED ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  sock_recv_ts_and_drops (struct msghdr*,struct sock*,struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int vcc_recvmsg(struct socket *sock, struct msghdr *msg, size_t size,
		int flags)
{
	struct sock *sk = sock->sk;
	struct atm_vcc *vcc;
	struct sk_buff *skb;
	int copied, error = -EINVAL;

	if (sock->state != SS_CONNECTED)
		return -ENOTCONN;

	/* only handle MSG_DONTWAIT and MSG_PEEK */
	if (flags & ~(MSG_DONTWAIT | MSG_PEEK))
		return -EOPNOTSUPP;

	vcc = ATM_SD(sock);
	if (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags))
		return 0;

	skb = skb_recv_datagram(sk, flags, flags & MSG_DONTWAIT, &error);
	if (!skb)
		return error;

	copied = skb->len;
	if (copied > size) {
		copied = size;
		msg->msg_flags |= MSG_TRUNC;
	}

	error = skb_copy_datagram_msg(skb, 0, msg, copied);
	if (error)
		return error;
	sock_recv_ts_and_drops(msg, sk, skb);

	if (!(flags & MSG_PEEK)) {
		pr_debug("%d -= %d\n", atomic_read(&sk->sk_rmem_alloc),
			 skb->truesize);
		atm_return(vcc, skb->truesize);
	}

	skb_free_datagram(sk, skb);
	return copied;
}