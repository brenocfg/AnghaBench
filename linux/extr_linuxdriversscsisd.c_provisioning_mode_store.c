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
struct scsi_device {scalar_t__ type; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 size_t EINVAL ; 
 int SD_LBP_DISABLE ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbp_mode ; 
 int /*<<< orphan*/  sd_config_discard (struct scsi_disk*,int) ; 
 scalar_t__ sd_is_zoned (struct scsi_disk*) ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
provisioning_mode_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	struct scsi_device *sdp = sdkp->device;
	int mode;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (sd_is_zoned(sdkp)) {
		sd_config_discard(sdkp, SD_LBP_DISABLE);
		return count;
	}

	if (sdp->type != TYPE_DISK)
		return -EINVAL;

	mode = sysfs_match_string(lbp_mode, buf);
	if (mode < 0)
		return -EINVAL;

	sd_config_discard(sdkp, mode);

	return count;
}