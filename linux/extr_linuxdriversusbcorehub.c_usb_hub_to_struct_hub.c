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
struct usb_hub {int dummy; } ;
struct usb_device {TYPE_1__* actconfig; int /*<<< orphan*/  maxchild; } ;
struct TYPE_2__ {int /*<<< orphan*/ * interface; } ;

/* Variables and functions */
 struct usb_hub* usb_get_intfdata (int /*<<< orphan*/ ) ; 

struct usb_hub *usb_hub_to_struct_hub(struct usb_device *hdev)
{
	if (!hdev || !hdev->actconfig || !hdev->maxchild)
		return NULL;
	return usb_get_intfdata(hdev->actconfig->interface[0]);
}