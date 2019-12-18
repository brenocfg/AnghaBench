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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pipe_inode_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; } ;
struct kcm_sock {TYPE_1__ stats; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  KCM_STATS_ADD (int /*<<< orphan*/ ,int) ; 
 unsigned int MSG_DONTWAIT ; 
 struct kcm_sock* kcm_sk (struct sock*) ; 
 struct sk_buff* kcm_wait_data (struct sock*,unsigned int,long,int*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int skb_splice_bits (struct sk_buff*,struct sock*,int,struct pipe_inode_info*,size_t,unsigned int) ; 
 long sock_rcvtimeo (struct sock*,unsigned int) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 

__attribute__((used)) static ssize_t kcm_splice_read(struct socket *sock, loff_t *ppos,
			       struct pipe_inode_info *pipe, size_t len,
			       unsigned int flags)
{
	struct sock *sk = sock->sk;
	struct kcm_sock *kcm = kcm_sk(sk);
	long timeo;
	struct strp_msg *stm;
	int err = 0;
	ssize_t copied;
	struct sk_buff *skb;

	/* Only support splice for SOCKSEQPACKET */

	timeo = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);

	lock_sock(sk);

	skb = kcm_wait_data(sk, flags, timeo, &err);
	if (!skb)
		goto err_out;

	/* Okay, have a message on the receive queue */

	stm = strp_msg(skb);

	if (len > stm->full_len)
		len = stm->full_len;

	copied = skb_splice_bits(skb, sk, stm->offset, pipe, len, flags);
	if (copied < 0) {
		err = copied;
		goto err_out;
	}

	KCM_STATS_ADD(kcm->stats.rx_bytes, copied);

	stm->offset += copied;
	stm->full_len -= copied;

	/* We have no way to return MSG_EOR. If all the bytes have been
	 * read we still leave the message in the receive socket buffer.
	 * A subsequent recvmsg needs to be done to return MSG_EOR and
	 * finish reading the message.
	 */

	release_sock(sk);

	return copied;

err_out:
	release_sock(sk);

	return err;
}