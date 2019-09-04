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
struct scsi_disk {struct scsi_device* device; } ;
struct scsi_device {int manage_start_stop; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtobool (char const*,int*) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
manage_start_stop_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;
	bool v;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (kstrtobool(buf, &v))
		return -EINVAL;

	sdp->manage_start_stop = v;

	return count;
}