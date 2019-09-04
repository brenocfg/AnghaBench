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
struct sock_exterr_skb {int /*<<< orphan*/  ee; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MSG_ERRQUEUE ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int,int,int,int /*<<< orphan*/ *) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int /*<<< orphan*/ ,struct msghdr*,int) ; 
 struct sk_buff* sock_dequeue_err_skb (struct sock*) ; 
 int /*<<< orphan*/  sock_recv_timestamp (struct msghdr*,struct sock*,struct sk_buff*) ; 

int sock_recv_errqueue(struct sock *sk, struct msghdr *msg, int len,
		       int level, int type)
{
	struct sock_exterr_skb *serr;
	struct sk_buff *skb;
	int copied, err;

	err = -EAGAIN;
	skb = sock_dequeue_err_skb(sk);
	if (skb == NULL)
		goto out;

	copied = skb->len;
	if (copied > len) {
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	}
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	if (err)
		goto out_free_skb;

	sock_recv_timestamp(msg, sk, skb);

	serr = SKB_EXT_ERR(skb);
	put_cmsg(msg, level, type, sizeof(serr->ee), &serr->ee);

	msg->msg_flags |= MSG_ERRQUEUE;
	err = copied;

out_free_skb:
	kfree_skb(skb);
out:
	return err;
}