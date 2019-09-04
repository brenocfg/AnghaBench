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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_dev {struct net_device* dev; } ;
struct in6_addr {int dummy; } ;
struct TYPE_4__ {int plen; struct in6_addr addr; } ;
struct TYPE_3__ {struct net_device* nh_dev; struct in6_addr nh_gw; } ;
struct fib6_info {int dst_nocount; int dst_host; int fib6_flags; int /*<<< orphan*/  fib6_table; TYPE_2__ fib6_dst; TYPE_1__ fib6_nh; int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_protocol; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fib6_info* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT6_TABLE_LOCAL ; 
 int RTF_ANYCAST ; 
 int RTF_LOCAL ; 
 int RTF_NONEXTHOP ; 
 int RTF_UP ; 
 int /*<<< orphan*/  RTN_ANYCAST ; 
 int /*<<< orphan*/  RTN_LOCAL ; 
 int /*<<< orphan*/  RTPROT_KERNEL ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 struct fib6_info* fib6_info_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ l3mdev_fib_table (struct net_device*) ; 

struct fib6_info *addrconf_f6i_alloc(struct net *net,
				     struct inet6_dev *idev,
				     const struct in6_addr *addr,
				     bool anycast, gfp_t gfp_flags)
{
	u32 tb_id;
	struct net_device *dev = idev->dev;
	struct fib6_info *f6i;

	f6i = fib6_info_alloc(gfp_flags);
	if (!f6i)
		return ERR_PTR(-ENOMEM);

	f6i->dst_nocount = true;
	f6i->dst_host = true;
	f6i->fib6_protocol = RTPROT_KERNEL;
	f6i->fib6_flags = RTF_UP | RTF_NONEXTHOP;
	if (anycast) {
		f6i->fib6_type = RTN_ANYCAST;
		f6i->fib6_flags |= RTF_ANYCAST;
	} else {
		f6i->fib6_type = RTN_LOCAL;
		f6i->fib6_flags |= RTF_LOCAL;
	}

	f6i->fib6_nh.nh_gw = *addr;
	dev_hold(dev);
	f6i->fib6_nh.nh_dev = dev;
	f6i->fib6_dst.addr = *addr;
	f6i->fib6_dst.plen = 128;
	tb_id = l3mdev_fib_table(idev->dev) ? : RT6_TABLE_LOCAL;
	f6i->fib6_table = fib6_get_table(net, tb_id);

	return f6i;
}