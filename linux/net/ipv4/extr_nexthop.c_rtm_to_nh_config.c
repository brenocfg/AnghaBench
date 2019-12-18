#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nhmsg {int nh_flags; int nh_family; int /*<<< orphan*/  nh_protocol; scalar_t__ nh_scope; scalar_t__ resvd; } ;
struct TYPE_7__ {int /*<<< orphan*/  ipv6; int /*<<< orphan*/  ipv4; } ;
struct TYPE_6__ {struct net* nl_net; struct nlmsghdr* nlh; int /*<<< orphan*/  portid; } ;
struct nh_config {int nh_family; int nh_flags; scalar_t__ nh_grp_type; int nh_blackhole; void* nh_encap_type; struct nlattr* nh_encap; TYPE_2__ gw; TYPE_3__* dev; void* nh_ifindex; struct nlattr* nh_grp; void* nh_id; int /*<<< orphan*/  nh_protocol; TYPE_1__ nlinfo; int /*<<< orphan*/  nlflags; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  portid; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int EINVAL ; 
 int ENETDOWN ; 
 int IFF_UP ; 
 TYPE_5__ NETLINK_CB (struct sk_buff*) ; 
 scalar_t__ NEXTHOP_GRP_TYPE_MAX ; 
 scalar_t__ NEXTHOP_GRP_TYPE_MPATH ; 
 int NEXTHOP_VALID_USER_FLAGS ; 
 size_t NHA_BLACKHOLE ; 
 size_t NHA_ENCAP ; 
 size_t NHA_ENCAP_TYPE ; 
 size_t NHA_GATEWAY ; 
 size_t NHA_GROUP ; 
 size_t NHA_GROUPS ; 
 size_t NHA_GROUP_TYPE ; 
 size_t NHA_ID ; 
 size_t NHA_MASTER ; 
 int /*<<< orphan*/  NHA_MAX ; 
 size_t NHA_OIF ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTNH_F_ONLINK ; 
 TYPE_3__* __dev_get_by_index (struct net*,void*) ; 
 int lwtunnel_valid_encap_type (void*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  memset (struct nh_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_ok (TYPE_3__*) ; 
 int nh_check_attr_group (struct net*,struct nlattr**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_in6_addr (struct nlattr*) ; 
 void* nla_get_u16 (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct nhmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  rtm_nh_policy ; 

__attribute__((used)) static int rtm_to_nh_config(struct net *net, struct sk_buff *skb,
			    struct nlmsghdr *nlh, struct nh_config *cfg,
			    struct netlink_ext_ack *extack)
{
	struct nhmsg *nhm = nlmsg_data(nlh);
	struct nlattr *tb[NHA_MAX + 1];
	int err;

	err = nlmsg_parse(nlh, sizeof(*nhm), tb, NHA_MAX, rtm_nh_policy,
			  extack);
	if (err < 0)
		return err;

	err = -EINVAL;
	if (nhm->resvd || nhm->nh_scope) {
		NL_SET_ERR_MSG(extack, "Invalid values in ancillary header");
		goto out;
	}
	if (nhm->nh_flags & ~NEXTHOP_VALID_USER_FLAGS) {
		NL_SET_ERR_MSG(extack, "Invalid nexthop flags in ancillary header");
		goto out;
	}

	switch (nhm->nh_family) {
	case AF_INET:
	case AF_INET6:
		break;
	case AF_UNSPEC:
		if (tb[NHA_GROUP])
			break;
		/* fallthrough */
	default:
		NL_SET_ERR_MSG(extack, "Invalid address family");
		goto out;
	}

	if (tb[NHA_GROUPS] || tb[NHA_MASTER]) {
		NL_SET_ERR_MSG(extack, "Invalid attributes in request");
		goto out;
	}

	memset(cfg, 0, sizeof(*cfg));
	cfg->nlflags = nlh->nlmsg_flags;
	cfg->nlinfo.portid = NETLINK_CB(skb).portid;
	cfg->nlinfo.nlh = nlh;
	cfg->nlinfo.nl_net = net;

	cfg->nh_family = nhm->nh_family;
	cfg->nh_protocol = nhm->nh_protocol;
	cfg->nh_flags = nhm->nh_flags;

	if (tb[NHA_ID])
		cfg->nh_id = nla_get_u32(tb[NHA_ID]);

	if (tb[NHA_GROUP]) {
		if (nhm->nh_family != AF_UNSPEC) {
			NL_SET_ERR_MSG(extack, "Invalid family for group");
			goto out;
		}
		cfg->nh_grp = tb[NHA_GROUP];

		cfg->nh_grp_type = NEXTHOP_GRP_TYPE_MPATH;
		if (tb[NHA_GROUP_TYPE])
			cfg->nh_grp_type = nla_get_u16(tb[NHA_GROUP_TYPE]);

		if (cfg->nh_grp_type > NEXTHOP_GRP_TYPE_MAX) {
			NL_SET_ERR_MSG(extack, "Invalid group type");
			goto out;
		}
		err = nh_check_attr_group(net, tb, extack);

		/* no other attributes should be set */
		goto out;
	}

	if (tb[NHA_BLACKHOLE]) {
		if (tb[NHA_GATEWAY] || tb[NHA_OIF] ||
		    tb[NHA_ENCAP]   || tb[NHA_ENCAP_TYPE]) {
			NL_SET_ERR_MSG(extack, "Blackhole attribute can not be used with gateway or oif");
			goto out;
		}

		cfg->nh_blackhole = 1;
		err = 0;
		goto out;
	}

	if (!tb[NHA_OIF]) {
		NL_SET_ERR_MSG(extack, "Device attribute required for non-blackhole nexthops");
		goto out;
	}

	cfg->nh_ifindex = nla_get_u32(tb[NHA_OIF]);
	if (cfg->nh_ifindex)
		cfg->dev = __dev_get_by_index(net, cfg->nh_ifindex);

	if (!cfg->dev) {
		NL_SET_ERR_MSG(extack, "Invalid device index");
		goto out;
	} else if (!(cfg->dev->flags & IFF_UP)) {
		NL_SET_ERR_MSG(extack, "Nexthop device is not up");
		err = -ENETDOWN;
		goto out;
	} else if (!netif_carrier_ok(cfg->dev)) {
		NL_SET_ERR_MSG(extack, "Carrier for nexthop device is down");
		err = -ENETDOWN;
		goto out;
	}

	err = -EINVAL;
	if (tb[NHA_GATEWAY]) {
		struct nlattr *gwa = tb[NHA_GATEWAY];

		switch (cfg->nh_family) {
		case AF_INET:
			if (nla_len(gwa) != sizeof(u32)) {
				NL_SET_ERR_MSG(extack, "Invalid gateway");
				goto out;
			}
			cfg->gw.ipv4 = nla_get_be32(gwa);
			break;
		case AF_INET6:
			if (nla_len(gwa) != sizeof(struct in6_addr)) {
				NL_SET_ERR_MSG(extack, "Invalid gateway");
				goto out;
			}
			cfg->gw.ipv6 = nla_get_in6_addr(gwa);
			break;
		default:
			NL_SET_ERR_MSG(extack,
				       "Unknown address family for gateway");
			goto out;
		}
	} else {
		/* device only nexthop (no gateway) */
		if (cfg->nh_flags & RTNH_F_ONLINK) {
			NL_SET_ERR_MSG(extack,
				       "ONLINK flag can not be set for nexthop without a gateway");
			goto out;
		}
	}

	if (tb[NHA_ENCAP]) {
		cfg->nh_encap = tb[NHA_ENCAP];

		if (!tb[NHA_ENCAP_TYPE]) {
			NL_SET_ERR_MSG(extack, "LWT encapsulation type is missing");
			goto out;
		}

		cfg->nh_encap_type = nla_get_u16(tb[NHA_ENCAP_TYPE]);
		err = lwtunnel_valid_encap_type(cfg->nh_encap_type, extack);
		if (err < 0)
			goto out;

	} else if (tb[NHA_ENCAP_TYPE]) {
		NL_SET_ERR_MSG(extack, "LWT encapsulation attribute is missing");
		goto out;
	}


	err = 0;
out:
	return err;
}