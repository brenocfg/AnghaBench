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
typedef  scalar_t__ u32 ;
struct r8152 {int version; int /*<<< orphan*/  intf; int /*<<< orphan*/  control; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_RMS ; 
#define  RTL_VER_01 130 
#define  RTL_VER_02 129 
#define  RTL_VER_07 128 
 scalar_t__ VLAN_ETH_HLEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r8153_set_rx_early_size (struct r8152*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8152_change_mtu(struct net_device *dev, int new_mtu)
{
	struct r8152 *tp = netdev_priv(dev);
	int ret;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		dev->mtu = new_mtu;
		return 0;
	default:
		break;
	}

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&tp->control);

	dev->mtu = new_mtu;

	if (netif_running(dev)) {
		u32 rms = new_mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;

		ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, rms);

		if (netif_carrier_ok(dev))
			r8153_set_rx_early_size(tp);
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

	return ret;
}