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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_expect {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  done; int /*<<< orphan*/  dump; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 size_t CTA_EXPECT_ID ; 
 size_t CTA_EXPECT_MASTER ; 
 size_t CTA_EXPECT_TUPLE ; 
 size_t CTA_EXPECT_ZONE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPCTNL_MSG_EXP_NEW ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int NLM_F_DUMP ; 
 int ctnetlink_dump_exp_ct (struct net*,struct sock*,struct sk_buff*,struct nlmsghdr const*,struct nlattr const* const*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  ctnetlink_exp_done ; 
 int /*<<< orphan*/  ctnetlink_exp_dump_table ; 
 int ctnetlink_exp_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_conntrack_expect*) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ctnetlink_parse_zone (struct nlattr const* const,struct nf_conntrack_zone*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_dump_start (struct sock*,struct sk_buff*,struct nlmsghdr const*,struct netlink_dump_control*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_expect* nf_ct_expect_find_get (struct net*,struct nf_conntrack_zone*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 scalar_t__ nf_expect_get_id (struct nf_conntrack_expect*) ; 
 scalar_t__ nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int ctnetlink_get_expect(struct net *net, struct sock *ctnl,
				struct sk_buff *skb, const struct nlmsghdr *nlh,
				const struct nlattr * const cda[],
				struct netlink_ext_ack *extack)
{
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_expect *exp;
	struct sk_buff *skb2;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int8_t u3 = nfmsg->nfgen_family;
	struct nf_conntrack_zone zone;
	int err;

	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		if (cda[CTA_EXPECT_MASTER])
			return ctnetlink_dump_exp_ct(net, ctnl, skb, nlh, cda,
						     extack);
		else {
			struct netlink_dump_control c = {
				.dump = ctnetlink_exp_dump_table,
				.done = ctnetlink_exp_done,
			};
			return netlink_dump_start(ctnl, skb, nlh, &c);
		}
	}

	err = ctnetlink_parse_zone(cda[CTA_EXPECT_ZONE], &zone);
	if (err < 0)
		return err;

	if (cda[CTA_EXPECT_TUPLE])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_TUPLE,
					    u3, NULL);
	else if (cda[CTA_EXPECT_MASTER])
		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_MASTER,
					    u3, NULL);
	else
		return -EINVAL;

	if (err < 0)
		return err;

	exp = nf_ct_expect_find_get(net, &zone, &tuple);
	if (!exp)
		return -ENOENT;

	if (cda[CTA_EXPECT_ID]) {
		__be32 id = nla_get_be32(cda[CTA_EXPECT_ID]);

		if (id != nf_expect_get_id(exp)) {
			nf_ct_expect_put(exp);
			return -ENOENT;
		}
	}

	err = -ENOMEM;
	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb2 == NULL) {
		nf_ct_expect_put(exp);
		goto out;
	}

	rcu_read_lock();
	err = ctnetlink_exp_fill_info(skb2, NETLINK_CB(skb).portid,
				      nlh->nlmsg_seq, IPCTNL_MSG_EXP_NEW, exp);
	rcu_read_unlock();
	nf_ct_expect_put(exp);
	if (err <= 0)
		goto free;

	err = netlink_unicast(ctnl, skb2, NETLINK_CB(skb).portid, MSG_DONTWAIT);
	if (err < 0)
		goto out;

	return 0;

free:
	kfree_skb(skb2);
out:
	/* this avoids a loop in nfnetlink. */
	return err == -EAGAIN ? -ENOBUFS : err;
}