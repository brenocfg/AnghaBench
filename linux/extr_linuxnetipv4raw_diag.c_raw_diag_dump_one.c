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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;
struct inet_diag_req_v2 {int dummy; } ;
struct inet_diag_msg {int dummy; } ;
struct inet_diag_meminfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sock*) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct sock*) ; 
 int inet_sk_diag_fill (struct sock*,int /*<<< orphan*/ *,struct sk_buff*,struct inet_diag_req_v2 const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlink_net_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 
 struct sock* raw_sock_get (struct net*,struct inet_diag_req_v2 const*) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int raw_diag_dump_one(struct sk_buff *in_skb,
			     const struct nlmsghdr *nlh,
			     const struct inet_diag_req_v2 *r)
{
	struct net *net = sock_net(in_skb->sk);
	struct sk_buff *rep;
	struct sock *sk;
	int err;

	sk = raw_sock_get(net, r);
	if (IS_ERR(sk))
		return PTR_ERR(sk);

	rep = nlmsg_new(sizeof(struct inet_diag_msg) +
			sizeof(struct inet_diag_meminfo) + 64,
			GFP_KERNEL);
	if (!rep) {
		sock_put(sk);
		return -ENOMEM;
	}

	err = inet_sk_diag_fill(sk, NULL, rep, r,
				sk_user_ns(NETLINK_CB(in_skb).sk),
				NETLINK_CB(in_skb).portid,
				nlh->nlmsg_seq, 0, nlh,
				netlink_net_capable(in_skb, CAP_NET_ADMIN));
	sock_put(sk);

	if (err < 0) {
		kfree_skb(rep);
		return err;
	}

	err = netlink_unicast(net->diag_nlsk, rep,
			      NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	if (err > 0)
		err = 0;
	return err;
}