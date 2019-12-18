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
struct rtgenmsg {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NETNSA_FD 131 
 int NETNSA_MAX ; 
#define  NETNSA_NSID 130 
#define  NETNSA_PID 129 
#define  NETNSA_TARGET_NSID 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  netlink_strict_get_check (struct sk_buff*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtnl_net_policy ; 

__attribute__((used)) static int rtnl_net_valid_getid_req(struct sk_buff *skb,
				    const struct nlmsghdr *nlh,
				    struct nlattr **tb,
				    struct netlink_ext_ack *extack)
{
	int i, err;

	if (!netlink_strict_get_check(skb))
		return nlmsg_parse_deprecated(nlh, sizeof(struct rtgenmsg),
					      tb, NETNSA_MAX, rtnl_net_policy,
					      extack);

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(struct rtgenmsg), tb,
					    NETNSA_MAX, rtnl_net_policy,
					    extack);
	if (err)
		return err;

	for (i = 0; i <= NETNSA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case NETNSA_PID:
		case NETNSA_FD:
		case NETNSA_NSID:
		case NETNSA_TARGET_NSID:
			break;
		default:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in peer netns getid request");
			return -EINVAL;
		}
	}

	return 0;
}