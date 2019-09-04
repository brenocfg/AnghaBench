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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct r8192_priv {int /*<<< orphan*/ * pFirmware; struct usb_device* udev; int /*<<< orphan*/  ieee80211; } ;
struct net_device {int watchdog_timeo; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/ * wireless_handlers; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_ieee80211 (int) ; 
 scalar_t__ dev_alloc_name (struct net_device*,char*) ; 
 int /*<<< orphan*/  free_ieee80211 (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 char* ifname ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  r8192_wx_handlers_def ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_down (struct net_device*) ; 
 scalar_t__ rtl8192_init (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_netdev_ops ; 
 int /*<<< orphan*/  rtl8192_proc_init_one (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_usb_deleteendpoints (struct net_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct net_device*) ; 

__attribute__((used)) static int rtl8192_usb_probe(struct usb_interface *intf,
			     const struct usb_device_id *id)
{
	struct net_device *dev = NULL;
	struct r8192_priv *priv = NULL;
	struct usb_device *udev = interface_to_usbdev(intf);
	int ret;

	RT_TRACE(COMP_INIT, "Oops: i'm coming\n");

	dev = alloc_ieee80211(sizeof(struct r8192_priv));
	if (!dev)
		return -ENOMEM;

	usb_set_intfdata(intf, dev);
	SET_NETDEV_DEV(dev, &intf->dev);
	priv = ieee80211_priv(dev);
	priv->ieee80211 = netdev_priv(dev);
	priv->udev = udev;

	dev->netdev_ops = &rtl8192_netdev_ops;

	dev->wireless_handlers = &r8192_wx_handlers_def;

	dev->type = ARPHRD_ETHER;

	dev->watchdog_timeo = HZ * 3;

	if (dev_alloc_name(dev, ifname) < 0) {
		RT_TRACE(COMP_INIT,
			 "Oops: devname already taken! Trying wlan%%d...\n");
		ifname = "wlan%d";
		dev_alloc_name(dev, ifname);
	}

	RT_TRACE(COMP_INIT, "Driver probe completed1\n");
	if (rtl8192_init(dev) != 0) {
		RT_TRACE(COMP_ERR, "Initialization failed");
		ret = -ENODEV;
		goto fail;
	}
	netif_carrier_off(dev);
	netif_stop_queue(dev);

	ret = register_netdev(dev);
	if (ret)
		goto fail2;

	RT_TRACE(COMP_INIT, "dev name=======> %s\n", dev->name);
	rtl8192_proc_init_one(dev);


	RT_TRACE(COMP_INIT, "Driver probe completed\n");
	return 0;

fail2:
	rtl8192_down(dev);
fail:
	kfree(priv->pFirmware);
	priv->pFirmware = NULL;
	rtl8192_usb_deleteendpoints(dev);
	msleep(10);
	free_ieee80211(dev);

	RT_TRACE(COMP_ERR, "wlan driver load failed\n");
	return ret;
}