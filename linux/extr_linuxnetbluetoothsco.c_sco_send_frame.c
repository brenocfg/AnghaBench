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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sco_conn {int mtu; int /*<<< orphan*/  hcon; } ;
struct msghdr {int msg_flags; } ;
struct TYPE_2__ {struct sco_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int) ; 
 int EFAULT ; 
 int EINVAL ; 
 int MSG_DONTWAIT ; 
 struct sk_buff* bt_skb_send_alloc (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  hci_send_sco (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ memcpy_from_msg (int /*<<< orphan*/ ,struct msghdr*,int) ; 
 TYPE_1__* sco_pi (struct sock*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int sco_send_frame(struct sock *sk, struct msghdr *msg, int len)
{
	struct sco_conn *conn = sco_pi(sk)->conn;
	struct sk_buff *skb;
	int err;

	/* Check outgoing MTU */
	if (len > conn->mtu)
		return -EINVAL;

	BT_DBG("sk %p len %d", sk, len);

	skb = bt_skb_send_alloc(sk, len, msg->msg_flags & MSG_DONTWAIT, &err);
	if (!skb)
		return err;

	if (memcpy_from_msg(skb_put(skb, len), msg, len)) {
		kfree_skb(skb);
		return -EFAULT;
	}

	hci_send_sco(conn->hcon, skb);

	return len;
}