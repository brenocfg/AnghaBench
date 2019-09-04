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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  attach_attr_path ;
struct TYPE_2__ {int /*<<< orphan*/  hc_device; } ;

/* Variables and functions */
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* udev_device_get_syspath (int /*<<< orphan*/ ) ; 
 TYPE_1__* vhci_driver ; 
 int write_sysfs_attribute (char*,char*,int /*<<< orphan*/ ) ; 

int usbip_vhci_attach_device2(uint8_t port, int sockfd, uint32_t devid,
		uint32_t speed) {
	char buff[200]; /* what size should be ? */
	char attach_attr_path[SYSFS_PATH_MAX];
	char attr_attach[] = "attach";
	const char *path;
	int ret;

	snprintf(buff, sizeof(buff), "%u %d %u %u",
			port, sockfd, devid, speed);
	dbg("writing: %s", buff);

	path = udev_device_get_syspath(vhci_driver->hc_device);
	snprintf(attach_attr_path, sizeof(attach_attr_path), "%s/%s",
		 path, attr_attach);
	dbg("attach attribute path: %s", attach_attr_path);

	ret = write_sysfs_attribute(attach_attr_path, buff, strlen(buff));
	if (ret < 0) {
		dbg("write_sysfs_attribute failed");
		return -1;
	}

	dbg("attached port: %d", port);

	return 0;
}