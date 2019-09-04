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
struct scsi_qla_host {int fw_uptime_secs; int fw_uptime_msecs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  qla4xxx_about_firmware (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 
 struct scsi_qla_host* to_qla_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla4xxx_fw_uptime_show(struct device *dev, struct device_attribute *attr,
		       char *buf)
{
	struct scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	qla4xxx_about_firmware(ha);
	return snprintf(buf, PAGE_SIZE, "%u.%u secs\n", ha->fw_uptime_secs,
			ha->fw_uptime_msecs);
}