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
struct TYPE_4__ {scalar_t__ sa_family; } ;
struct rtentry {int rt_flags; int rt_mtu; int rt_window; int rt_irtt; TYPE_2__ rt_gateway; scalar_t__ rt_dev; scalar_t__ rt_metric; TYPE_2__ rt_genmask; TYPE_2__ rt_dst; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_local; int /*<<< orphan*/  ifa_label; struct in_ifaddr* ifa_next; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;
struct TYPE_3__ {struct net* nl_net; } ;
struct fib_config {int fc_dst_len; scalar_t__ fc_scope; unsigned int fc_type; int fc_mx_len; struct nlattr* fc_mx; void* fc_gw; int /*<<< orphan*/  fc_table; int /*<<< orphan*/  fc_prefsrc; int /*<<< orphan*/  fc_oif; scalar_t__ fc_priority; int /*<<< orphan*/  fc_protocol; int /*<<< orphan*/  fc_nlflags; void* fc_dst; TYPE_1__ fc_nlinfo; } ;
typedef  void* __be32 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  NLM_F_CREATE ; 
 int /*<<< orphan*/  RTAX_ADVMSS ; 
 int /*<<< orphan*/  RTAX_RTT ; 
 int /*<<< orphan*/  RTAX_WINDOW ; 
 int RTF_GATEWAY ; 
 int RTF_HOST ; 
 int RTF_IRTT ; 
 int RTF_MTU ; 
 int RTF_REJECT ; 
 int RTF_WINDOW ; 
 unsigned int RTN_UNICAST ; 
 unsigned int RTN_UNREACHABLE ; 
 int /*<<< orphan*/  RTPROT_BOOT ; 
 scalar_t__ RT_SCOPE_HOST ; 
 scalar_t__ RT_SCOPE_LINK ; 
 scalar_t__ RT_SCOPE_NOWHERE ; 
 scalar_t__ RT_SCOPE_UNIVERSE ; 
 int SIOCDELRT ; 
 struct net_device* __dev_get_by_name (struct net*,char*) ; 
 struct in_device* __in_dev_get_rtnl (struct net_device*) ; 
 scalar_t__ bad_mask (void*,void*) ; 
 scalar_t__ copy_from_user (char*,scalar_t__,int) ; 
 unsigned int inet_addr_type_table (struct net*,void*,int /*<<< orphan*/ ) ; 
 int inet_mask_len (void*) ; 
 struct nlattr* kcalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3mdev_fib_table (struct net_device*) ; 
 int /*<<< orphan*/  memset (struct fib_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_total_size (int) ; 
 int put_rtax (struct nlattr*,int,int /*<<< orphan*/ ,int) ; 
 void* sk_extract_addr (TYPE_2__*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtentry_to_fib_config(struct net *net, int cmd, struct rtentry *rt,
				 struct fib_config *cfg)
{
	__be32 addr;
	int plen;

	memset(cfg, 0, sizeof(*cfg));
	cfg->fc_nlinfo.nl_net = net;

	if (rt->rt_dst.sa_family != AF_INET)
		return -EAFNOSUPPORT;

	/*
	 * Check mask for validity:
	 * a) it must be contiguous.
	 * b) destination must have all host bits clear.
	 * c) if application forgot to set correct family (AF_INET),
	 *    reject request unless it is absolutely clear i.e.
	 *    both family and mask are zero.
	 */
	plen = 32;
	addr = sk_extract_addr(&rt->rt_dst);
	if (!(rt->rt_flags & RTF_HOST)) {
		__be32 mask = sk_extract_addr(&rt->rt_genmask);

		if (rt->rt_genmask.sa_family != AF_INET) {
			if (mask || rt->rt_genmask.sa_family)
				return -EAFNOSUPPORT;
		}

		if (bad_mask(mask, addr))
			return -EINVAL;

		plen = inet_mask_len(mask);
	}

	cfg->fc_dst_len = plen;
	cfg->fc_dst = addr;

	if (cmd != SIOCDELRT) {
		cfg->fc_nlflags = NLM_F_CREATE;
		cfg->fc_protocol = RTPROT_BOOT;
	}

	if (rt->rt_metric)
		cfg->fc_priority = rt->rt_metric - 1;

	if (rt->rt_flags & RTF_REJECT) {
		cfg->fc_scope = RT_SCOPE_HOST;
		cfg->fc_type = RTN_UNREACHABLE;
		return 0;
	}

	cfg->fc_scope = RT_SCOPE_NOWHERE;
	cfg->fc_type = RTN_UNICAST;

	if (rt->rt_dev) {
		char *colon;
		struct net_device *dev;
		char devname[IFNAMSIZ];

		if (copy_from_user(devname, rt->rt_dev, IFNAMSIZ-1))
			return -EFAULT;

		devname[IFNAMSIZ-1] = 0;
		colon = strchr(devname, ':');
		if (colon)
			*colon = 0;
		dev = __dev_get_by_name(net, devname);
		if (!dev)
			return -ENODEV;
		cfg->fc_oif = dev->ifindex;
		cfg->fc_table = l3mdev_fib_table(dev);
		if (colon) {
			struct in_ifaddr *ifa;
			struct in_device *in_dev = __in_dev_get_rtnl(dev);
			if (!in_dev)
				return -ENODEV;
			*colon = ':';
			for (ifa = in_dev->ifa_list; ifa; ifa = ifa->ifa_next)
				if (strcmp(ifa->ifa_label, devname) == 0)
					break;
			if (!ifa)
				return -ENODEV;
			cfg->fc_prefsrc = ifa->ifa_local;
		}
	}

	addr = sk_extract_addr(&rt->rt_gateway);
	if (rt->rt_gateway.sa_family == AF_INET && addr) {
		unsigned int addr_type;

		cfg->fc_gw = addr;
		addr_type = inet_addr_type_table(net, addr, cfg->fc_table);
		if (rt->rt_flags & RTF_GATEWAY &&
		    addr_type == RTN_UNICAST)
			cfg->fc_scope = RT_SCOPE_UNIVERSE;
	}

	if (cmd == SIOCDELRT)
		return 0;

	if (rt->rt_flags & RTF_GATEWAY && !cfg->fc_gw)
		return -EINVAL;

	if (cfg->fc_scope == RT_SCOPE_NOWHERE)
		cfg->fc_scope = RT_SCOPE_LINK;

	if (rt->rt_flags & (RTF_MTU | RTF_WINDOW | RTF_IRTT)) {
		struct nlattr *mx;
		int len = 0;

		mx = kcalloc(3, nla_total_size(4), GFP_KERNEL);
		if (!mx)
			return -ENOMEM;

		if (rt->rt_flags & RTF_MTU)
			len = put_rtax(mx, len, RTAX_ADVMSS, rt->rt_mtu - 40);

		if (rt->rt_flags & RTF_WINDOW)
			len = put_rtax(mx, len, RTAX_WINDOW, rt->rt_window);

		if (rt->rt_flags & RTF_IRTT)
			len = put_rtax(mx, len, RTAX_RTT, rt->rt_irtt << 3);

		cfg->fc_mx = mx;
		cfg->fc_mx_len = len;
	}

	return 0;
}