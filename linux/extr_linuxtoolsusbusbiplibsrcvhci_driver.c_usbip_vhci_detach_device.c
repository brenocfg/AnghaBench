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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  detach_attr_path ;
typedef  int /*<<< orphan*/  buff ;
struct TYPE_2__ {int /*<<< orphan*/  hc_device; } ;

/* Variables and functions */
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* udev_device_get_syspath (int /*<<< orphan*/ ) ; 
 TYPE_1__* vhci_driver ; 
 int write_sysfs_attribute (char*,char*,int /*<<< orphan*/ ) ; 

int usbip_vhci_detach_device(uint8_t port)
{
	char detach_attr_path[SYSFS_PATH_MAX];
	char attr_detach[] = "detach";
	char buff[200]; /* what size should be ? */
	const char *path;
	int ret;

	snprintf(buff, sizeof(buff), "%u", port);
	dbg("writing: %s", buff);

	path = udev_device_get_syspath(vhci_driver->hc_device);
	snprintf(detach_attr_path, sizeof(detach_attr_path), "%s/%s",
		 path, attr_detach);
	dbg("detach attribute path: %s", detach_attr_path);

	ret = write_sysfs_attribute(detach_attr_path, buff, strlen(buff));
	if (ret < 0) {
		dbg("write_sysfs_attribute failed");
		return -1;
	}

	dbg("detached port: %d", port);

	return 0;
}