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
struct scsi_target {int dummy; } ;
struct scsi_device {int /*<<< orphan*/  host; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct ibmvfc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int FAILED ; 
 int FAST_IO_FAIL ; 
 int /*<<< orphan*/  IBMVFC_TARGET_RESET ; 
 int /*<<< orphan*/  LEAVE ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ibmvfc_dev_cancel_all_noreset ; 
 int /*<<< orphan*/  ibmvfc_dev_cancel_all_reset ; 
 int /*<<< orphan*/  ibmvfc_match_target ; 
 int ibmvfc_reset_device (struct scsi_device*,int /*<<< orphan*/ ,char*) ; 
 int ibmvfc_wait_for_ops (struct ibmvfc_host*,struct scsi_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_wait_while_resetting (struct ibmvfc_host*) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 struct ibmvfc_host* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  starget_for_each_device (struct scsi_target*,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_eh_target_reset_handler(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct ibmvfc_host *vhost = shost_priv(sdev->host);
	struct scsi_target *starget = scsi_target(sdev);
	int block_rc;
	int reset_rc = 0;
	int rc = FAILED;
	unsigned long cancel_rc = 0;

	ENTER;
	block_rc = fc_block_scsi_eh(cmd);
	ibmvfc_wait_while_resetting(vhost);
	if (block_rc != FAST_IO_FAIL) {
		starget_for_each_device(starget, &cancel_rc, ibmvfc_dev_cancel_all_reset);
		reset_rc = ibmvfc_reset_device(sdev, IBMVFC_TARGET_RESET, "target");
	} else
		starget_for_each_device(starget, &cancel_rc, ibmvfc_dev_cancel_all_noreset);

	if (!cancel_rc && !reset_rc)
		rc = ibmvfc_wait_for_ops(vhost, starget, ibmvfc_match_target);

	if (block_rc == FAST_IO_FAIL && rc != FAILED)
		rc = FAST_IO_FAIL;

	LEAVE;
	return rc;
}