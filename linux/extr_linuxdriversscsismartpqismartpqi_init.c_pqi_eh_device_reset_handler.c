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
struct scsi_cmnd {TYPE_1__* device; } ;
struct pqi_scsi_dev {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct pqi_ctrl_info {TYPE_2__* pci_dev; int /*<<< orphan*/  lun_reset_mutex; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct pqi_scsi_dev* hostdata; struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_check_ctrl_health (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_block_requests (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_unblock_requests (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_wait_until_quiesced (struct pqi_ctrl_info*) ; 
 int pqi_device_reset (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 int /*<<< orphan*/  pqi_device_reset_done (struct pqi_scsi_dev*) ; 
 int /*<<< orphan*/  pqi_device_reset_start (struct pqi_scsi_dev*) ; 
 int /*<<< orphan*/  pqi_fail_io_queued_for_device (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 int pqi_wait_until_inbound_queues_empty (struct pqi_ctrl_info*) ; 
 struct pqi_ctrl_info* shost_to_hba (struct Scsi_Host*) ; 

__attribute__((used)) static int pqi_eh_device_reset_handler(struct scsi_cmnd *scmd)
{
	int rc;
	struct Scsi_Host *shost;
	struct pqi_ctrl_info *ctrl_info;
	struct pqi_scsi_dev *device;

	shost = scmd->device->host;
	ctrl_info = shost_to_hba(shost);
	device = scmd->device->hostdata;

	dev_err(&ctrl_info->pci_dev->dev,
		"resetting scsi %d:%d:%d:%d\n",
		shost->host_no, device->bus, device->target, device->lun);

	pqi_check_ctrl_health(ctrl_info);
	if (pqi_ctrl_offline(ctrl_info)) {
		rc = FAILED;
		goto out;
	}

	mutex_lock(&ctrl_info->lun_reset_mutex);

	pqi_ctrl_block_requests(ctrl_info);
	pqi_ctrl_wait_until_quiesced(ctrl_info);
	pqi_fail_io_queued_for_device(ctrl_info, device);
	rc = pqi_wait_until_inbound_queues_empty(ctrl_info);
	pqi_device_reset_start(device);
	pqi_ctrl_unblock_requests(ctrl_info);

	if (rc)
		rc = FAILED;
	else
		rc = pqi_device_reset(ctrl_info, device);

	pqi_device_reset_done(device);

	mutex_unlock(&ctrl_info->lun_reset_mutex);

out:
	dev_err(&ctrl_info->pci_dev->dev,
		"reset of scsi %d:%d:%d:%d: %s\n",
		shost->host_no, device->bus, device->target, device->lun,
		rc == SUCCESS ? "SUCCESS" : "FAILED");

	return rc;
}