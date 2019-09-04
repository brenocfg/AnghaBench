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
struct TYPE_2__ {int bNumConfigurations; } ;
struct usb_device {scalar_t__ config; scalar_t__ actconfig; int /*<<< orphan*/  speed; TYPE_1__ descriptor; } ;

/* Variables and functions */
 char* usb_dump_config (int /*<<< orphan*/ ,char*,char*,scalar_t__,int) ; 
 char* usb_dump_device_descriptor (char*,char*,TYPE_1__*) ; 
 char* usb_dump_device_strings (char*,char*,struct usb_device*) ; 

__attribute__((used)) static char *usb_dump_desc(char *start, char *end, struct usb_device *dev)
{
	int i;

	if (start > end)
		return start;

	start = usb_dump_device_descriptor(start, end, &dev->descriptor);

	if (start > end)
		return start;

	start = usb_dump_device_strings(start, end, dev);

	for (i = 0; i < dev->descriptor.bNumConfigurations; i++) {
		if (start > end)
			return start;
		start = usb_dump_config(dev->speed,
				start, end, dev->config + i,
				/* active ? */
				(dev->config + i) == dev->actconfig);
	}
	return start;
}