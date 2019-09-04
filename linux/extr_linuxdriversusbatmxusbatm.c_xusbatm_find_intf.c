#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct usb_interface {int dummy; } ;
struct TYPE_6__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_1__ desc; } ;
struct usb_device {TYPE_5__* actconfig; } ;
struct TYPE_9__ {int bNumInterfaces; } ;
struct TYPE_10__ {struct usb_interface** interface; TYPE_4__ desc; } ;
struct TYPE_7__ {scalar_t__ bEndpointAddress; } ;
struct TYPE_8__ {TYPE_2__ desc; } ;

/* Variables and functions */
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int) ; 

__attribute__((used)) static struct usb_interface *xusbatm_find_intf(struct usb_device *usb_dev, int altsetting, u8 ep)
{
	struct usb_host_interface *alt;
	struct usb_interface *intf;
	int i, j;

	for (i = 0; i < usb_dev->actconfig->desc.bNumInterfaces; i++)
		if ((intf = usb_dev->actconfig->interface[i]) && (alt = usb_altnum_to_altsetting(intf, altsetting)))
			for (j = 0; j < alt->desc.bNumEndpoints; j++)
				if (alt->endpoint[j].desc.bEndpointAddress == ep)
					return intf;
	return NULL;
}