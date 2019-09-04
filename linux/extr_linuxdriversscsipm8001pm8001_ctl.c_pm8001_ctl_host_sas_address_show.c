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
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {scalar_t__ sas_addr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pm8001_ctl_host_sas_address_show(struct device *cdev,
	struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	return snprintf(buf, PAGE_SIZE, "0x%016llx\n",
			be64_to_cpu(*(__be64 *)pm8001_ha->sas_addr));
}