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
struct scsi_target {int /*<<< orphan*/  max_target_blocked; int /*<<< orphan*/  target_blocked; } ;
struct scsi_device {int /*<<< orphan*/  max_device_blocked; int /*<<< orphan*/  device_blocked; struct Scsi_Host* host; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct Scsi_Host {int /*<<< orphan*/  max_host_blocked; int /*<<< orphan*/  host_blocked; } ;

/* Variables and functions */
#define  SCSI_MLQUEUE_DEVICE_BUSY 131 
#define  SCSI_MLQUEUE_EH_RETRY 130 
#define  SCSI_MLQUEUE_HOST_BUSY 129 
#define  SCSI_MLQUEUE_TARGET_BUSY 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 

__attribute__((used)) static void
scsi_set_blocked(struct scsi_cmnd *cmd, int reason)
{
	struct Scsi_Host *host = cmd->device->host;
	struct scsi_device *device = cmd->device;
	struct scsi_target *starget = scsi_target(device);

	/*
	 * Set the appropriate busy bit for the device/host.
	 *
	 * If the host/device isn't busy, assume that something actually
	 * completed, and that we should be able to queue a command now.
	 *
	 * Note that the prior mid-layer assumption that any host could
	 * always queue at least one command is now broken.  The mid-layer
	 * will implement a user specifiable stall (see
	 * scsi_host.max_host_blocked and scsi_device.max_device_blocked)
	 * if a command is requeued with no other commands outstanding
	 * either for the device or for the host.
	 */
	switch (reason) {
	case SCSI_MLQUEUE_HOST_BUSY:
		atomic_set(&host->host_blocked, host->max_host_blocked);
		break;
	case SCSI_MLQUEUE_DEVICE_BUSY:
	case SCSI_MLQUEUE_EH_RETRY:
		atomic_set(&device->device_blocked,
			   device->max_device_blocked);
		break;
	case SCSI_MLQUEUE_TARGET_BUSY:
		atomic_set(&starget->target_blocked,
			   starget->max_target_blocked);
		break;
	}
}