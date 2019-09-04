#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usbnet {struct usb_device* udev; } ;
struct TYPE_10__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_4__ descriptor; } ;
struct notifier_block {int dummy; } ;
struct TYPE_9__ {TYPE_2__* parent; } ;
struct net_device {int num_tx_queues; int /*<<< orphan*/  name; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  ifindex; TYPE_3__ dev; } ;
struct cflayer {int /*<<< orphan*/  name; } ;
struct caif_dev_common {int use_frag; int use_fcs; int use_stx; int /*<<< orphan*/ * flowctrl; int /*<<< orphan*/  link_select; } ;
typedef  int /*<<< orphan*/  common ;
struct TYPE_11__ {int /*<<< orphan*/  func; } ;
struct TYPE_8__ {TYPE_1__* driver; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_LINK_HIGH_BANDW ; 
 int /*<<< orphan*/  CFUSB_MAX_HEADLEN ; 
 int ENOMEM ; 
 unsigned long NETDEV_REGISTER ; 
 unsigned long NETDEV_UNREGISTER ; 
 scalar_t__ STE_USB_PID_CAIF ; 
 scalar_t__ STE_USB_VID ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caif_enroll_dev (struct net_device*,struct caif_dev_common*,struct cflayer*,int /*<<< orphan*/ ,struct cflayer**,int /*<<< orphan*/ *) ; 
 TYPE_5__ caif_usb_type ; 
 struct cflayer* cfusbl_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_add_pack (TYPE_5__*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct caif_dev_common*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int pack_added ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cfusbl_device_notify(struct notifier_block *me, unsigned long what,
				void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct caif_dev_common common;
	struct cflayer *layer, *link_support;
	struct usbnet *usbnet;
	struct usb_device *usbdev;

	/* Check whether we have a NCM device, and find its VID/PID. */
	if (!(dev->dev.parent && dev->dev.parent->driver &&
	      strcmp(dev->dev.parent->driver->name, "cdc_ncm") == 0))
		return 0;

	usbnet = netdev_priv(dev);
	usbdev = usbnet->udev;

	pr_debug("USB CDC NCM device VID:0x%4x PID:0x%4x\n",
		le16_to_cpu(usbdev->descriptor.idVendor),
		le16_to_cpu(usbdev->descriptor.idProduct));

	/* Check for VID/PID that supports CAIF */
	if (!(le16_to_cpu(usbdev->descriptor.idVendor) == STE_USB_VID &&
		le16_to_cpu(usbdev->descriptor.idProduct) == STE_USB_PID_CAIF))
		return 0;

	if (what == NETDEV_UNREGISTER)
		module_put(THIS_MODULE);

	if (what != NETDEV_REGISTER)
		return 0;

	__module_get(THIS_MODULE);

	memset(&common, 0, sizeof(common));
	common.use_frag = false;
	common.use_fcs = false;
	common.use_stx = false;
	common.link_select = CAIF_LINK_HIGH_BANDW;
	common.flowctrl = NULL;

	link_support = cfusbl_create(dev->ifindex, dev->dev_addr,
					dev->broadcast);

	if (!link_support)
		return -ENOMEM;

	if (dev->num_tx_queues > 1)
		pr_warn("USB device uses more than one tx queue\n");

	caif_enroll_dev(dev, &common, link_support, CFUSB_MAX_HEADLEN,
			&layer, &caif_usb_type.func);
	if (!pack_added)
		dev_add_pack(&caif_usb_type);
	pack_added = true;

	strlcpy(layer->name, dev->name, sizeof(layer->name));

	return 0;
}