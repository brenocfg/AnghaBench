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
struct usb_bus {unsigned int resuming_ports; TYPE_1__* root_hub; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 

void usb_hcd_start_port_resume(struct usb_bus *bus, int portnum)
{
	unsigned bit = 1 << portnum;

	if (!(bus->resuming_ports & bit)) {
		bus->resuming_ports |= bit;
		pm_runtime_get_noresume(&bus->root_hub->dev);
	}
}