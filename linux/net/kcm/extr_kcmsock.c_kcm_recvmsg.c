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
struct strp_msg {size_t full_len; int offset; } ;
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_msgs; int /*<<< orphan*/  rx_bytes; } ;
struct kcm_sock {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_STATS_ADD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KCM_STATS_INCR (int /*<<< orphan*/ ) ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  MSG_TRUNC ; 
 scalar_t__ SOCK_DGRAM ; 
 struct kcm_sock* kcm_sk (struct sock*) ; 
 struct sk_buff* kcm_wait_data (struct sock*,int,long,int*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 long sock_rcvtimeo (struct sock*,int) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 

__attribute__((used)) static int kcm_recvmsg(struct socket *sock, struct msghdr *msg,
		       size_t len, int flags)
{
	struct sock *sk = sock->sk;
	struct kcm_sock *kcm = kcm_sk(sk);
	int err = 0;
	long timeo;
	struct strp_msg *stm;
	int copied = 0;
	struct sk_buff *skb;

	timeo = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);

	lock_sock(sk);

	skb = kcm_wait_data(sk, flags, timeo, &err);
	if (!skb)
		goto out;

	/* Okay, have a message on the receive queue */

	stm = strp_msg(skb);

	if (len > stm->full_len)
		len = stm->full_len;

	err = skb_copy_datagram_msg(skb, stm->offset, msg, len);
	if (err < 0)
		goto out;

	copied = len;
	if (likely(!(flags & MSG_PEEK))) {
		KCM_STATS_ADD(kcm->stats.rx_bytes, copied);
		if (copied < stm->full_len) {
			if (sock->type == SOCK_DGRAM) {
				/* Truncated message */
				msg->msg_flags |= MSG_TRUNC;
				goto msg_finished;
			}
			stm->offset += copied;
			stm->full_len -= copied;
		} else {
msg_finished:
			/* Finished with message */
			msg->msg_flags |= MSG_EOR;
			KCM_STATS_INCR(kcm->stats.rx_msgs);
			skb_unlink(skb, &sk->sk_receive_queue);
			kfree_skb(skb);
		}
	}

out:
	release_sock(sk);

	return copied ? : err;
}