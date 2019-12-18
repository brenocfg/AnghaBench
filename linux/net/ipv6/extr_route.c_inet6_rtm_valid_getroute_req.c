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
struct rtmsg {int rtm_src_len; int rtm_dst_len; int rtm_flags; scalar_t__ rtm_type; scalar_t__ rtm_scope; scalar_t__ rtm_protocol; scalar_t__ rtm_table; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
#define  RTA_DPORT 136 
#define  RTA_DST 135 
#define  RTA_IIF 134 
#define  RTA_IP_PROTO 133 
#define  RTA_MARK 132 
 int RTA_MAX ; 
#define  RTA_OIF 131 
#define  RTA_SPORT 130 
#define  RTA_SRC 129 
#define  RTA_UID 128 
 int RTM_F_FIB_MATCH ; 
 int /*<<< orphan*/  netlink_strict_get_check (struct sk_buff*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr const*) ; 
 scalar_t__ nlmsg_msg_size (int) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int nlmsg_parse_deprecated_strict (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_ipv6_policy ; 

__attribute__((used)) static int inet6_rtm_valid_getroute_req(struct sk_buff *skb,
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
					      rtm_ipv6_policy, extack);

	rtm = nlmsg_data(nlh);
	if ((rtm->rtm_src_len && rtm->rtm_src_len != 128) ||
	    (rtm->rtm_dst_len && rtm->rtm_dst_len != 128) ||
	    rtm->rtm_table || rtm->rtm_protocol || rtm->rtm_scope ||
	    rtm->rtm_type) {
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for get route request");
		return -EINVAL;
	}
	if (rtm->rtm_flags & ~RTM_F_FIB_MATCH) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Invalid flags for get route request");
		return -EINVAL;
	}

	err = nlmsg_parse_deprecated_strict(nlh, sizeof(*rtm), tb, RTA_MAX,
					    rtm_ipv6_policy, extack);
	if (err)
		return err;

	if ((tb[RTA_SRC] && !rtm->rtm_src_len) ||
	    (tb[RTA_DST] && !rtm->rtm_dst_len)) {
		NL_SET_ERR_MSG_MOD(extack, "rtm_src_len and rtm_dst_len must be 128 for IPv6");
		return -EINVAL;
	}

	for (i = 0; i <= RTA_MAX; i++) {
		if (!tb[i])
			continue;

		switch (i) {
		case RTA_SRC:
		case RTA_DST:
		case RTA_IIF:
		case RTA_OIF:
		case RTA_MARK:
		case RTA_UID:
		case RTA_SPORT:
		case RTA_DPORT:
		case RTA_IP_PROTO:
			break;
		default:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in get route request");
			return -EINVAL;
		}
	}

	return 0;
}