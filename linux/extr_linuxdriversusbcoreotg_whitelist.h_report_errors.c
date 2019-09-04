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
struct TYPE_2__ {scalar_t__ bDeviceClass; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_CRIT ; 
 scalar_t__ USB_CLASS_HUB ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void report_errors(struct usb_device *dev)
{
	/* OTG MESSAGE: report errors here, customize to match your product */
	dev_info(&dev->dev, "device Vendor:%04x Product:%04x is not supported\n",
		 le16_to_cpu(dev->descriptor.idVendor),
		 le16_to_cpu(dev->descriptor.idProduct));
        if (USB_CLASS_HUB == dev->descriptor.bDeviceClass){
                dev_printk(KERN_CRIT, &dev->dev, "Unsupported Hub Topology\n");
        } else {
                dev_printk(KERN_CRIT, &dev->dev, "Attached Device is not Supported\n");
        }
}