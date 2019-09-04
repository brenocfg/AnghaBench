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
struct usb_string {scalar_t__ s; int /*<<< orphan*/  id; } ;
struct usb_gadget_strings {struct usb_string* strings; } ;
struct usb_device_descriptor {int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  iSerialNumber; void* bcdDevice; void* idProduct; void* idVendor; } ;
struct usb_composite_overwrite {scalar_t__ product; scalar_t__ manufacturer; scalar_t__ serial_number; scalar_t__ bcdDevice; scalar_t__ idProduct; scalar_t__ idVendor; } ;
struct usb_composite_dev {scalar_t__ def_manufacturer; int /*<<< orphan*/  gadget; TYPE_1__* driver; struct usb_device_descriptor desc; } ;
struct TYPE_2__ {struct usb_gadget_strings** strings; } ;

/* Variables and functions */
 size_t USB_GADGET_MANUFACTURER_IDX ; 
 size_t USB_GADGET_PRODUCT_IDX ; 
 size_t USB_GADGET_SERIAL_IDX ; 
 scalar_t__ composite_default_mfr (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

void usb_composite_overwrite_options(struct usb_composite_dev *cdev,
		struct usb_composite_overwrite *covr)
{
	struct usb_device_descriptor	*desc = &cdev->desc;
	struct usb_gadget_strings	*gstr = cdev->driver->strings[0];
	struct usb_string		*dev_str = gstr->strings;

	if (covr->idVendor)
		desc->idVendor = cpu_to_le16(covr->idVendor);

	if (covr->idProduct)
		desc->idProduct = cpu_to_le16(covr->idProduct);

	if (covr->bcdDevice)
		desc->bcdDevice = cpu_to_le16(covr->bcdDevice);

	if (covr->serial_number) {
		desc->iSerialNumber = dev_str[USB_GADGET_SERIAL_IDX].id;
		dev_str[USB_GADGET_SERIAL_IDX].s = covr->serial_number;
	}
	if (covr->manufacturer) {
		desc->iManufacturer = dev_str[USB_GADGET_MANUFACTURER_IDX].id;
		dev_str[USB_GADGET_MANUFACTURER_IDX].s = covr->manufacturer;

	} else if (!strlen(dev_str[USB_GADGET_MANUFACTURER_IDX].s)) {
		desc->iManufacturer = dev_str[USB_GADGET_MANUFACTURER_IDX].id;
		cdev->def_manufacturer = composite_default_mfr(cdev->gadget);
		dev_str[USB_GADGET_MANUFACTURER_IDX].s = cdev->def_manufacturer;
	}

	if (covr->product) {
		desc->iProduct = dev_str[USB_GADGET_PRODUCT_IDX].id;
		dev_str[USB_GADGET_PRODUCT_IDX].s = covr->product;
	}
}