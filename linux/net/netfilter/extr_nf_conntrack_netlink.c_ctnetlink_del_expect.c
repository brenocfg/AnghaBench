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
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int /*<<< orphan*/  nfgen_family; } ;
struct nf_conntrack_zone {int dummy; } ;
struct nf_conntrack_tuple {int dummy; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  timeout; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 size_t CTA_EXPECT_HELP_NAME ; 
 size_t CTA_EXPECT_ID ; 
 size_t CTA_EXPECT_TUPLE ; 
 size_t CTA_EXPECT_ZONE ; 
 int ENOENT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int ctnetlink_parse_tuple (struct nlattr const* const*,struct nf_conntrack_tuple*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ctnetlink_parse_zone (struct nlattr const* const,struct nf_conntrack_zone*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect_iter_all ; 
 int /*<<< orphan*/  expect_iter_name ; 
 int /*<<< orphan*/  nf_conntrack_expect_lock ; 
 struct nf_conntrack_expect* nf_ct_expect_find_get (struct net*,struct nf_conntrack_zone*,struct nf_conntrack_tuple*) ; 
 int /*<<< orphan*/  nf_ct_expect_iterate_net (struct net*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_unlink_expect_report (struct nf_conntrack_expect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctnetlink_del_expect(struct net *net, struct sock *ctnl,
				struct sk_buff *skb, const struct nlmsghdr *nlh,
				const struct nlattr * const cda[],
				struct netlink_ext_ack *extack)
{
	struct nf_conntrack_expect *exp;
	struct nf_conntrack_tuple tuple;
	struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u_int8_t u3 = nfmsg->nfgen_family;
	struct nf_conntrack_zone zone;
	int err;

	if (cda[CTA_EXPECT_TUPLE]) {
		/* delete a single expect by tuple */
		err = ctnetlink_parse_zone(cda[CTA_EXPECT_ZONE], &zone);
		if (err < 0)
			return err;

		err = ctnetlink_parse_tuple(cda, &tuple, CTA_EXPECT_TUPLE,
					    u3, NULL);
		if (err < 0)
			return err;

		/* bump usage count to 2 */
		exp = nf_ct_expect_find_get(net, &zone, &tuple);
		if (!exp)
			return -ENOENT;

		if (cda[CTA_EXPECT_ID]) {
			__be32 id = nla_get_be32(cda[CTA_EXPECT_ID]);
			if (ntohl(id) != (u32)(unsigned long)exp) {
				nf_ct_expect_put(exp);
				return -ENOENT;
			}
		}

		/* after list removal, usage count == 1 */
		spin_lock_bh(&nf_conntrack_expect_lock);
		if (del_timer(&exp->timeout)) {
			nf_ct_unlink_expect_report(exp, NETLINK_CB(skb).portid,
						   nlmsg_report(nlh));
			nf_ct_expect_put(exp);
		}
		spin_unlock_bh(&nf_conntrack_expect_lock);
		/* have to put what we 'get' above.
		 * after this line usage count == 0 */
		nf_ct_expect_put(exp);
	} else if (cda[CTA_EXPECT_HELP_NAME]) {
		char *name = nla_data(cda[CTA_EXPECT_HELP_NAME]);

		nf_ct_expect_iterate_net(net, expect_iter_name, name,
					 NETLINK_CB(skb).portid,
					 nlmsg_report(nlh));
	} else {
		/* This basically means we have to flush everything*/
		nf_ct_expect_iterate_net(net, expect_iter_all, NULL,
					 NETLINK_CB(skb).portid,
					 nlmsg_report(nlh));
	}

	return 0;
}