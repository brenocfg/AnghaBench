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
struct twl6030_usb {int vbus_enable; int /*<<< orphan*/  set_vbus_work; } ;
struct phy_companion {int dummy; } ;

/* Variables and functions */
 struct twl6030_usb* comparator_to_twl (struct phy_companion*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int twl6030_set_vbus(struct phy_companion *comparator, bool enabled)
{
	struct twl6030_usb *twl = comparator_to_twl(comparator);

	twl->vbus_enable = enabled;
	schedule_work(&twl->set_vbus_work);

	return 0;
}