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
struct renesas_usb3 {int dummy; } ;
struct device {int dummy; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int USB_ROLE_DEVICE ; 
 int USB_ROLE_HOST ; 
 struct renesas_usb3* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 scalar_t__ usb3_is_host (struct renesas_usb3*) ; 

__attribute__((used)) static enum usb_role renesas_usb3_role_switch_get(struct device *dev)
{
	struct renesas_usb3 *usb3 = dev_get_drvdata(dev);
	enum usb_role cur_role;

	pm_runtime_get_sync(dev);
	cur_role = usb3_is_host(usb3) ? USB_ROLE_HOST : USB_ROLE_DEVICE;
	pm_runtime_put(dev);

	return cur_role;
}