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
struct udev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 char* udev_device_get_sysattr_value (struct udev_device*,char*) ; 

__attribute__((used)) static int get_nports(struct udev_device *hc_device)
{
	const char *attr_nports;

	attr_nports = udev_device_get_sysattr_value(hc_device, "nports");
	if (!attr_nports) {
		err("udev_device_get_sysattr_value nports failed");
		return -1;
	}

	return (int)strtoul(attr_nports, NULL, 10);
}