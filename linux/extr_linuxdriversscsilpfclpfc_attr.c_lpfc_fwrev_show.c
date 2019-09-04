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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct TYPE_3__ {int if_type; int sli_family; } ;
struct TYPE_4__ {TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_2__ sli4_hba; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int FW_REV_STR_SIZE ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  lpfc_decode_firmware_rev (struct lpfc_hba*,char*,int) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,...) ; 

__attribute__((used)) static ssize_t
lpfc_fwrev_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	uint32_t if_type;
	uint8_t sli_family;
	char fwrev[FW_REV_STR_SIZE];
	int len;

	lpfc_decode_firmware_rev(phba, fwrev, 1);
	if_type = phba->sli4_hba.pc_sli4_params.if_type;
	sli_family = phba->sli4_hba.pc_sli4_params.sli_family;

	if (phba->sli_rev < LPFC_SLI_REV4)
		len = snprintf(buf, PAGE_SIZE, "%s, sli-%d\n",
			       fwrev, phba->sli_rev);
	else
		len = snprintf(buf, PAGE_SIZE, "%s, sli-%d:%d:%x\n",
			       fwrev, phba->sli_rev, if_type, sli_family);

	return len;
}