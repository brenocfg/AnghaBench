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
struct rtmsg {int rtm_dst_len; int rtm_flags; scalar_t__ rtm_type; scalar_t__ rtm_scope; scalar_t__ rtm_protocol; scalar_t__ rtm_table; scalar_t__ rtm_tos; scalar_t__ rtm_src_len; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
#define  RTA_DST 129 
 int RTA_MAX ; 
#define  RTA_NEWDST 128 
 int RTM_F_FIB_MATCH ; 
 int /*<<< orphan*/  netlink_strict_get_check (struct sk_buff*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_mpls_policy ; 

__attribute__((used)) static int mpls_valid_getroute_req(struct sk_buff *skb,
				   const struct nlmsghdr *nlh,
				   struct nlattr **tb,
				   struct netlink_ext_ack *extack)
{
	struct rtmsg *rtm;
	int i, err;

	if (nlh->nlmsg_len < nlmsg_msg_size(sizeof(*rtm))) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid header for get route request");
		return -EINVAL;
	}

	if (!netlink_strict_get_check(skb))
		return nlmsg_parse_deprecated(nlh, sizeof(*rtm), tb, RTA_MAX,
					      rtm_mpls_policy, extack);

	rtm = nlmsg_data(nlh);
	if ((rtm->rtm_dst_len && rtm->rtm_dst_len != 20) ||
	    rtm->rtm_src_len || rtm->rtm_tos || rtm->rtm_table ||
	    rtm->rtm_protocol || rtm->rtm_scope || rtm->rtm_type) {
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for get route request");
		return -EINVAL;
	}
	if (rtm->rtm_flags & ~RTM_F_FIB_MATCH) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid flags for get route request");
		return -EINVAL;
	}

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(*rtm), tb, RTA_MAX,
					    rtm_mpls_policy, extack);
	if (err)
		return err;

	if ((tb[RTA_DST] || tb[RTA_NEWDST]) && !rtm->rtm_dst_len) {
		NL_SET_ERR_MSG_MOD(extack, "rtm_dst_len must be 20 for MPLS");
		return -EINVAL;
	}

	for (i = 0; i <= RTA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case RTA_DST:
		case RTA_NEWDST:
			break;
		default:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in get route request");
			return -EINVAL;
		}
	}

	return 0;
}