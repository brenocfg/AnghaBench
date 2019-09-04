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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mon_setup ; 
 int register_netdev (struct net_device*) ; 

struct net_device *rtl88eu_mon_init(void)
{
	struct net_device *dev;
	int err;

	dev = alloc_netdev(0, "mon%d", NET_NAME_UNKNOWN, mon_setup);
	if (!dev)
		goto fail;

	err = register_netdev(dev);
	if (err < 0)
		goto fail_free_dev;

	return dev;

fail_free_dev:
	free_netdev(dev);
fail:
	return NULL;
}