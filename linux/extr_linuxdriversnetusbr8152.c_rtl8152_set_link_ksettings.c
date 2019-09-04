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
struct r8152 {int /*<<< orphan*/  intf; int /*<<< orphan*/  control; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 int rtl8152_set_speed (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_set_link_ksettings(struct net_device *dev,
				      const struct ethtool_link_ksettings *cmd)
{
	struct r8152 *tp = netdev_priv(dev);
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	ret = rtl8152_set_speed(tp, cmd->base.autoneg, cmd->base.speed,
				cmd->base.duplex);
	if (!ret) {
		tp->autoneg = cmd->base.autoneg;
		tp->speed = cmd->base.speed;
		tp->duplex = cmd->base.duplex;
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}