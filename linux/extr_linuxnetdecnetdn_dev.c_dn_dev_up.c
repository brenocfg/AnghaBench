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
struct net_device {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  dn_ptr; } ;
struct dn_ifaddr {int /*<<< orphan*/  ifa_label; int /*<<< orphan*/  ifa_scope; scalar_t__ ifa_flags; scalar_t__ ifa_address; scalar_t__ ifa_local; } ;
struct dn_dev {int dummy; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_LOOPBACK ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 scalar_t__ decnet_address ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct dn_ifaddr* dn_dev_alloc_ifa () ; 
 struct dn_dev* dn_dev_create (struct net_device*,int*) ; 
 scalar_t__ dn_dev_set_default (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_dev_set_ifa (struct net_device*,struct dn_ifaddr*) ; 
 scalar_t__ dn_eth2dn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_hiord ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dn_dev* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dn_dev_up(struct net_device *dev)
{
	struct dn_ifaddr *ifa;
	__le16 addr = decnet_address;
	int maybe_default = 0;
	struct dn_dev *dn_db = rtnl_dereference(dev->dn_ptr);

	if ((dev->type != ARPHRD_ETHER) && (dev->type != ARPHRD_LOOPBACK))
		return;

	/*
	 * Need to ensure that loopback device has a dn_db attached to it
	 * to allow creation of neighbours against it, even though it might
	 * not have a local address of its own. Might as well do the same for
	 * all autoconfigured interfaces.
	 */
	if (dn_db == NULL) {
		int err;
		dn_db = dn_dev_create(dev, &err);
		if (dn_db == NULL)
			return;
	}

	if (dev->type == ARPHRD_ETHER) {
		if (memcmp(dev->dev_addr, dn_hiord, 4) != 0)
			return;
		addr = dn_eth2dn(dev->dev_addr);
		maybe_default = 1;
	}

	if (addr == 0)
		return;

	if ((ifa = dn_dev_alloc_ifa()) == NULL)
		return;

	ifa->ifa_local = ifa->ifa_address = addr;
	ifa->ifa_flags = 0;
	ifa->ifa_scope = RT_SCOPE_UNIVERSE;
	strcpy(ifa->ifa_label, dev->name);

	dn_dev_set_ifa(dev, ifa);

	/*
	 * Automagically set the default device to the first automatically
	 * configured ethernet card in the system.
	 */
	if (maybe_default) {
		dev_hold(dev);
		if (dn_dev_set_default(dev, 0))
			dev_put(dev);
	}
}