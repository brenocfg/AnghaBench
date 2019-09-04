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
struct sockaddr_can {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {size_t len; int /*<<< orphan*/  cb; int /*<<< orphan*/  data; } ;
struct msghdr {int msg_namelen; scalar_t__ msg_name; } ;

/* Variables and functions */
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  __sockaddr_check_size (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int memcpy_to_msg (struct msghdr*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_free_datagram (struct sock*,struct sk_buff*) ; 
 struct sk_buff* skb_recv_datagram (struct sock*,int,int,int*) ; 
 int /*<<< orphan*/  sock_recv_ts_and_drops (struct msghdr*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int bcm_recvmsg(struct socket *sock, struct msghdr *msg, size_t size,
		       int flags)
{
	struct sock *sk = sock->sk;
	struct sk_buff *skb;
	int error = 0;
	int noblock;
	int err;

	noblock =  flags & MSG_DONTWAIT;
	flags   &= ~MSG_DONTWAIT;
	skb = skb_recv_datagram(sk, flags, noblock, &error);
	if (!skb)
		return error;

	if (skb->len < size)
		size = skb->len;

	err = memcpy_to_msg(msg, skb->data, size);
	if (err < 0) {
		skb_free_datagram(sk, skb);
		return err;
	}

	sock_recv_ts_and_drops(msg, sk, skb);

	if (msg->msg_name) {
		__sockaddr_check_size(sizeof(struct sockaddr_can));
		msg->msg_namelen = sizeof(struct sockaddr_can);
		memcpy(msg->msg_name, skb->cb, msg->msg_namelen);
	}

	skb_free_datagram(sk, skb);

	return size;
}