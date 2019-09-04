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
struct scsi_disk {int /*<<< orphan*/  max_medium_access_timeouts; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int kstrtouint (char const*,int,int /*<<< orphan*/ *) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
max_medium_access_timeouts_store(struct device *dev,
				 struct device_attribute *attr, const char *buf,
				 size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	err = kstrtouint(buf, 10, &sdkp->max_medium_access_timeouts);

	return err ? err : count;
}