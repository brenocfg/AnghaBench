#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct netlink_ext_ack {int dummy; } ;
struct net_device {int flags; } ;
struct net {struct net_device* loopback_dev; } ;
struct lwtunnel_state {int dummy; } ;
struct TYPE_7__ {scalar_t__ disable_ipv6; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct fib6_table {int dummy; } ;
struct TYPE_12__ {int nh_weight; int nh_flags; struct net_device* nh_dev; int /*<<< orphan*/  nh_gw; int /*<<< orphan*/  nh_lwtstate; } ;
struct TYPE_8__ {int plen; int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {int plen; int /*<<< orphan*/  addr; } ;
struct fib6_info {int dst_nocount; scalar_t__ fib6_protocol; int dst_host; scalar_t__ fib6_metric; scalar_t__ fib6_type; int fib6_flags; struct fib6_table* fib6_table; TYPE_6__ fib6_nh; TYPE_2__ fib6_prefsrc; TYPE_5__ fib6_dst; } ;
struct TYPE_10__ {struct net* nl_net; TYPE_3__* nlh; } ;
struct fib6_config {int fc_flags; scalar_t__ fc_type; int fc_dst_len; int fc_src_len; scalar_t__ fc_metric; scalar_t__ fc_protocol; TYPE_4__ fc_nlinfo; int /*<<< orphan*/  fc_prefsrc; int /*<<< orphan*/  fc_gateway; int /*<<< orphan*/  fc_dst; scalar_t__ fc_encap; int /*<<< orphan*/  fc_encap_type; int /*<<< orphan*/  fc_expires; int /*<<< orphan*/  fc_table; int /*<<< orphan*/  fc_ifindex; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_9__ {int nlmsg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int EACCES ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct fib6_info* ERR_PTR (int) ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 scalar_t__ IP6_RT_PRIO_USER ; 
 int IPV6_ADDR_LOOPBACK ; 
 int NLM_F_CREATE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTF_ADDRCONF ; 
 int RTF_ANYCAST ; 
 int RTF_CACHE ; 
 int RTF_EXPIRES ; 
 int RTF_GATEWAY ; 
 int RTF_LOCAL ; 
 int RTF_NONEXTHOP ; 
 int RTF_PCPU ; 
 int RTF_REJECT ; 
 int RTNH_F_LINKDOWN ; 
 int RTNH_F_ONLINK ; 
 scalar_t__ RTN_MAX ; 
 scalar_t__ RTPROT_BOOT ; 
 scalar_t__ RTPROT_UNSPEC ; 
 scalar_t__ clock_t_to_jiffies (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  fib6_clean_expires (struct fib6_info*) ; 
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 struct fib6_info* fib6_info_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_info_release (struct fib6_info*) ; 
 struct fib6_table* fib6_new_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_set_expires (struct fib6_info*,scalar_t__) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int ip6_convert_metrics (struct net*,struct fib6_info*,struct fib6_config*) ; 
 int ip6_validate_gw (struct net*,struct fib6_config*,struct net_device**,struct inet6_dev**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_chk_addr (struct net*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lwtstate_get (struct lwtunnel_state*) ; 
 int lwtunnel_build_state (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct fib6_config*,struct lwtunnel_state**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static struct fib6_info *ip6_route_info_create(struct fib6_config *cfg,
					      gfp_t gfp_flags,
					      struct netlink_ext_ack *extack)
{
	struct net *net = cfg->fc_nlinfo.nl_net;
	struct fib6_info *rt = NULL;
	struct net_device *dev = NULL;
	struct inet6_dev *idev = NULL;
	struct fib6_table *table;
	int addr_type;
	int err = -EINVAL;

	/* RTF_PCPU is an internal flag; can not be set by userspace */
	if (cfg->fc_flags & RTF_PCPU) {
		NL_SET_ERR_MSG(extack, "Userspace can not set RTF_PCPU");
		goto out;
	}

	/* RTF_CACHE is an internal flag; can not be set by userspace */
	if (cfg->fc_flags & RTF_CACHE) {
		NL_SET_ERR_MSG(extack, "Userspace can not set RTF_CACHE");
		goto out;
	}

	if (cfg->fc_type > RTN_MAX) {
		NL_SET_ERR_MSG(extack, "Invalid route type");
		goto out;
	}

	if (cfg->fc_dst_len > 128) {
		NL_SET_ERR_MSG(extack, "Invalid prefix length");
		goto out;
	}
	if (cfg->fc_src_len > 128) {
		NL_SET_ERR_MSG(extack, "Invalid source address length");
		goto out;
	}
#ifndef CONFIG_IPV6_SUBTREES
	if (cfg->fc_src_len) {
		NL_SET_ERR_MSG(extack,
			       "Specifying source address requires IPV6_SUBTREES to be enabled");
		goto out;
	}
#endif
	if (cfg->fc_ifindex) {
		err = -ENODEV;
		dev = dev_get_by_index(net, cfg->fc_ifindex);
		if (!dev)
			goto out;
		idev = in6_dev_get(dev);
		if (!idev)
			goto out;
	}

	if (cfg->fc_metric == 0)
		cfg->fc_metric = IP6_RT_PRIO_USER;

	if (cfg->fc_flags & RTNH_F_ONLINK) {
		if (!dev) {
			NL_SET_ERR_MSG(extack,
				       "Nexthop device required for onlink");
			err = -ENODEV;
			goto out;
		}

		if (!(dev->flags & IFF_UP)) {
			NL_SET_ERR_MSG(extack, "Nexthop device is not up");
			err = -ENETDOWN;
			goto out;
		}
	}

	err = -ENOBUFS;
	if (cfg->fc_nlinfo.nlh &&
	    !(cfg->fc_nlinfo.nlh->nlmsg_flags & NLM_F_CREATE)) {
		table = fib6_get_table(net, cfg->fc_table);
		if (!table) {
			pr_warn("NLM_F_CREATE should be specified when creating new route\n");
			table = fib6_new_table(net, cfg->fc_table);
		}
	} else {
		table = fib6_new_table(net, cfg->fc_table);
	}

	if (!table)
		goto out;

	err = -ENOMEM;
	rt = fib6_info_alloc(gfp_flags);
	if (!rt)
		goto out;

	if (cfg->fc_flags & RTF_ADDRCONF)
		rt->dst_nocount = true;

	err = ip6_convert_metrics(net, rt, cfg);
	if (err < 0)
		goto out;

	if (cfg->fc_flags & RTF_EXPIRES)
		fib6_set_expires(rt, jiffies +
				clock_t_to_jiffies(cfg->fc_expires));
	else
		fib6_clean_expires(rt);

	if (cfg->fc_protocol == RTPROT_UNSPEC)
		cfg->fc_protocol = RTPROT_BOOT;
	rt->fib6_protocol = cfg->fc_protocol;

	addr_type = ipv6_addr_type(&cfg->fc_dst);

	if (cfg->fc_encap) {
		struct lwtunnel_state *lwtstate;

		err = lwtunnel_build_state(cfg->fc_encap_type,
					   cfg->fc_encap, AF_INET6, cfg,
					   &lwtstate, extack);
		if (err)
			goto out;
		rt->fib6_nh.nh_lwtstate = lwtstate_get(lwtstate);
	}

	ipv6_addr_prefix(&rt->fib6_dst.addr, &cfg->fc_dst, cfg->fc_dst_len);
	rt->fib6_dst.plen = cfg->fc_dst_len;
	if (rt->fib6_dst.plen == 128)
		rt->dst_host = true;

#ifdef CONFIG_IPV6_SUBTREES
	ipv6_addr_prefix(&rt->fib6_src.addr, &cfg->fc_src, cfg->fc_src_len);
	rt->fib6_src.plen = cfg->fc_src_len;
#endif

	rt->fib6_metric = cfg->fc_metric;
	rt->fib6_nh.nh_weight = 1;

	rt->fib6_type = cfg->fc_type;

	/* We cannot add true routes via loopback here,
	   they would result in kernel looping; promote them to reject routes
	 */
	if ((cfg->fc_flags & RTF_REJECT) ||
	    (dev && (dev->flags & IFF_LOOPBACK) &&
	     !(addr_type & IPV6_ADDR_LOOPBACK) &&
	     !(cfg->fc_flags & RTF_LOCAL))) {
		/* hold loopback dev/idev if we haven't done so. */
		if (dev != net->loopback_dev) {
			if (dev) {
				dev_put(dev);
				in6_dev_put(idev);
			}
			dev = net->loopback_dev;
			dev_hold(dev);
			idev = in6_dev_get(dev);
			if (!idev) {
				err = -ENODEV;
				goto out;
			}
		}
		rt->fib6_flags = RTF_REJECT|RTF_NONEXTHOP;
		goto install_route;
	}

	if (cfg->fc_flags & RTF_GATEWAY) {
		err = ip6_validate_gw(net, cfg, &dev, &idev, extack);
		if (err)
			goto out;

		rt->fib6_nh.nh_gw = cfg->fc_gateway;
	}

	err = -ENODEV;
	if (!dev)
		goto out;

	if (idev->cnf.disable_ipv6) {
		NL_SET_ERR_MSG(extack, "IPv6 is disabled on nexthop device");
		err = -EACCES;
		goto out;
	}

	if (!(dev->flags & IFF_UP)) {
		NL_SET_ERR_MSG(extack, "Nexthop device is not up");
		err = -ENETDOWN;
		goto out;
	}

	if (!ipv6_addr_any(&cfg->fc_prefsrc)) {
		if (!ipv6_chk_addr(net, &cfg->fc_prefsrc, dev, 0)) {
			NL_SET_ERR_MSG(extack, "Invalid source address");
			err = -EINVAL;
			goto out;
		}
		rt->fib6_prefsrc.addr = cfg->fc_prefsrc;
		rt->fib6_prefsrc.plen = 128;
	} else
		rt->fib6_prefsrc.plen = 0;

	rt->fib6_flags = cfg->fc_flags;

install_route:
	if (!(rt->fib6_flags & (RTF_LOCAL | RTF_ANYCAST)) &&
	    !netif_carrier_ok(dev))
		rt->fib6_nh.nh_flags |= RTNH_F_LINKDOWN;
	rt->fib6_nh.nh_flags |= (cfg->fc_flags & RTNH_F_ONLINK);
	rt->fib6_nh.nh_dev = dev;
	rt->fib6_table = table;

	cfg->fc_nlinfo.nl_net = dev_net(dev);

	if (idev)
		in6_dev_put(idev);

	return rt;
out:
	if (dev)
		dev_put(dev);
	if (idev)
		in6_dev_put(idev);

	fib6_info_release(rt);
	return ERR_PTR(err);
}