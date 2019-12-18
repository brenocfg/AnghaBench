#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct sctp_transport {struct sctp_association* asoc; } ;
struct sctp_comm_param {int /*<<< orphan*/  net_admin; struct nlmsghdr* nlh; struct inet_diag_req_v2* r; struct sk_buff* skb; } ;
struct TYPE_5__ {struct sock* sk; } ;
struct sctp_association {TYPE_2__ base; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int /*<<< orphan*/  diag_nlsk; } ;
struct TYPE_4__ {int /*<<< orphan*/  idiag_cookie; } ;
struct inet_diag_req_v2 {TYPE_1__ id; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_3__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  inet_assoc_attr_size (struct sctp_association*) ; 
 int inet_sctp_diag_fill (struct sock*,struct sctp_association*,struct sk_buff*,struct inet_diag_req_v2 const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 
 int sock_diag_check_cookie (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_tsp_dump_one(struct sctp_transport *tsp, void *p)
{
	struct sctp_association *assoc = tsp->asoc;
	struct sock *sk = tsp->asoc->base.sk;
	struct sctp_comm_param *commp = p;
	struct sk_buff *in_skb = commp->skb;
	const struct inet_diag_req_v2 *req = commp->r;
	const struct nlmsghdr *nlh = commp->nlh;
	struct net *net = sock_net(in_skb->sk);
	struct sk_buff *rep;
	int err;

	err = sock_diag_check_cookie(sk, req->id.idiag_cookie);
	if (err)
		goto out;

	err = -ENOMEM;
	rep = nlmsg_new(inet_assoc_attr_size(assoc), GFP_KERNEL);
	if (!rep)
		goto out;

	lock_sock(sk);
	if (sk != assoc->base.sk) {
		release_sock(sk);
		sk = assoc->base.sk;
		lock_sock(sk);
	}
	err = inet_sctp_diag_fill(sk, assoc, rep, req,
				  sk_user_ns(NETLINK_CB(in_skb).sk),
				  NETLINK_CB(in_skb).portid,
				  nlh->nlmsg_seq, 0, nlh,
				  commp->net_admin);
	release_sock(sk);
	if (err < 0) {
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(rep);
		goto out;
	}

	err = netlink_unicast(net->diag_nlsk, rep, NETLINK_CB(in_skb).portid,
			      MSG_DONTWAIT);
	if (err > 0)
		err = 0;
out:
	return err;
}