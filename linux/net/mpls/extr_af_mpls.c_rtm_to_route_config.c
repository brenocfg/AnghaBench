#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct rtmsg {scalar_t__ rtm_family; int rtm_dst_len; scalar_t__ rtm_src_len; scalar_t__ rtm_tos; scalar_t__ rtm_table; scalar_t__ rtm_scope; scalar_t__ rtm_type; scalar_t__ rtm_flags; int /*<<< orphan*/  rtm_protocol; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nl_net; struct nlmsghdr* nlh; int /*<<< orphan*/  portid; } ;
struct mpls_route_config {int rc_output_labels; int /*<<< orphan*/  rc_ttl_propagate; int /*<<< orphan*/  rc_mp_len; int /*<<< orphan*/  rc_mp; int /*<<< orphan*/  rc_via; int /*<<< orphan*/  rc_via_table; int /*<<< orphan*/  rc_via_alen; int /*<<< orphan*/  rc_label; TYPE_1__ rc_nlinfo; int /*<<< orphan*/ * rc_output_label; int /*<<< orphan*/  rc_ifindex; int /*<<< orphan*/  rc_nlflags; int /*<<< orphan*/  rc_protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 scalar_t__ AF_MPLS ; 
 int EINVAL ; 
 int /*<<< orphan*/  LABEL_NOT_SPECIFIED ; 
 int MAX_NEW_LABELS ; 
 int /*<<< orphan*/  MPLS_NEIGH_TABLE_UNSPEC ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_DEFAULT ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_DISABLED ; 
 int /*<<< orphan*/  MPLS_TTL_PROP_ENABLED ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (struct netlink_ext_ack*,struct nlattr*,char*) ; 
#define  RTA_DST 134 
#define  RTA_GATEWAY 133 
 int RTA_MAX ; 
#define  RTA_MULTIPATH 132 
#define  RTA_NEWDST 131 
#define  RTA_OIF 130 
#define  RTA_TTL_PROPAGATE 129 
#define  RTA_VIA 128 
 scalar_t__ RTN_UNICAST ; 
 scalar_t__ RT_SCOPE_UNIVERSE ; 
 scalar_t__ RT_TABLE_MAIN ; 
 int /*<<< orphan*/  mpls_label_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_labels (struct nlattr*,int,int*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_via (struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_mpls_policy ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtm_to_route_config(struct sk_buff *skb,
			       struct nlmsghdr *nlh,
			       struct mpls_route_config *cfg,
			       struct netlink_ext_ack *extack)
{
	struct rtmsg *rtm;
	struct nlattr *tb[RTA_MAX+1];
	int index;
	int err;

	err = nlmsg_parse_deprecated(nlh, sizeof(*rtm), tb, RTA_MAX,
				     rtm_mpls_policy, extack);
	if (err < 0)
		goto errout;

	err = -EINVAL;
	rtm = nlmsg_data(nlh);

	if (rtm->rtm_family != AF_MPLS) {
		NL_SET_ERR_MSG(extack, "Invalid address family in rtmsg");
		goto errout;
	}
	if (rtm->rtm_dst_len != 20) {
		NL_SET_ERR_MSG(extack, "rtm_dst_len must be 20 for MPLS");
		goto errout;
	}
	if (rtm->rtm_src_len != 0) {
		NL_SET_ERR_MSG(extack, "rtm_src_len must be 0 for MPLS");
		goto errout;
	}
	if (rtm->rtm_tos != 0) {
		NL_SET_ERR_MSG(extack, "rtm_tos must be 0 for MPLS");
		goto errout;
	}
	if (rtm->rtm_table != RT_TABLE_MAIN) {
		NL_SET_ERR_MSG(extack,
			       "MPLS only supports the main route table");
		goto errout;
	}
	/* Any value is acceptable for rtm_protocol */

	/* As mpls uses destination specific addresses
	 * (or source specific address in the case of multicast)
	 * all addresses have universal scope.
	 */
	if (rtm->rtm_scope != RT_SCOPE_UNIVERSE) {
		NL_SET_ERR_MSG(extack,
			       "Invalid route scope  - MPLS only supports UNIVERSE");
		goto errout;
	}
	if (rtm->rtm_type != RTN_UNICAST) {
		NL_SET_ERR_MSG(extack,
			       "Invalid route type - MPLS only supports UNICAST");
		goto errout;
	}
	if (rtm->rtm_flags != 0) {
		NL_SET_ERR_MSG(extack, "rtm_flags must be 0 for MPLS");
		goto errout;
	}

	cfg->rc_label		= LABEL_NOT_SPECIFIED;
	cfg->rc_protocol	= rtm->rtm_protocol;
	cfg->rc_via_table	= MPLS_NEIGH_TABLE_UNSPEC;
	cfg->rc_ttl_propagate	= MPLS_TTL_PROP_DEFAULT;
	cfg->rc_nlflags		= nlh->nlmsg_flags;
	cfg->rc_nlinfo.portid	= NETLINK_CB(skb).portid;
	cfg->rc_nlinfo.nlh	= nlh;
	cfg->rc_nlinfo.nl_net	= sock_net(skb->sk);

	for (index = 0; index <= RTA_MAX; index++) {
		struct nlattr *nla = tb[index];
		if (!nla)
			continue;

		switch (index) {
		case RTA_OIF:
			cfg->rc_ifindex = nla_get_u32(nla);
			break;
		case RTA_NEWDST:
			if (nla_get_labels(nla, MAX_NEW_LABELS,
					   &cfg->rc_output_labels,
					   cfg->rc_output_label, extack))
				goto errout;
			break;
		case RTA_DST:
		{
			u8 label_count;
			if (nla_get_labels(nla, 1, &label_count,
					   &cfg->rc_label, extack))
				goto errout;

			if (!mpls_label_ok(cfg->rc_nlinfo.nl_net,
					   &cfg->rc_label, extack))
				goto errout;
			break;
		}
		case RTA_GATEWAY:
			NL_SET_ERR_MSG(extack, "MPLS does not support RTA_GATEWAY attribute");
			goto errout;
		case RTA_VIA:
		{
			if (nla_get_via(nla, &cfg->rc_via_alen,
					&cfg->rc_via_table, cfg->rc_via,
					extack))
				goto errout;
			break;
		}
		case RTA_MULTIPATH:
		{
			cfg->rc_mp = nla_data(nla);
			cfg->rc_mp_len = nla_len(nla);
			break;
		}
		case RTA_TTL_PROPAGATE:
		{
			u8 ttl_propagate = nla_get_u8(nla);

			if (ttl_propagate > 1) {
				NL_SET_ERR_MSG_ATTR(extack, nla,
						    "RTA_TTL_PROPAGATE can only be 0 or 1");
				goto errout;
			}
			cfg->rc_ttl_propagate = ttl_propagate ?
				MPLS_TTL_PROP_ENABLED :
				MPLS_TTL_PROP_DISABLED;
			break;
		}
		default:
			NL_SET_ERR_MSG_ATTR(extack, nla, "Unknown attribute");
			/* Unsupported attribute */
			goto errout;
		}
	}

	err = 0;
errout:
	return err;
}