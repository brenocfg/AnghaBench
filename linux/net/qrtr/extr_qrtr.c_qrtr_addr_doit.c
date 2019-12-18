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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ifaddrmsg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EPERM ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 int /*<<< orphan*/  netlink_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  qrtr_local_nid ; 
 int /*<<< orphan*/  qrtr_policy ; 

__attribute__((used)) static int qrtr_addr_doit(struct sk_buff *skb, struct nlmsghdr *nlh,
			  struct netlink_ext_ack *extack)
{
	struct nlattr *tb[IFA_MAX + 1];
	struct ifaddrmsg *ifm;
	int rc;

	if (!netlink_capable(skb, CAP_NET_ADMIN))
		return -EPERM;

	if (!netlink_capable(skb, CAP_SYS_ADMIN))
		return -EPERM;

	ASSERT_RTNL();

	rc = nlmsg_parse_deprecated(nlh, sizeof(*ifm), tb, IFA_MAX,
				    qrtr_policy, extack);
	if (rc < 0)
		return rc;

	ifm = nlmsg_data(nlh);
	if (!tb[IFA_LOCAL])
		return -EINVAL;

	qrtr_local_nid = nla_get_u32(tb[IFA_LOCAL]);
	return 0;
}