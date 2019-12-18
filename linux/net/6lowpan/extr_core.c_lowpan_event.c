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
struct net_device {scalar_t__ type; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr32; int /*<<< orphan*/  s6_addr; } ;
struct TYPE_5__ {TYPE_1__* table; } ;
struct TYPE_6__ {TYPE_2__ ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_6LOWPAN ; 
 int /*<<< orphan*/  LOWPAN_IPHC_CTX_FLAG_ACTIVE ; 
 int LOWPAN_IPHC_CTX_TABLE_SIZE ; 
 int /*<<< orphan*/  LOWPAN_LLTYPE_IEEE802154 ; 
#define  NETDEV_CHANGE 130 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  __ipv6_addr_set_half (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_add_linklocal (struct inet6_dev*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_ifid_802154_6lowpan (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int) ; 
 TYPE_3__* lowpan_dev (struct net_device*) ; 
 int /*<<< orphan*/  lowpan_is_ll (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int lowpan_event(struct notifier_block *unused,
			unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct inet6_dev *idev;
	struct in6_addr addr;
	int i;

	if (dev->type != ARPHRD_6LOWPAN)
		return NOTIFY_DONE;

	idev = __in6_dev_get(dev);
	if (!idev)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
	case NETDEV_CHANGE:
		/* (802.15.4 6LoWPAN short address slaac handling */
		if (lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154) &&
		    addrconf_ifid_802154_6lowpan(addr.s6_addr + 8, dev) == 0) {
			__ipv6_addr_set_half(&addr.s6_addr32[0],
					     htonl(0xFE800000), 0);
			addrconf_add_linklocal(idev, &addr, 0);
		}
		break;
	case NETDEV_DOWN:
		for (i = 0; i < LOWPAN_IPHC_CTX_TABLE_SIZE; i++)
			clear_bit(LOWPAN_IPHC_CTX_FLAG_ACTIVE,
				  &lowpan_dev(dev)->ctx.table[i].flags);
		break;
	default:
		return NOTIFY_DONE;
	}

	return NOTIFY_OK;
}