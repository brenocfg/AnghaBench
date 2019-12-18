#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {scalar_t__ state; struct sock* sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct sock {TYPE_2__ sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct nfc_dev {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; scalar_t__ msg_namelen; } ;
struct TYPE_3__ {int tx_work_scheduled; int /*<<< orphan*/  tx_work; struct nfc_dev* dev; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 scalar_t__ SS_CONNECTED ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,size_t) ; 
 struct sk_buff* nfc_alloc_send_skb (struct nfc_dev*,struct sock*,int /*<<< orphan*/ ,size_t,int*) ; 
 TYPE_1__* nfc_rawsock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct socket*,struct sock*,size_t) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rawsock_sendmsg(struct socket *sock, struct msghdr *msg, size_t len)
{
	struct sock *sk = sock->sk;
	struct nfc_dev *dev = nfc_rawsock(sk)->dev;
	struct sk_buff *skb;
	int rc;

	pr_debug("sock=%p sk=%p len=%zu\n", sock, sk, len);

	if (msg->msg_namelen)
		return -EOPNOTSUPP;

	if (sock->state != SS_CONNECTED)
		return -ENOTCONN;

	skb = nfc_alloc_send_skb(dev, sk, msg->msg_flags, len, &rc);
	if (skb == NULL)
		return rc;

	rc = memcpy_from_msg(skb_put(skb, len), msg, len);
	if (rc < 0) {
		kfree_skb(skb);
		return rc;
	}

	spin_lock_bh(&sk->sk_write_queue.lock);
	__skb_queue_tail(&sk->sk_write_queue, skb);
	if (!nfc_rawsock(sk)->tx_work_scheduled) {
		schedule_work(&nfc_rawsock(sk)->tx_work);
		nfc_rawsock(sk)->tx_work_scheduled = true;
	}
	spin_unlock_bh(&sk->sk_write_queue.lock);

	return len;
}