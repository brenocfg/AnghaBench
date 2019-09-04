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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_usb_device (struct device*) ; 
 scalar_t__ is_usb_port (struct device*) ; 

__attribute__((used)) static bool usb_acpi_bus_match(struct device *dev)
{
	return is_usb_device(dev) || is_usb_port(dev);
}