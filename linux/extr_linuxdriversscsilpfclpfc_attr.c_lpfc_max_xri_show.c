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
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 scalar_t__ lpfc_get_hba_info (struct lpfc_hba*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t
lpfc_max_xri_show(struct device *dev, struct device_attribute *attr,
		  char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	uint32_t cnt;

	if (lpfc_get_hba_info(phba, &cnt, NULL, NULL, NULL, NULL, NULL))
		return snprintf(buf, PAGE_SIZE, "%d\n", cnt);
	return snprintf(buf, PAGE_SIZE, "Unknown\n");
}