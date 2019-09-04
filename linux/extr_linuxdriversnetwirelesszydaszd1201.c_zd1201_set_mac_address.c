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
struct zd1201 {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ZD1201_RID_CNFOWNMACADDR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_mac_reset (struct zd1201*) ; 
 int zd1201_setconfig (struct zd1201*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zd1201_set_mac_address(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct zd1201 *zd = netdev_priv(dev);
	int err;

	if (!zd)
		return -ENODEV;

	err = zd1201_setconfig(zd, ZD1201_RID_CNFOWNMACADDR, 
	    addr->sa_data, dev->addr_len, 1);
	if (err)
		return err;
	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	return zd1201_mac_reset(zd);
}