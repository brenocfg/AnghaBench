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
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {unsigned int len; } ;
struct msghdr {int msg_flags; } ;
struct TYPE_2__ {int channel; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int EOPNOTSUPP ; 
 int HCI_CHANNEL_LOGGING ; 
#define  HCI_CHANNEL_MONITOR 130 
#define  HCI_CHANNEL_RAW 129 
#define  HCI_CHANNEL_USER 128 
 int MSG_DONTWAIT ; 
 int MSG_OOB ; 
 int MSG_TRUNC ; 
 int /*<<< orphan*/  hci_mgmt_chan_find (int) ; 
 TYPE_1__* hci_pi (struct sock*) ; 
 int /*<<< orphan*/  hci_sock_cmsg (struct sock*,struct msghdr*,struct sk_buff*) ; 
 int skb_copy_datagram_msg (struct sk_buff*,int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_recv_timestamp (struct msghdr*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int hci_sock_recvmsg(struct socket *sock, struct msghdr *msg,
			    size_t len, int flags)
{
	int noblock = flags & MSG_DONTWAIT;
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	int copied, err;
	unsigned int skblen;

	BT_DBG("sock %p, sk %p", sock, sk);

	if (flags & MSG_OOB)
		return -EOPNOTSUPP;

	if (hci_pi(sk)->channel == HCI_CHANNEL_LOGGING)
		return -EOPNOTSUPP;

	if (sk->sk_state == BT_CLOSED)
		return 0;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	if (!skb)
		return err;

	skblen = skb->len;
	copied = skb->len;
	if (len < copied) {
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	}

	skb_reset_transport_header(skb);
	err = skb_copy_datagram_msg(skb, 0, msg, copied);

	switch (hci_pi(sk)->channel) {
	case HCI_CHANNEL_RAW:
		hci_sock_cmsg(sk, msg, skb);
		break;
	case HCI_CHANNEL_USER:
	case HCI_CHANNEL_MONITOR:
		sock_recv_timestamp(msg, sk, skb);
		break;
	default:
		if (hci_mgmt_chan_find(hci_pi(sk)->channel))
			sock_recv_timestamp(msg, sk, skb);
		break;
	}

	skb_free_datagram(sk, skb);

	if (flags & MSG_TRUNC)
		copied = skblen;

	return err ? : copied;
}