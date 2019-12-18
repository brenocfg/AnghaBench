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
struct inet_hashinfo {int dummy; } ;
struct inet_diag_req_v2 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sock*) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct sock*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sock* inet_diag_find_one_icsk (struct net*,struct inet_hashinfo*,struct inet_diag_req_v2 const*) ; 
 int /*<<< orphan*/  inet_sk_attr_size (struct sock*,struct inet_diag_req_v2 const*,int) ; 
 int netlink_net_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sk_diag_fill (struct sock*,struct sk_buff*,struct inet_diag_req_v2 const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*,int) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_gen_put (struct sock*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int inet_diag_dump_one_icsk(struct inet_hashinfo *hashinfo,
			    struct sk_buff *in_skb,
			    const struct nlmsghdr *nlh,
			    const struct inet_diag_req_v2 *req)
{
	bool net_admin = netlink_net_capable(in_skb, CAP_NET_ADMIN);
	struct net *net = sock_net(in_skb->sk);
	struct sk_buff *rep;
	struct sock *sk;
	int err;

	sk = inet_diag_find_one_icsk(net, hashinfo, req);
	if (IS_ERR(sk))
		return PTR_ERR(sk);

	rep = nlmsg_new(inet_sk_attr_size(sk, req, net_admin), GFP_KERNEL);
	if (!rep) {
		err = -ENOMEM;
		goto out;
	}

	err = sk_diag_fill(sk, rep, req,
			   sk_user_ns(NETLINK_CB(in_skb).sk),
			   NETLINK_CB(in_skb).portid,
			   nlh->nlmsg_seq, 0, nlh, net_admin);
	if (err < 0) {
		WARN_ON(err == -EMSGSIZE);
		nlmsg_free(rep);
		goto out;
	}
	err = netlink_unicast(net->diag_nlsk, rep, NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	if (err > 0)
		err = 0;

out:
	if (sk)
		sock_gen_put(sk);

	return err;
}