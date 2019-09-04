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
struct kernfs_node {int dummy; } ;
struct device_attribute {int /*<<< orphan*/  attr; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,struct device_attribute*) ; 
 int /*<<< orphan*/  scsi_remove_device (int /*<<< orphan*/ ) ; 
 struct kernfs_node* sysfs_break_active_protection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_unbreak_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_store_delete(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	struct kernfs_node *kn;

	kn = sysfs_break_active_protection(&dev->kobj, &attr->attr);
	WARN_ON_ONCE(!kn);
	/*
	 * Concurrent writes into the "delete" sysfs attribute may trigger
	 * concurrent calls to device_remove_file() and scsi_remove_device().
	 * device_remove_file() handles concurrent removal calls by
	 * serializing these and by ignoring the second and later removal
	 * attempts.  Concurrent calls of scsi_remove_device() are
	 * serialized. The second and later calls of scsi_remove_device() are
	 * ignored because the first call of that function changes the device
	 * state into SDEV_DEL.
	 */
	device_remove_file(dev, attr);
	scsi_remove_device(to_scsi_device(dev));
	if (kn)
		sysfs_unbreak_active_protection(kn);
	return count;
}