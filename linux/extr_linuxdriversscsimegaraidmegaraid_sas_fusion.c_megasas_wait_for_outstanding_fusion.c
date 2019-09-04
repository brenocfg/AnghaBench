#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct megasas_instance {TYPE_5__* host; TYPE_4__* pdev; int /*<<< orphan*/  fw_outstanding; TYPE_3__* hb_host_mem; scalar_t__ requestorId; int /*<<< orphan*/  reg_set; TYPE_1__* instancet; } ;
struct TYPE_10__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ fwCounter; scalar_t__ driverCounter; } ;
struct TYPE_8__ {TYPE_2__ HB; } ;
struct TYPE_6__ {int (* read_fw_status_reg ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HZ ; 
 int MEGASAS_RESET_NOTICE_INTERVAL ; 
 int MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF ; 
 int MFI_IO_TIMEOUT_OCR ; 
 int MFI_STATE_FAULT ; 
 int MFI_STATE_MASK ; 
 int SCSIIO_TIMEOUT_OCR ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_complete_cmd_dpc_fusion (unsigned long) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int resetwaittime ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int megasas_wait_for_outstanding_fusion(struct megasas_instance *instance,
					int reason, int *convert)
{
	int i, outstanding, retval = 0, hb_seconds_missed = 0;
	u32 fw_state;

	for (i = 0; i < resetwaittime; i++) {
		/* Check if firmware is in fault state */
		fw_state = instance->instancet->read_fw_status_reg(
			instance->reg_set) & MFI_STATE_MASK;
		if (fw_state == MFI_STATE_FAULT) {
			dev_warn(&instance->pdev->dev, "Found FW in FAULT state,"
			       " will reset adapter scsi%d.\n",
				instance->host->host_no);
			megasas_complete_cmd_dpc_fusion((unsigned long)instance);
			if (instance->requestorId && reason) {
				dev_warn(&instance->pdev->dev, "SR-IOV Found FW in FAULT"
				" state while polling during"
				" I/O timeout handling for %d\n",
				instance->host->host_no);
				*convert = 1;
			}

			retval = 1;
			goto out;
		}

		if (reason == MFI_IO_TIMEOUT_OCR) {
			dev_info(&instance->pdev->dev,
				"MFI IO is timed out, initiating OCR\n");
			megasas_complete_cmd_dpc_fusion((unsigned long)instance);
			retval = 1;
			goto out;
		}

		/* If SR-IOV VF mode & heartbeat timeout, don't wait */
		if (instance->requestorId && !reason) {
			retval = 1;
			goto out;
		}

		/* If SR-IOV VF mode & I/O timeout, check for HB timeout */
		if (instance->requestorId && (reason == SCSIIO_TIMEOUT_OCR)) {
			if (instance->hb_host_mem->HB.fwCounter !=
			    instance->hb_host_mem->HB.driverCounter) {
				instance->hb_host_mem->HB.driverCounter =
					instance->hb_host_mem->HB.fwCounter;
				hb_seconds_missed = 0;
			} else {
				hb_seconds_missed++;
				if (hb_seconds_missed ==
				    (MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF/HZ)) {
					dev_warn(&instance->pdev->dev, "SR-IOV:"
					       " Heartbeat never completed "
					       " while polling during I/O "
					       " timeout handling for "
					       "scsi%d.\n",
					       instance->host->host_no);
					       *convert = 1;
					       retval = 1;
					       goto out;
				}
			}
		}

		megasas_complete_cmd_dpc_fusion((unsigned long)instance);
		outstanding = atomic_read(&instance->fw_outstanding);
		if (!outstanding)
			goto out;

		if (!(i % MEGASAS_RESET_NOTICE_INTERVAL)) {
			dev_notice(&instance->pdev->dev, "[%2d]waiting for %d "
			       "commands to complete for scsi%d\n", i,
			       outstanding, instance->host->host_no);
		}
		msleep(1000);
	}

	if (atomic_read(&instance->fw_outstanding)) {
		dev_err(&instance->pdev->dev, "pending commands remain after waiting, "
		       "will reset adapter scsi%d.\n",
		       instance->host->host_no);
		*convert = 1;
		retval = 1;
	}
out:
	return retval;
}