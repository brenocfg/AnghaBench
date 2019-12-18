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
struct rtgenmsg {int dummy; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct ifinfomsg {scalar_t__ ifi_index; scalar_t__ ifi_change; scalar_t__ ifi_flags; scalar_t__ ifi_type; scalar_t__ __ifi_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  ifla_policy ; 
 struct ifinfomsg* nlmsg_data (struct nlmsghdr const*) ; 
 int nlmsg_len (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr const*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static int rtnl_valid_dump_ifinfo_req(const struct nlmsghdr *nlh,
				      bool strict_check, struct nlattr **tb,
				      struct netlink_ext_ack *extack)
{
	int hdrlen;

	if (strict_check) {
		struct ifinfomsg *ifm;

		if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ifm))) {
			NL_SET_ERR_MSG(extack, "Invalid header for link dump");
			return -EINVAL;
		}

		ifm = nlmsg_data(nlh);
		if (ifm->__ifi_pad || ifm->ifi_type || ifm->ifi_flags ||
		    ifm->ifi_change) {
			NL_SET_ERR_MSG(extack, "Invalid values in header for link dump request");
			return -EINVAL;
		}
		if (ifm->ifi_index) {
			NL_SET_ERR_MSG(extack, "Filter by device index not supported for link dumps");
			return -EINVAL;
		}

		return nlmsg_parse_deprecated_strict(nlh, sizeof(*ifm), tb,
						     IFLA_MAX, ifla_policy,
						     extack);
	}

	/* A hack to preserve kernel<->userspace interface.
	 * The correct header is ifinfomsg. It is consistent with rtnl_getlink.
	 * However, before Linux v3.9 the code here assumed rtgenmsg and that's
	 * what iproute2 < v3.9.0 used.
	 * We can detect the old iproute2. Even including the IFLA_EXT_MASK
	 * attribute, its netlink message is shorter than struct ifinfomsg.
	 */
	hdrlen = nlmsg_len(nlh) < sizeof(struct ifinfomsg) ?
		 sizeof(struct rtgenmsg) : sizeof(struct ifinfomsg);

	return nlmsg_parse_deprecated(nlh, hdrlen, tb, IFLA_MAX, ifla_policy,
				      extack);
}