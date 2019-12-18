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
struct TYPE_2__ {int busid; char* path; } ;
struct usbip_exported_device {int status; TYPE_1__ udev; } ;
typedef  int /*<<< orphan*/  sockfd_buff ;
typedef  int /*<<< orphan*/  sockfd_attr_path ;

/* Variables and functions */
 int SDEV_ST_AVAILABLE ; 
#define  SDEV_ST_ERROR 129 
#define  SDEV_ST_USED 128 
 int ST_DEV_BUSY ; 
 int ST_DEV_ERR ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,int) ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write_sysfs_attribute (char*,char*,int /*<<< orphan*/ ) ; 

int usbip_export_device(struct usbip_exported_device *edev, int sockfd)
{
	char attr_name[] = "usbip_sockfd";
	char sockfd_attr_path[SYSFS_PATH_MAX];
	int size;
	char sockfd_buff[30];
	int ret;

	if (edev->status != SDEV_ST_AVAILABLE) {
		dbg("device not available: %s", edev->udev.busid);
		switch (edev->status) {
		case SDEV_ST_ERROR:
			dbg("status SDEV_ST_ERROR");
			ret = ST_DEV_ERR;
			break;
		case SDEV_ST_USED:
			dbg("status SDEV_ST_USED");
			ret = ST_DEV_BUSY;
			break;
		default:
			dbg("status unknown: 0x%x", edev->status);
			ret = -1;
		}
		return ret;
	}

	/* only the first interface is true */
	size = snprintf(sockfd_attr_path, sizeof(sockfd_attr_path), "%s/%s",
			edev->udev.path, attr_name);
	if (size < 0 || (unsigned int)size >= sizeof(sockfd_attr_path)) {
		err("exported device path length %i >= %lu or < 0", size,
		    (long unsigned)sizeof(sockfd_attr_path));
		return -1;
	}

	size = snprintf(sockfd_buff, sizeof(sockfd_buff), "%d\n", sockfd);
	if (size < 0 || (unsigned int)size >= sizeof(sockfd_buff)) {
		err("socket length %i >= %lu or < 0", size,
		    (long unsigned)sizeof(sockfd_buff));
		return -1;
	}

	ret = write_sysfs_attribute(sockfd_attr_path, sockfd_buff,
				    strlen(sockfd_buff));
	if (ret < 0) {
		err("write_sysfs_attribute failed: sockfd %s to %s",
		    sockfd_buff, sockfd_attr_path);
		return ret;
	}

	info("connect: %s", edev->udev.busid);

	return ret;
}