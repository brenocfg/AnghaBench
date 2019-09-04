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
struct scsi_device {unsigned int eh_timeout; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_store_eh_timeout(struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t count)
{
	struct scsi_device *sdev;
	unsigned int eh_timeout;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	sdev = to_scsi_device(dev);
	err = kstrtouint(buf, 10, &eh_timeout);
	if (err)
		return err;
	sdev->eh_timeout = eh_timeout * HZ;

	return count;
}