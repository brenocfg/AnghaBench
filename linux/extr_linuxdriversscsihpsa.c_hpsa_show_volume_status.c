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
struct hpsa_scsi_dev_t {int volume_offline; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct ctlr_info {TYPE_2__* scsi_host; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER 139 
#define  HPSA_LV_ENCRYPTED_NO_KEY 138 
#define  HPSA_LV_NOT_AVAILABLE 137 
#define  HPSA_LV_OK 136 
#define  HPSA_LV_PENDING_ENCRYPTION 135 
#define  HPSA_LV_PENDING_ENCRYPTION_REKEYING 134 
#define  HPSA_LV_PENDING_RPI 133 
#define  HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER 132 
#define  HPSA_LV_UNDERGOING_ENCRYPTION 131 
#define  HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING 130 
#define  HPSA_LV_UNDERGOING_ERASE 129 
#define  HPSA_LV_UNDERGOING_RPI 128 
 int HPSA_VPD_LV_STATUS_UNSUPPORTED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_show_volume_status(struct ctlr_info *h,
	struct hpsa_scsi_dev_t *sd)
{
	if (sd->volume_offline == HPSA_VPD_LV_STATUS_UNSUPPORTED)
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume status is not available through vital product data pages.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
	switch (sd->volume_offline) {
	case HPSA_LV_OK:
		break;
	case HPSA_LV_UNDERGOING_ERASE:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing background erase process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_NOT_AVAILABLE:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is waiting for transforming volume.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_UNDERGOING_RPI:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing rapid parity init.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_PENDING_RPI:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is queued for rapid parity initialization process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_ENCRYPTED_NO_KEY:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is encrypted and cannot be accessed because key is not present.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_PLAINTEXT_IN_ENCRYPT_ONLY_CONTROLLER:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is not encrypted and cannot be accessed because controller is in encryption-only mode.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_UNDERGOING_ENCRYPTION:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing encryption process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_UNDERGOING_ENCRYPTION_REKEYING:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is undergoing encryption re-keying process.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is encrypted and cannot be accessed because controller does not have encryption enabled.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_PENDING_ENCRYPTION:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is pending migration to encrypted state, but process has not started.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	case HPSA_LV_PENDING_ENCRYPTION_REKEYING:
		dev_info(&h->pdev->dev,
			"C%d:B%d:T%d:L%d Volume is encrypted and is pending encryption rekeying.\n",
			h->scsi_host->host_no,
			sd->bus, sd->target, sd->lun);
		break;
	}
}