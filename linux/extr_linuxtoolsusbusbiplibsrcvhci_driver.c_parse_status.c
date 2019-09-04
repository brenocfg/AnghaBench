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
struct usbip_imported_device {int port; int status; int devid; int busnum; int devnum; int /*<<< orphan*/  hub; } ;
struct TYPE_2__ {struct usbip_imported_device* idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  HUB_SPEED_HIGH ; 
 int /*<<< orphan*/  HUB_SPEED_SUPER ; 
 int SYSFS_BUS_ID_SIZE ; 
 int VDEV_ST_NOTASSIGNED ; 
 int VDEV_ST_NULL ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 struct usbip_imported_device* imported_device_init (struct usbip_imported_device*,char*) ; 
 int /*<<< orphan*/  memset (struct usbip_imported_device*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,char*,int*,int*,int*,int*,int*,char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_1__* vhci_driver ; 

__attribute__((used)) static int parse_status(const char *value)
{
	int ret = 0;
	char *c;

	/* skip a header line */
	c = strchr(value, '\n');
	if (!c)
		return -1;
	c++;

	while (*c != '\0') {
		int port, status, speed, devid;
		int sockfd;
		char lbusid[SYSFS_BUS_ID_SIZE];
		struct usbip_imported_device *idev;
		char hub[3];

		ret = sscanf(c, "%2s  %d %d %d %x %u %31s\n",
				hub, &port, &status, &speed,
				&devid, &sockfd, lbusid);

		if (ret < 5) {
			dbg("sscanf failed: %d", ret);
			BUG();
		}

		dbg("hub %s port %d status %d speed %d devid %x",
				hub, port, status, speed, devid);
		dbg("sockfd %u lbusid %s", sockfd, lbusid);

		/* if a device is connected, look at it */
		idev = &vhci_driver->idev[port];
		memset(idev, 0, sizeof(*idev));

		if (strncmp("hs", hub, 2) == 0)
			idev->hub = HUB_SPEED_HIGH;
		else /* strncmp("ss", hub, 2) == 0 */
			idev->hub = HUB_SPEED_SUPER;

		idev->port	= port;
		idev->status	= status;

		idev->devid	= devid;

		idev->busnum	= (devid >> 16);
		idev->devnum	= (devid & 0x0000ffff);

		if (idev->status != VDEV_ST_NULL
		    && idev->status != VDEV_ST_NOTASSIGNED) {
			idev = imported_device_init(idev, lbusid);
			if (!idev) {
				dbg("imported_device_init failed");
				return -1;
			}
		}

		/* go to the next line */
		c = strchr(c, '\n');
		if (!c)
			break;
		c++;
	}

	dbg("exit");

	return 0;
}