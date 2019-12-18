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
struct usbentry {void* product_id; void* vendor_id; void* dev_num; void* bus_num; int /*<<< orphan*/  product_name; int /*<<< orphan*/  vendor_name; } ;
struct dirent {int /*<<< orphan*/ * d_name; } ;
typedef  int /*<<< orphan*/  dev ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct usbentry*,int /*<<< orphan*/ ,int) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int) ; 
 char* sysfs_attr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct usbentry * parse_devlist(DIR *d)
{
	char *attr;
	struct dirent *e;
	static struct usbentry dev;

	do {
		e = readdir(d);

		if (!e)
			return NULL;
	}
	while(!isdigit(e->d_name[0]) || strchr(e->d_name, ':'));

	memset(&dev, 0, sizeof(dev));

	if ((attr = sysfs_attr(e->d_name, "busnum")) != NULL)
		dev.bus_num = strtoul(attr, NULL, 10);

	if ((attr = sysfs_attr(e->d_name, "devnum")) != NULL)
		dev.dev_num = strtoul(attr, NULL, 10);

	if ((attr = sysfs_attr(e->d_name, "idVendor")) != NULL)
		dev.vendor_id = strtoul(attr, NULL, 16);

	if ((attr = sysfs_attr(e->d_name, "idProduct")) != NULL)
		dev.product_id = strtoul(attr, NULL, 16);

	if ((attr = sysfs_attr(e->d_name, "manufacturer")) != NULL)
		strcpy(dev.vendor_name, attr);

	if ((attr = sysfs_attr(e->d_name, "product")) != NULL)
		strcpy(dev.product_name, attr);

	if (dev.bus_num && dev.dev_num && dev.vendor_id && dev.product_id)
		return &dev;

	return NULL;
}