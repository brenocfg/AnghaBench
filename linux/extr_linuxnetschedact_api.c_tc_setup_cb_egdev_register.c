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
typedef  int /*<<< orphan*/  tc_setup_cb_t ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __tc_setup_cb_egdev_register (struct net_device const*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int tc_setup_cb_egdev_register(const struct net_device *dev,
			       tc_setup_cb_t *cb, void *cb_priv)
{
	int err;

	rtnl_lock();
	err = __tc_setup_cb_egdev_register(dev, cb, cb_priv);
	rtnl_unlock();
	return err;
}