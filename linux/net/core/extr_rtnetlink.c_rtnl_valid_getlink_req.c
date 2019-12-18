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
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ifinfomsg {scalar_t__ ifi_change; scalar_t__ ifi_flags; scalar_t__ ifi_type; scalar_t__ __ifi_pad; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IFLA_EXT_MASK 130 
#define  IFLA_IFNAME 129 
 int IFLA_MAX ; 
#define  IFLA_TARGET_NETNSID 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  ifla_policy ; 
 int /*<<< orphan*/  netlink_strict_get_check (struct sk_buff*) ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int rtnl_valid_getlink_req(struct sk_buff *skb,
				  const struct nlmsghdr *nlh,
				  struct nlattr **tb,
				  struct netlink_ext_ack *extack)
{
	struct ifinfomsg *ifm;
	int i, err;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ifm))) {
		NL_SET_ERR_MSG(extack, "Invalid header for get link");
		return -EINVAL;
	}

	if (!netlink_strict_get_check(skb))
		return nlmsg_parse_deprecated(nlh, sizeof(*ifm), tb, IFLA_MAX,
					      ifla_policy, extack);

	ifm = nlmsg_data(nlh);
	if (ifm->__ifi_pad || ifm->ifi_type || ifm->ifi_flags ||
	    ifm->ifi_change) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for get link request");
		return -EINVAL;
	}

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(*ifm), tb, IFLA_MAX,
					    ifla_policy, extack);
	if (err)
		return err;

	for (i = 0; i <= IFLA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case IFLA_IFNAME:
		case IFLA_EXT_MASK:
		case IFLA_TARGET_NETNSID:
			break;
		default:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in get link request");
			return -EINVAL;
		}
	}

	return 0;
}