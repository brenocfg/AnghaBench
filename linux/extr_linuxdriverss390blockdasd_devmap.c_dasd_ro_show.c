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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dasd_devmap {int features; struct dasd_device* device; } ;
struct dasd_device {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DASD_FEATURE_READONLY ; 
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 scalar_t__ IS_ERR (struct dasd_devmap*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dasd_devmap_lock ; 
 struct dasd_devmap* dasd_find_busid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
dasd_ro_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct dasd_devmap *devmap;
	struct dasd_device *device;
	int ro_flag = 0;

	devmap = dasd_find_busid(dev_name(dev));
	if (IS_ERR(devmap))
		goto out;

	ro_flag = !!(devmap->features & DASD_FEATURE_READONLY);

	spin_lock(&dasd_devmap_lock);
	device = devmap->device;
	if (device)
		ro_flag |= test_bit(DASD_FLAG_DEVICE_RO, &device->flags);
	spin_unlock(&dasd_devmap_lock);

out:
	return snprintf(buf, PAGE_SIZE, ro_flag ? "1\n" : "0\n");
}