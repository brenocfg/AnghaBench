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
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct in_ifaddr {int ifa_prefixlen; void* ifa_rt_priority; int /*<<< orphan*/  ifa_label; void* ifa_broadcast; void* ifa_address; void* ifa_local; struct in_device* ifa_dev; int /*<<< orphan*/  ifa_scope; void* ifa_flags; int /*<<< orphan*/  ifa_mask; int /*<<< orphan*/  hash; } ;
struct in_device {int /*<<< orphan*/  arp_parms; } ;
struct ifaddrmsg {int ifa_prefixlen; void* ifa_flags; int /*<<< orphan*/  ifa_scope; int /*<<< orphan*/  ifa_index; } ;
struct ifa_cacheinfo {scalar_t__ ifa_valid; scalar_t__ ifa_prefered; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 struct in_ifaddr* ERR_PTR (int) ; 
 size_t IFA_ADDRESS ; 
 size_t IFA_BROADCAST ; 
 size_t IFA_CACHEINFO ; 
 size_t IFA_FLAGS ; 
 size_t IFA_LABEL ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 size_t IFA_RT_PRIORITY ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  ifa_ipv4_policy ; 
 int /*<<< orphan*/  in_dev_hold (struct in_device*) ; 
 struct in_ifaddr* inet_alloc_ifa () ; 
 int /*<<< orphan*/  inet_free_ifa (struct in_ifaddr*) ; 
 int /*<<< orphan*/  inet_make_mask (int) ; 
 int /*<<< orphan*/  ipv4_devconf_setall (struct in_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_parms_data_state_setall (int /*<<< orphan*/ ) ; 
 struct ifa_cacheinfo* nla_data (struct nlattr*) ; 
 void* nla_get_in_addr (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_strlcpy (int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static struct in_ifaddr *rtm_to_ifaddr(struct net *net, struct nlmsghdr *nlh,
				       __u32 *pvalid_lft, __u32 *pprefered_lft,
				       struct netlink_ext_ack *extack)
{
	struct nlattr *tb[IFA_MAX+1];
	struct in_ifaddr *ifa;
	struct ifaddrmsg *ifm;
	struct net_device *dev;
	struct in_device *in_dev;
	int err;

	err = nlmsg_parse_deprecated(nlh, sizeof(*ifm), tb, IFA_MAX,
				     ifa_ipv4_policy, extack);
	if (err < 0)
		goto errout;

	ifm = nlmsg_data(nlh);
	err = -EINVAL;
	if (ifm->ifa_prefixlen > 32 || !tb[IFA_LOCAL])
		goto errout;

	dev = __dev_get_by_index(net, ifm->ifa_index);
	err = -ENODEV;
	if (!dev)
		goto errout;

	in_dev = __in_dev_get_rtnl(dev);
	err = -ENOBUFS;
	if (!in_dev)
		goto errout;

	ifa = inet_alloc_ifa();
	if (!ifa)
		/*
		 * A potential indev allocation can be left alive, it stays
		 * assigned to its device and is destroy with it.
		 */
		goto errout;

	ipv4_devconf_setall(in_dev);
	neigh_parms_data_state_setall(in_dev->arp_parms);
	in_dev_hold(in_dev);

	if (!tb[IFA_ADDRESS])
		tb[IFA_ADDRESS] = tb[IFA_LOCAL];

	INIT_HLIST_NODE(&ifa->hash);
	ifa->ifa_prefixlen = ifm->ifa_prefixlen;
	ifa->ifa_mask = inet_make_mask(ifm->ifa_prefixlen);
	ifa->ifa_flags = tb[IFA_FLAGS] ? nla_get_u32(tb[IFA_FLAGS]) :
					 ifm->ifa_flags;
	ifa->ifa_scope = ifm->ifa_scope;
	ifa->ifa_dev = in_dev;

	ifa->ifa_local = nla_get_in_addr(tb[IFA_LOCAL]);
	ifa->ifa_address = nla_get_in_addr(tb[IFA_ADDRESS]);

	if (tb[IFA_BROADCAST])
		ifa->ifa_broadcast = nla_get_in_addr(tb[IFA_BROADCAST]);

	if (tb[IFA_LABEL])
		nla_strlcpy(ifa->ifa_label, tb[IFA_LABEL], IFNAMSIZ);
	else
		memcpy(ifa->ifa_label, dev->name, IFNAMSIZ);

	if (tb[IFA_RT_PRIORITY])
		ifa->ifa_rt_priority = nla_get_u32(tb[IFA_RT_PRIORITY]);

	if (tb[IFA_CACHEINFO]) {
		struct ifa_cacheinfo *ci;

		ci = nla_data(tb[IFA_CACHEINFO]);
		if (!ci->ifa_valid || ci->ifa_prefered > ci->ifa_valid) {
			err = -EINVAL;
			goto errout_free;
		}
		*pvalid_lft = ci->ifa_valid;
		*pprefered_lft = ci->ifa_prefered;
	}

	return ifa;

errout_free:
	inet_free_ifa(ifa);
errout:
	return ERR_PTR(err);
}