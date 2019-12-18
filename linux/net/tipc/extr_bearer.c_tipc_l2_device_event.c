#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tipc_bearer {int /*<<< orphan*/  addr; TYPE_1__* media; int /*<<< orphan*/  mtu; int /*<<< orphan*/  up; } ;
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ dev_addr; int /*<<< orphan*/  mtu; int /*<<< orphan*/  tipc_ptr; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* raw2addr ) (struct tipc_bearer*,int /*<<< orphan*/ *,char*) ;} ;

/* Variables and functions */
#define  NETDEV_CHANGE 134 
#define  NETDEV_CHANGEADDR 133 
#define  NETDEV_CHANGEMTU 132 
#define  NETDEV_CHANGENAME 131 
#define  NETDEV_GOING_DOWN 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  bearer_disable (struct net*,struct tipc_bearer*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net* dev_net (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_oper_up (struct net_device*) ; 
 struct tipc_bearer* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tipc_bearer*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_mtu_bad (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_reset_bearer (struct net*,struct tipc_bearer*) ; 
 int /*<<< orphan*/  trace_tipc_l2_device_event (struct net_device*,struct tipc_bearer*,unsigned long) ; 

__attribute__((used)) static int tipc_l2_device_event(struct notifier_block *nb, unsigned long evt,
				void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct net *net = dev_net(dev);
	struct tipc_bearer *b;

	b = rtnl_dereference(dev->tipc_ptr);
	if (!b)
		return NOTIFY_DONE;

	trace_tipc_l2_device_event(dev, b, evt);
	switch (evt) {
	case NETDEV_CHANGE:
		if (netif_carrier_ok(dev) && netif_oper_up(dev)) {
			test_and_set_bit_lock(0, &b->up);
			break;
		}
		/* fall through */
	case NETDEV_GOING_DOWN:
		clear_bit_unlock(0, &b->up);
		tipc_reset_bearer(net, b);
		break;
	case NETDEV_UP:
		test_and_set_bit_lock(0, &b->up);
		break;
	case NETDEV_CHANGEMTU:
		if (tipc_mtu_bad(dev, 0)) {
			bearer_disable(net, b);
			break;
		}
		b->mtu = dev->mtu;
		tipc_reset_bearer(net, b);
		break;
	case NETDEV_CHANGEADDR:
		b->media->raw2addr(b, &b->addr,
				   (char *)dev->dev_addr);
		tipc_reset_bearer(net, b);
		break;
	case NETDEV_UNREGISTER:
	case NETDEV_CHANGENAME:
		bearer_disable(net, b);
		break;
	}
	return NOTIFY_OK;
}