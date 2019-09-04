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
typedef  int /*<<< orphan*/  unknown_state_str ;
typedef  int /*<<< orphan*/  unknown_state_buffer ;
struct pqi_scsi_dev {int volume_status; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct pqi_ctrl_info {TYPE_2__* scsi_host; TYPE_1__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CISS_LV_DEGRADED 154 
#define  CISS_LV_DISABLED_SCSI_ID_CONFLICT 153 
#define  CISS_LV_EJECTED 152 
#define  CISS_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER 151 
#define  CISS_LV_ENCRYPTED_NO_KEY 150 
#define  CISS_LV_FAILED 149 
#define  CISS_LV_HARDWARE_HAS_OVERHEATED 148 
#define  CISS_LV_HARDWARE_OVERHEATING 147 
#define  CISS_LV_NOT_AVAILABLE 146 
#define  CISS_LV_NOT_CONFIGURED 145 
#define  CISS_LV_NOT_SUPPORTED 144 
#define  CISS_LV_OK 143 
#define  CISS_LV_PENDING_ENCRYPTION 142 
#define  CISS_LV_PENDING_ENCRYPTION_REKEYING 141 
#define  CISS_LV_PENDING_RPI 140 
#define  CISS_LV_PHYSICAL_DRIVE_CONNECTION_PROBLEM 139 
#define  CISS_LV_QUEUED_FOR_EXPANSION 138 
#define  CISS_LV_READY_FOR_PREDICTIVE_SPARE_REBUILD 137 
#define  CISS_LV_READY_FOR_RECOVERY 136 
#define  CISS_LV_STATUS_UNAVAILABLE 135 
#define  CISS_LV_UNDERGOING_ENCRYPTION 134 
#define  CISS_LV_UNDERGOING_ENCRYPTION_REKEYING 133 
#define  CISS_LV_UNDERGOING_ERASE 132 
#define  CISS_LV_UNDERGOING_EXPANSION 131 
#define  CISS_LV_UNDERGOING_RECOVERY 130 
#define  CISS_LV_UNDERGOING_RPI 129 
#define  CISS_LV_WRONG_PHYSICAL_DRIVE_REPLACED 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int) ; 

__attribute__((used)) static void pqi_show_volume_status(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	char *status;
	static const char unknown_state_str[] =
		"Volume is in an unknown state (%u)";
	char unknown_state_buffer[sizeof(unknown_state_str) + 10];

	switch (device->volume_status) {
	case CISS_LV_OK:
		status = "Volume online";
		break;
	case CISS_LV_FAILED:
		status = "Volume failed";
		break;
	case CISS_LV_NOT_CONFIGURED:
		status = "Volume not configured";
		break;
	case CISS_LV_DEGRADED:
		status = "Volume degraded";
		break;
	case CISS_LV_READY_FOR_RECOVERY:
		status = "Volume ready for recovery operation";
		break;
	case CISS_LV_UNDERGOING_RECOVERY:
		status = "Volume undergoing recovery";
		break;
	case CISS_LV_WRONG_PHYSICAL_DRIVE_REPLACED:
		status = "Wrong physical drive was replaced";
		break;
	case CISS_LV_PHYSICAL_DRIVE_CONNECTION_PROBLEM:
		status = "A physical drive not properly connected";
		break;
	case CISS_LV_HARDWARE_OVERHEATING:
		status = "Hardware is overheating";
		break;
	case CISS_LV_HARDWARE_HAS_OVERHEATED:
		status = "Hardware has overheated";
		break;
	case CISS_LV_UNDERGOING_EXPANSION:
		status = "Volume undergoing expansion";
		break;
	case CISS_LV_NOT_AVAILABLE:
		status = "Volume waiting for transforming volume";
		break;
	case CISS_LV_QUEUED_FOR_EXPANSION:
		status = "Volume queued for expansion";
		break;
	case CISS_LV_DISABLED_SCSI_ID_CONFLICT:
		status = "Volume disabled due to SCSI ID conflict";
		break;
	case CISS_LV_EJECTED:
		status = "Volume has been ejected";
		break;
	case CISS_LV_UNDERGOING_ERASE:
		status = "Volume undergoing background erase";
		break;
	case CISS_LV_READY_FOR_PREDICTIVE_SPARE_REBUILD:
		status = "Volume ready for predictive spare rebuild";
		break;
	case CISS_LV_UNDERGOING_RPI:
		status = "Volume undergoing rapid parity initialization";
		break;
	case CISS_LV_PENDING_RPI:
		status = "Volume queued for rapid parity initialization";
		break;
	case CISS_LV_ENCRYPTED_NO_KEY:
		status = "Encrypted volume inaccessible - key not present";
		break;
	case CISS_LV_UNDERGOING_ENCRYPTION:
		status = "Volume undergoing encryption process";
		break;
	case CISS_LV_UNDERGOING_ENCRYPTION_REKEYING:
		status = "Volume undergoing encryption re-keying process";
		break;
	case CISS_LV_ENCRYPTED_IN_NON_ENCRYPTED_CONTROLLER:
		status = "Volume encrypted but encryption is disabled";
		break;
	case CISS_LV_PENDING_ENCRYPTION:
		status = "Volume pending migration to encrypted state";
		break;
	case CISS_LV_PENDING_ENCRYPTION_REKEYING:
		status = "Volume pending encryption rekeying";
		break;
	case CISS_LV_NOT_SUPPORTED:
		status = "Volume not supported on this controller";
		break;
	case CISS_LV_STATUS_UNAVAILABLE:
		status = "Volume status not available";
		break;
	default:
		snprintf(unknown_state_buffer, sizeof(unknown_state_buffer),
			unknown_state_str, device->volume_status);
		status = unknown_state_buffer;
		break;
	}

	dev_info(&ctrl_info->pci_dev->dev,
		"scsi %d:%d:%d:%d %s\n",
		ctrl_info->scsi_host->host_no,
		device->bus, device->target, device->lun, status);
}