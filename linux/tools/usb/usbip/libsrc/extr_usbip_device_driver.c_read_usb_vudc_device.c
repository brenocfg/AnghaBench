#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbip_usb_device {char* path; char* busid; scalar_t__ busnum; scalar_t__ bConfigurationValue; scalar_t__ bNumInterfaces; int /*<<< orphan*/  speed; } ;
struct usb_device_descriptor {int dummy; } ;
struct udev_device {int dummy; } ;
typedef  int /*<<< orphan*/  descr ;
struct TYPE_3__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int SYSFS_BUS_ID_SIZE ; 
 int SYSFS_PATH_MAX ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 char* VUDC_DEVICE_DESCR_FILE ; 
 int /*<<< orphan*/  bDeviceClass ; 
 int /*<<< orphan*/  bDeviceProtocol ; 
 int /*<<< orphan*/  bDeviceSubClass ; 
 int /*<<< orphan*/  bNumConfigurations ; 
 int /*<<< orphan*/  bcdDevice ; 
 int /*<<< orphan*/  copy_descr_attr (struct usbip_usb_device*,struct usb_device_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_descr_attr16 (struct usbip_usb_device*,struct usb_device_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idProduct ; 
 int /*<<< orphan*/  idVendor ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 TYPE_1__* speed_names ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 struct udev_device* udev_device_get_parent (struct udev_device*) ; 
 char* udev_device_get_sysattr_value (struct udev_device*,char*) ; 
 char* udev_device_get_sysname (struct udev_device*) ; 
 char* udev_device_get_syspath (struct udev_device*) ; 

__attribute__((used)) static
int read_usb_vudc_device(struct udev_device *sdev, struct usbip_usb_device *dev)
{
	const char *path, *name;
	char filepath[SYSFS_PATH_MAX];
	struct usb_device_descriptor descr;
	unsigned int i;
	FILE *fd = NULL;
	struct udev_device *plat;
	const char *speed;
	size_t ret;

	plat = udev_device_get_parent(sdev);
	path = udev_device_get_syspath(plat);
	snprintf(filepath, SYSFS_PATH_MAX, "%s/%s",
		 path, VUDC_DEVICE_DESCR_FILE);
	fd = fopen(filepath, "r");
	if (!fd)
		return -1;
	ret = fread((char *) &descr, sizeof(descr), 1, fd);
	if (ret != 1) {
		err("Cannot read vudc device descr file: %s", strerror(errno));
		goto err;
	}
	fclose(fd);

	copy_descr_attr(dev, &descr, bDeviceClass);
	copy_descr_attr(dev, &descr, bDeviceSubClass);
	copy_descr_attr(dev, &descr, bDeviceProtocol);
	copy_descr_attr(dev, &descr, bNumConfigurations);
	copy_descr_attr16(dev, &descr, idVendor);
	copy_descr_attr16(dev, &descr, idProduct);
	copy_descr_attr16(dev, &descr, bcdDevice);

	strncpy(dev->path, path, SYSFS_PATH_MAX - 1);
	dev->path[SYSFS_PATH_MAX - 1] = '\0';

	dev->speed = USB_SPEED_UNKNOWN;
	speed = udev_device_get_sysattr_value(sdev, "current_speed");
	if (speed) {
		for (i = 0; i < ARRAY_SIZE(speed_names); i++) {
			if (!strcmp(speed_names[i].name, speed)) {
				dev->speed = speed_names[i].speed;
				break;
			}
		}
	}

	/* Only used for user output, little sense to output them in general */
	dev->bNumInterfaces = 0;
	dev->bConfigurationValue = 0;
	dev->busnum = 0;

	name = udev_device_get_sysname(plat);
	strncpy(dev->busid, name, SYSFS_BUS_ID_SIZE - 1);
	dev->busid[SYSFS_BUS_ID_SIZE - 1] = '\0';
	return 0;
err:
	fclose(fd);
	return -1;
}