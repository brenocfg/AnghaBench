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
struct unix_diag_req {scalar_t__ udiag_ino; int /*<<< orphan*/  udiag_cookie; } ;
struct unix_diag_msg {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {struct sock* sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  net_eq (struct net*,struct net*) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 
 int sk_diag_fill (struct sock*,struct sk_buff*,struct unix_diag_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int sock_diag_check_cookie (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sock* unix_lookup_by_ino (scalar_t__) ; 

__attribute__((used)) static int unix_diag_get_exact(struct sk_buff *in_skb,
			       const struct nlmsghdr *nlh,
			       struct unix_diag_req *req)
{
	int err = -EINVAL;
	struct sock *sk;
	struct sk_buff *rep;
	unsigned int extra_len;
	struct net *net = sock_net(in_skb->sk);

	if (req->udiag_ino == 0)
		goto out_nosk;

	sk = unix_lookup_by_ino(req->udiag_ino);
	err = -ENOENT;
	if (sk == NULL)
		goto out_nosk;
	if (!net_eq(sock_net(sk), net))
		goto out;

	err = sock_diag_check_cookie(sk, req->udiag_cookie);
	if (err)
		goto out;

	extra_len = 256;
again:
	err = -ENOMEM;
	rep = nlmsg_new(sizeof(struct unix_diag_msg) + extra_len, GFP_KERNEL);
	if (!rep)
		goto out;

	err = sk_diag_fill(sk, rep, req, NETLINK_CB(in_skb).portid,
			   nlh->nlmsg_seq, 0, req->udiag_ino);
	if (err < 0) {
		nlmsg_free(rep);
		extra_len += 256;
		if (extra_len >= PAGE_SIZE)
			goto out;

		goto again;
	}
	err = netlink_unicast(net->diag_nlsk, rep, NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	if (err > 0)
		err = 0;
out:
	if (sk)
		sock_put(sk);
out_nosk:
	return err;
}