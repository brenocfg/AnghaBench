#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ptr; } ;
struct scsi_cmnd {TYPE_2__* device; TYPE_1__ SCp; } ;
struct megasas_instance {scalar_t__ adapter_type; int /*<<< orphan*/  fw_outstanding; } ;
struct megasas_cmd_fusion {int /*<<< orphan*/  io_request; } ;
struct TYPE_7__ {int /*<<< orphan*/  shost_state; scalar_t__ hostdata; } ;
struct TYPE_6__ {TYPE_3__* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE ; 
 scalar_t__ MFI_SERIES ; 
 int /*<<< orphan*/  SCSIIO_TIMEOUT_OCR ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  megasas_dump_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int megasas_generic_reset (struct scsi_cmnd*) ; 
 int megasas_reset_fusion (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_busy (TYPE_3__*) ; 

__attribute__((used)) static int megasas_reset_bus_host(struct scsi_cmnd *scmd)
{
	int ret;
	struct megasas_instance *instance;

	instance = (struct megasas_instance *)scmd->device->host->hostdata;

	scmd_printk(KERN_INFO, scmd,
		"Controller reset is requested due to IO timeout\n"
		"SCSI command pointer: (%p)\t SCSI host state: %d\t"
		" SCSI host busy: %d\t FW outstanding: %d\n",
		scmd, scmd->device->host->shost_state,
		scsi_host_busy(scmd->device->host),
		atomic_read(&instance->fw_outstanding));

	/*
	 * First wait for all commands to complete
	 */
	if (instance->adapter_type == MFI_SERIES) {
		ret = megasas_generic_reset(scmd);
	} else {
		struct megasas_cmd_fusion *cmd;
		cmd = (struct megasas_cmd_fusion *)scmd->SCp.ptr;
		if (cmd)
			megasas_dump_frame(cmd->io_request,
				MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE);
		ret = megasas_reset_fusion(scmd->device->host,
				SCSIIO_TIMEOUT_OCR);
	}

	return ret;
}