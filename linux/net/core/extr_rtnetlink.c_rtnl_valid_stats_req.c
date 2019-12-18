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
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct netlink_ext_ack {int dummy; } ;
struct if_stats_msg {scalar_t__ filter_mask; scalar_t__ ifindex; scalar_t__ pad2; scalar_t__ pad1; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IFLA_STATS_FILTER_BIT (scalar_t__) ; 
 scalar_t__ IFLA_STATS_MAX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ nlmsg_attrlen (struct nlmsghdr const*,int) ; 
 struct if_stats_msg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 

__attribute__((used)) static int rtnl_valid_stats_req(const struct nlmsghdr *nlh, bool strict_check,
				bool is_dump, struct netlink_ext_ack *extack)
{
	struct if_stats_msg *ifsm;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ifsm))) {
		NL_SET_ERR_MSG(extack, "Invalid header for stats dump");
		return -EINVAL;
	}

	if (!strict_check)
		return 0;

	ifsm = nlmsg_data(nlh);

	/* only requests using strict checks can pass data to influence
	 * the dump. The legacy exception is filter_mask.
	 */
	if (ifsm->pad1 || ifsm->pad2 || (is_dump && ifsm->ifindex)) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for stats dump request");
		return -EINVAL;
	}
	if (nlmsg_attrlen(nlh, sizeof(*ifsm))) {
		NL_SET_ERR_MSG(extack, "Invalid attributes after stats header");
		return -EINVAL;
	}
	if (ifsm->filter_mask >= IFLA_STATS_FILTER_BIT(IFLA_STATS_MAX + 1)) {
		NL_SET_ERR_MSG(extack, "Invalid stats requested through filter mask");
		return -EINVAL;
	}

	return 0;
}