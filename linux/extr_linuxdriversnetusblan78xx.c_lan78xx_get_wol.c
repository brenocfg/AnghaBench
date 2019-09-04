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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct lan78xx_priv {int /*<<< orphan*/  wol; } ;
struct lan78xx_net {int /*<<< orphan*/  intf; scalar_t__* data; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; scalar_t__ supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CFG0 ; 
 int USB_CFG_RMT_WKP_ ; 
 scalar_t__ WAKE_ALL ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 struct lan78xx_net* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan78xx_get_wol(struct net_device *netdev,
			    struct ethtool_wolinfo *wol)
{
	struct lan78xx_net *dev = netdev_priv(netdev);
	int ret;
	u32 buf;
	struct lan78xx_priv *pdata = (struct lan78xx_priv *)(dev->data[0]);

	if (usb_autopm_get_interface(dev->intf) < 0)
			return;

	ret = lan78xx_read_reg(dev, USB_CFG0, &buf);
	if (unlikely(ret < 0)) {
		wol->supported = 0;
		wol->wolopts = 0;
	} else {
		if (buf & USB_CFG_RMT_WKP_) {
			wol->supported = WAKE_ALL;
			wol->wolopts = pdata->wol;
		} else {
			wol->supported = 0;
			wol->wolopts = 0;
		}
	}

	usb_autopm_put_interface(dev->intf);
}