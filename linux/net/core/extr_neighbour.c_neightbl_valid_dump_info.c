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
struct ndtmsg {scalar_t__ ndtm_pad2; scalar_t__ ndtm_pad1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ nlmsg_attrlen (struct nlmsghdr const*,int) ; 
 struct ndtmsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 

__attribute__((used)) static int neightbl_valid_dump_info(const struct nlmsghdr *nlh,
				    struct netlink_ext_ack *extack)
{
	struct ndtmsg *ndtm;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*ndtm))) {
		NL_SET_ERR_MSG(extack, "Invalid header for neighbor table dump request");
		return -EINVAL;
	}

	ndtm = nlmsg_data(nlh);
	if (ndtm->ndtm_pad1  || ndtm->ndtm_pad2) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for neighbor table dump request");
		return -EINVAL;
	}

	if (nlmsg_attrlen(nlh, sizeof(*ndtm))) {
		NL_SET_ERR_MSG(extack, "Invalid data after header in neighbor table dump request");
		return -EINVAL;
	}

	return 0;
}