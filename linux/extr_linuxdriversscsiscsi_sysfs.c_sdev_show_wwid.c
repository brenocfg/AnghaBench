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
struct scsi_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t scsi_vpd_lun_id (struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
sdev_show_wwid(struct device *dev, struct device_attribute *attr,
		    char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	ssize_t count;

	count = scsi_vpd_lun_id(sdev, buf, PAGE_SIZE);
	if (count > 0) {
		buf[count] = '\n';
		count++;
	}
	return count;
}