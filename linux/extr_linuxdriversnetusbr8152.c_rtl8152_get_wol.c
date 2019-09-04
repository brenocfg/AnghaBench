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
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; scalar_t__ supported; } ;

/* Variables and functions */
 scalar_t__ WAKE_ANY ; 
 int /*<<< orphan*/  __rtl_get_wol (struct r8152*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl_can_wakeup (struct r8152*) ; 
 scalar_t__ usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8152_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct r8152 *tp = netdev_priv(dev);

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	if (!rtl_can_wakeup(tp)) {
		wol->supported = 0;
		wol->wolopts = 0;
	} else {
		mutex_lock(&tp->control);
		wol->supported = WAKE_ANY;
		wol->wolopts = __rtl_get_wol(tp);
		mutex_unlock(&tp->control);
	}

	usb_autopm_put_interface(tp->intf);
}