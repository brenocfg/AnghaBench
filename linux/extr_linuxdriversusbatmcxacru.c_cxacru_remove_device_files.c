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
struct usbatm_data {struct usb_interface* usb_intf; } ;
struct usb_interface {int dummy; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXACRU_ALL_FILES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REMOVE ; 

__attribute__((used)) static void cxacru_remove_device_files(struct usbatm_data *usbatm_instance,
		struct atm_dev *atm_dev)
{
	struct usb_interface *intf = usbatm_instance->usb_intf;

	#define CXACRU_DEVICE_REMOVE_FILE(_name) \
		device_remove_file(&intf->dev, &dev_attr_##_name);
	CXACRU_ALL_FILES(REMOVE);
	#undef CXACRU_DEVICE_REMOVE_FILE
}