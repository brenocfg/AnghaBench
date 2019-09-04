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
struct r8152 {int saved_wolopts; int /*<<< orphan*/  intf; int /*<<< orphan*/  control; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int WAKE_ANY ; 
 int /*<<< orphan*/  __rtl_set_wol (struct r8152*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl_can_wakeup (struct r8152*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct r8152 *tp = netdev_priv(dev);
	int ret;

	if (!rtl_can_wakeup(tp))
		return -EOPNOTSUPP;

	if (wol->wolopts & ~WAKE_ANY)
		return -EINVAL;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out_set_wol;

	mutex_lock(&tp->control);

	__rtl_set_wol(tp, wol->wolopts);
	tp->saved_wolopts = wol->wolopts & WAKE_ANY;

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out_set_wol:
	return ret;
}