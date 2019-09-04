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
struct r8152 {int version; scalar_t__ coalesce; int /*<<< orphan*/  intf; int /*<<< orphan*/  control; int /*<<< orphan*/  netdev; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ rx_coalesce_usecs; } ;

/* Variables and functions */
 scalar_t__ COALESCE_SLOW ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  RTL_VER_01 130 
#define  RTL_VER_02 129 
#define  RTL_VER_07 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8153_set_rx_early_timeout (struct r8152*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_set_coalesce(struct net_device *netdev,
				struct ethtool_coalesce *coalesce)
{
	struct r8152 *tp = netdev_priv(netdev);
	int ret;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		return -EOPNOTSUPP;
	default:
		break;
	}

	if (coalesce->rx_coalesce_usecs > COALESCE_SLOW)
		return -EINVAL;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&tp->control);

	if (tp->coalesce != coalesce->rx_coalesce_usecs) {
		tp->coalesce = coalesce->rx_coalesce_usecs;

		if (netif_running(tp->netdev) && netif_carrier_ok(netdev))
			r8153_set_rx_early_timeout(tp);
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

	return ret;
}