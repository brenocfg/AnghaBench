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
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_urbs ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_to_dummy_hcd (struct usb_hcd*) ; 

__attribute__((used)) static void dummy_stop(struct usb_hcd *hcd)
{
	device_remove_file(dummy_dev(hcd_to_dummy_hcd(hcd)), &dev_attr_urbs);
	dev_info(dummy_dev(hcd_to_dummy_hcd(hcd)), "stopped\n");
}