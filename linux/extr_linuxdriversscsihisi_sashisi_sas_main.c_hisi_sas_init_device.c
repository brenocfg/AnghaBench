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
struct scsi_lun {int /*<<< orphan*/  scsi_lun; } ;
struct hisi_sas_tmf_task {int /*<<< orphan*/  tmf; } ;
struct hisi_hba {int dummy; } ;
struct domain_device {int dev_type; } ;

/* Variables and functions */
 int HISI_SAS_SRST_ATA_DISK_CNT ; 
#define  SAS_END_DEVICE 132 
#define  SAS_SATA_DEV 131 
#define  SAS_SATA_PENDING 130 
#define  SAS_SATA_PM 129 
#define  SAS_SATA_PM_PORT 128 
 int /*<<< orphan*/  TMF_CLEAR_TASK_SET ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 struct hisi_hba* dev_to_hisi_hba (struct domain_device*) ; 
 int hisi_sas_debug_issue_ssp_tmf (struct domain_device*,int /*<<< orphan*/ ,struct hisi_sas_tmf_task*) ; 
 int /*<<< orphan*/  hisi_sas_release_task (struct hisi_hba*,struct domain_device*) ; 
 int hisi_sas_softreset_ata_disk (struct domain_device*) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 

__attribute__((used)) static int hisi_sas_init_device(struct domain_device *device)
{
	int rc = TMF_RESP_FUNC_COMPLETE;
	struct scsi_lun lun;
	struct hisi_sas_tmf_task tmf_task;
	int retry = HISI_SAS_SRST_ATA_DISK_CNT;
	struct hisi_hba *hisi_hba = dev_to_hisi_hba(device);

	switch (device->dev_type) {
	case SAS_END_DEVICE:
		int_to_scsilun(0, &lun);

		tmf_task.tmf = TMF_CLEAR_TASK_SET;
		rc = hisi_sas_debug_issue_ssp_tmf(device, lun.scsi_lun,
						  &tmf_task);
		if (rc == TMF_RESP_FUNC_COMPLETE)
			hisi_sas_release_task(hisi_hba, device);
		break;
	case SAS_SATA_DEV:
	case SAS_SATA_PM:
	case SAS_SATA_PM_PORT:
	case SAS_SATA_PENDING:
		while (retry-- > 0) {
			rc = hisi_sas_softreset_ata_disk(device);
			if (!rc)
				break;
		}
		break;
	default:
		break;
	}

	return rc;
}