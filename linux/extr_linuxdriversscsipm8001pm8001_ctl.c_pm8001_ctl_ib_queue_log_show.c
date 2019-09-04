#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct TYPE_4__ {TYPE_1__* region; } ;
struct pm8001_hba_info {int evtlog_ib_offset; TYPE_2__ memoryMap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ virt_ptr; } ;

/* Variables and functions */
 size_t IB ; 
 int IB_OB_READ_TIMES ; 
 int PM80XX_IB_OB_QUEUE_SIZE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 scalar_t__ SYSFS_OFFSET ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pm8001_ctl_ib_queue_log_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	int offset;
	char *str = buf;
	int start = 0;
#define IB_MEMMAP(c)	\
		(*(u32 *)((u8 *)pm8001_ha->	\
		memoryMap.region[IB].virt_ptr +	\
		pm8001_ha->evtlog_ib_offset + (c)))

	for (offset = 0; offset < IB_OB_READ_TIMES; offset++) {
		str += sprintf(str, "0x%08x\n", IB_MEMMAP(start));
		start = start + 4;
	}
	pm8001_ha->evtlog_ib_offset += SYSFS_OFFSET;
	if (((pm8001_ha->evtlog_ib_offset) % (PM80XX_IB_OB_QUEUE_SIZE)) == 0)
		pm8001_ha->evtlog_ib_offset = 0;

	return str - buf;
}