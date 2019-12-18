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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_ifaddr {int dummy; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrmsg {int ifa_flags; int /*<<< orphan*/  ifa_index; int /*<<< orphan*/  ifa_prefixlen; } ;
struct ifa_cacheinfo {void* ifa_prefered; void* ifa_valid; } ;
struct ifa6_config {int ifa_flags; int /*<<< orphan*/  pfx; void* preferred_lft; void* valid_lft; void* rt_priority; int /*<<< orphan*/  plen; struct in6_addr* peer_pfx; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENODEV ; 
 size_t IFA_ADDRESS ; 
 size_t IFA_CACHEINFO ; 
 size_t IFA_FLAGS ; 
 int IFA_F_HOMEADDRESS ; 
 int IFA_F_MANAGETEMPADDR ; 
 int IFA_F_MCAUTOJOIN ; 
 int IFA_F_NODAD ; 
 int IFA_F_NOPREFIXROUTE ; 
 int IFA_F_OPTIMISTIC ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 size_t IFA_RT_PRIORITY ; 
 void* INFINITY_LIFE_TIME ; 
 scalar_t__ IS_ERR (struct inet6_dev*) ; 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (struct inet6_dev*) ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_addr (struct nlattr*,struct nlattr*,struct in6_addr**) ; 
 int /*<<< orphan*/  ifa_ipv6_policy ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 int inet6_addr_add (struct net*,int /*<<< orphan*/ ,struct ifa6_config*,struct netlink_ext_ack*) ; 
 int inet6_addr_modify (struct inet6_ifaddr*,struct ifa6_config*) ; 
 int /*<<< orphan*/  ipv6_allow_optimistic_dad (struct net*,struct inet6_dev*) ; 
 struct inet6_dev* ipv6_find_idev (struct net_device*) ; 
 struct inet6_ifaddr* ipv6_get_ifaddr (struct net*,int /*<<< orphan*/ ,struct net_device*,int) ; 
 int /*<<< orphan*/  memset (struct ifa6_config*,int /*<<< orphan*/ ,int) ; 
 struct ifa_cacheinfo* nla_data (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inet6_rtm_newaddr(struct sk_buff *skb, struct nlmsghdr *nlh,
		  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct ifaddrmsg *ifm;
	struct nlattr *tb[IFA_MAX+1];
	struct in6_addr *peer_pfx;
	struct inet6_ifaddr *ifa;
	struct net_device *dev;
	struct inet6_dev *idev;
	struct ifa6_config cfg;
	int err;

	err = nlmsg_parse_deprecated(nlh, sizeof(*ifm), tb, IFA_MAX,
				     ifa_ipv6_policy, extack);
	if (err < 0)
		return err;

	memset(&cfg, 0, sizeof(cfg));

	ifm = nlmsg_data(nlh);
	cfg.pfx = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer_pfx);
	if (!cfg.pfx)
		return -EINVAL;

	cfg.peer_pfx = peer_pfx;
	cfg.plen = ifm->ifa_prefixlen;
	if (tb[IFA_RT_PRIORITY])
		cfg.rt_priority = nla_get_u32(tb[IFA_RT_PRIORITY]);

	cfg.valid_lft = INFINITY_LIFE_TIME;
	cfg.preferred_lft = INFINITY_LIFE_TIME;

	if (tb[IFA_CACHEINFO]) {
		struct ifa_cacheinfo *ci;

		ci = nla_data(tb[IFA_CACHEINFO]);
		cfg.valid_lft = ci->ifa_valid;
		cfg.preferred_lft = ci->ifa_prefered;
	}

	dev =  __dev_get_by_index(net, ifm->ifa_index);
	if (!dev)
		return -ENODEV;

	if (tb[IFA_FLAGS])
		cfg.ifa_flags = nla_get_u32(tb[IFA_FLAGS]);
	else
		cfg.ifa_flags = ifm->ifa_flags;

	/* We ignore other flags so far. */
	cfg.ifa_flags &= IFA_F_NODAD | IFA_F_HOMEADDRESS |
			 IFA_F_MANAGETEMPADDR | IFA_F_NOPREFIXROUTE |
			 IFA_F_MCAUTOJOIN | IFA_F_OPTIMISTIC;

	idev = ipv6_find_idev(dev);
	if (IS_ERR(idev))
		return PTR_ERR(idev);

	if (!ipv6_allow_optimistic_dad(net, idev))
		cfg.ifa_flags &= ~IFA_F_OPTIMISTIC;

	if (cfg.ifa_flags & IFA_F_NODAD &&
	    cfg.ifa_flags & IFA_F_OPTIMISTIC) {
		NL_SET_ERR_MSG(extack, "IFA_F_NODAD and IFA_F_OPTIMISTIC are mutually exclusive");
		return -EINVAL;
	}

	ifa = ipv6_get_ifaddr(net, cfg.pfx, dev, 1);
	if (!ifa) {
		/*
		 * It would be best to check for !NLM_F_CREATE here but
		 * userspace already relies on not having to provide this.
		 */
		return inet6_addr_add(net, ifm->ifa_index, &cfg, extack);
	}

	if (nlh->nlmsg_flags & NLM_F_EXCL ||
	    !(nlh->nlmsg_flags & NLM_F_REPLACE))
		err = -EEXIST;
	else
		err = inet6_addr_modify(ifa, &cfg);

	in6_ifa_put(ifa);

	return err;
}