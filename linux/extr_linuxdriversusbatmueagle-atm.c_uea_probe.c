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
struct usbatm_data {struct uea_softc* driver_data; } ;
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct uea_softc {int /*<<< orphan*/  kthread; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_PHY_SIG_LOST ; 
 size_t UEA_CHIP_VERSION (struct usb_device_id const*) ; 
 scalar_t__ UEA_IS_PREFIRM (struct usb_device_id const*) ; 
 int /*<<< orphan*/  UPDATE_ATM_SIGNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * chip_name ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_enters (struct usb_device*) ; 
 int /*<<< orphan*/  uea_info (struct usb_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uea_load_firmware (struct usb_device*,size_t) ; 
 int /*<<< orphan*/  uea_usbatm_driver ; 
 struct usbatm_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 
 int usbatm_usb_probe (struct usb_interface*,struct usb_device_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uea_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_device *usb = interface_to_usbdev(intf);
	int ret;

	uea_enters(usb);
	uea_info(usb, "ADSL device founded vid (%#X) pid (%#X) Rev (%#X): %s\n",
		le16_to_cpu(usb->descriptor.idVendor),
		le16_to_cpu(usb->descriptor.idProduct),
		le16_to_cpu(usb->descriptor.bcdDevice),
		chip_name[UEA_CHIP_VERSION(id)]);

	usb_reset_device(usb);

	if (UEA_IS_PREFIRM(id))
		return uea_load_firmware(usb, UEA_CHIP_VERSION(id));

	ret = usbatm_usb_probe(intf, id, &uea_usbatm_driver);
	if (ret == 0) {
		struct usbatm_data *usbatm = usb_get_intfdata(intf);
		struct uea_softc *sc = usbatm->driver_data;

		/* Ensure carrier is initialized to off as early as possible */
		UPDATE_ATM_SIGNAL(ATM_PHY_SIG_LOST);

		/* Only start the worker thread when all init is done */
		wake_up_process(sc->kthread);
	}

	return ret;
}