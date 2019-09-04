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
struct scsi_disk {int RCD; int WCE; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** sd_cache_types ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
cache_type_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);
	int ct = sdkp->RCD + 2*sdkp->WCE;

	return sprintf(buf, "%s\n", sd_cache_types[ct]);
}