#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct usb_interface {int needs_remote_wakeup; int /*<<< orphan*/  usb_dev; TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_3__ descriptor; } ;
struct phy_dev {int /*<<< orphan*/  gdm_ed; struct usb_interface* intf; struct usb_device* usbdev; int /*<<< orphan*/  get_endian; int /*<<< orphan*/  rcv_func; int /*<<< orphan*/  send_sdu_func; int /*<<< orphan*/  send_hci_func; void* priv_dev; } ;
struct lte_udev {int /*<<< orphan*/  gdm_ed; struct usb_interface* intf; struct usb_device* usbdev; int /*<<< orphan*/  get_endian; int /*<<< orphan*/  rcv_func; int /*<<< orphan*/  send_sdu_func; int /*<<< orphan*/  send_hci_func; void* priv_dev; } ;
struct TYPE_4__ {int bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_SUSPEND_TIMER ; 
 int /*<<< orphan*/  ENDIANNESS_BIG ; 
 int /*<<< orphan*/  ENDIANNESS_LITTLE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NETWORK_INTERFACE ; 
 scalar_t__ PID_GDM7243 ; 
 scalar_t__ __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdm_usb_get_endian ; 
 int /*<<< orphan*/  gdm_usb_hci_send ; 
 int /*<<< orphan*/  gdm_usb_recv ; 
 int /*<<< orphan*/  gdm_usb_sdu_send ; 
 int init_usb (struct phy_dev*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct phy_dev*) ; 
 struct phy_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  release_usb (struct phy_dev*) ; 
 int request_mac_address (struct phy_dev*) ; 
 int /*<<< orphan*/  start_rx_proc (struct phy_dev*) ; 
 int /*<<< orphan*/  usb_enable_autosuspend (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct phy_dev*) ; 

__attribute__((used)) static int gdm_usb_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	int ret = 0;
	struct phy_dev *phy_dev = NULL;
	struct lte_udev *udev = NULL;
	u16 idVendor, idProduct;
	int bInterfaceNumber;
	struct usb_device *usbdev = interface_to_usbdev(intf);

	bInterfaceNumber = intf->cur_altsetting->desc.bInterfaceNumber;
	idVendor = __le16_to_cpu(usbdev->descriptor.idVendor);
	idProduct = __le16_to_cpu(usbdev->descriptor.idProduct);

	pr_info("net vid = 0x%04x pid = 0x%04x\n", idVendor, idProduct);

	if (bInterfaceNumber > NETWORK_INTERFACE) {
		pr_info("not a network device\n");
		return -ENODEV;
	}

	phy_dev = kzalloc(sizeof(*phy_dev), GFP_KERNEL);
	if (!phy_dev)
		return -ENOMEM;

	udev = kzalloc(sizeof(*udev), GFP_KERNEL);
	if (!udev) {
		ret = -ENOMEM;
		goto err_udev;
	}

	phy_dev->priv_dev = (void *)udev;
	phy_dev->send_hci_func = gdm_usb_hci_send;
	phy_dev->send_sdu_func = gdm_usb_sdu_send;
	phy_dev->rcv_func = gdm_usb_recv;
	phy_dev->get_endian = gdm_usb_get_endian;

	udev->usbdev = usbdev;
	ret = init_usb(udev);
	if (ret < 0) {
		dev_err(intf->usb_dev, "init_usb func failed\n");
		goto err_init_usb;
	}
	udev->intf = intf;

	intf->needs_remote_wakeup = 1;
	usb_enable_autosuspend(usbdev);
	pm_runtime_set_autosuspend_delay(&usbdev->dev, AUTO_SUSPEND_TIMER);

	/* List up hosts with big endians, otherwise,
	 * defaults to little endian
	 */
	if (idProduct == PID_GDM7243)
		udev->gdm_ed = ENDIANNESS_BIG;
	else
		udev->gdm_ed = ENDIANNESS_LITTLE;

	ret = request_mac_address(udev);
	if (ret < 0) {
		dev_err(intf->usb_dev, "request Mac address failed\n");
		goto err_mac_address;
	}

	start_rx_proc(phy_dev);
	usb_get_dev(usbdev);
	usb_set_intfdata(intf, phy_dev);

	return 0;

err_mac_address:
	release_usb(udev);
err_init_usb:
	kfree(udev);
err_udev:
	kfree(phy_dev);

	return ret;
}