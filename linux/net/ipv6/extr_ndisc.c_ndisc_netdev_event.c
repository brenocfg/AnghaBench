#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct netdev_notifier_change_info {int flags_changed; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {TYPE_2__* devconf_all; } ;
struct net {TYPE_3__ ipv6; } ;
struct TYPE_4__ {int /*<<< orphan*/  ndisc_notify; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndisc_notify; } ;

/* Variables and functions */
 int IFF_NOARP ; 
#define  NETDEV_CHANGE 132 
#define  NETDEV_CHANGEADDR 131 
#define  NETDEV_DOWN 130 
#define  NETDEV_NOTIFY_PEERS 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib6_run_gc (int /*<<< orphan*/ ,struct net*,int) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/  ndisc_send_unsol_na (struct net_device*) ; 
 int /*<<< orphan*/  neigh_carrier_down (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_changeaddr (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int ndisc_netdev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct netdev_notifier_change_info *change_info;
	struct net *net = dev_net(dev);
	struct inet6_dev *idev;

	switch (event) {
	case NETDEV_CHANGEADDR:
		neigh_changeaddr(&nd_tbl, dev);
		fib6_run_gc(0, net, false);
		/* fallthrough */
	case NETDEV_UP:
		idev = in6_dev_get(dev);
		if (!idev)
			break;
		if (idev->cnf.ndisc_notify ||
		    net->ipv6.devconf_all->ndisc_notify)
			ndisc_send_unsol_na(dev);
		in6_dev_put(idev);
		break;
	case NETDEV_CHANGE:
		change_info = ptr;
		if (change_info->flags_changed & IFF_NOARP)
			neigh_changeaddr(&nd_tbl, dev);
		if (!netif_carrier_ok(dev))
			neigh_carrier_down(&nd_tbl, dev);
		break;
	case NETDEV_DOWN:
		neigh_ifdown(&nd_tbl, dev);
		fib6_run_gc(0, net, false);
		break;
	case NETDEV_NOTIFY_PEERS:
		ndisc_send_unsol_na(dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}