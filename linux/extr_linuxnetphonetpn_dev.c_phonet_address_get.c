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
typedef  int u8 ;
struct phonet_device {int /*<<< orphan*/  addrs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int PN_NO_ADDR ; 
 struct phonet_device* __phonet_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 struct net_device* phonet_device_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

u8 phonet_address_get(struct net_device *dev, u8 daddr)
{
	struct phonet_device *pnd;
	u8 saddr;

	rcu_read_lock();
	pnd = __phonet_get_rcu(dev);
	if (pnd) {
		BUG_ON(bitmap_empty(pnd->addrs, 64));

		/* Use same source address as destination, if possible */
		if (test_bit(daddr >> 2, pnd->addrs))
			saddr = daddr;
		else
			saddr = find_first_bit(pnd->addrs, 64) << 2;
	} else
		saddr = PN_NO_ADDR;
	rcu_read_unlock();

	if (saddr == PN_NO_ADDR) {
		/* Fallback to another device */
		struct net_device *def_dev;

		def_dev = phonet_device_get(dev_net(dev));
		if (def_dev) {
			if (def_dev != dev)
				saddr = phonet_address_get(def_dev, daddr);
			dev_put(def_dev);
		}
	}
	return saddr;
}