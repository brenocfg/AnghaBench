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
struct TYPE_2__ {scalar_t__ bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct usb_host_interface {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_MASS_STORAGE ; 
 scalar_t__ USB_PR_UAS ; 
 scalar_t__ USB_SC_SCSI ; 

__attribute__((used)) static int uas_is_interface(struct usb_host_interface *intf)
{
	return (intf->desc.bInterfaceClass == USB_CLASS_MASS_STORAGE &&
		intf->desc.bInterfaceSubClass == USB_SC_SCSI &&
		intf->desc.bInterfaceProtocol == USB_PR_UAS);
}