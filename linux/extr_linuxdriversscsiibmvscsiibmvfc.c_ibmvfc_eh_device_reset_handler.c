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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct ibmvfc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int FAILED ; 
 int FAST_IO_FAIL ; 
 int /*<<< orphan*/  IBMVFC_LUN_RESET ; 
 int /*<<< orphan*/  IBMVFC_TMF_LUN_RESET ; 
 int /*<<< orphan*/  IBMVFC_TMF_SUPPRESS_ABTS ; 
 int /*<<< orphan*/  LEAVE ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 int ibmvfc_cancel_all (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_match_lun ; 
 int ibmvfc_reset_device (struct scsi_device*,int /*<<< orphan*/ ,char*) ; 
 int ibmvfc_wait_for_ops (struct ibmvfc_host*,struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_wait_while_resetting (struct ibmvfc_host*) ; 
 struct ibmvfc_host* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_eh_device_reset_handler(struct scsi_cmnd *cmd)
{
	struct scsi_device *sdev = cmd->device;
	struct ibmvfc_host *vhost = shost_priv(sdev->host);
	int cancel_rc, block_rc, reset_rc = 0;
	int rc = FAILED;

	ENTER;
	block_rc = fc_block_scsi_eh(cmd);
	ibmvfc_wait_while_resetting(vhost);
	if (block_rc != FAST_IO_FAIL) {
		cancel_rc = ibmvfc_cancel_all(sdev, IBMVFC_TMF_LUN_RESET);
		reset_rc = ibmvfc_reset_device(sdev, IBMVFC_LUN_RESET, "LUN");
	} else
		cancel_rc = ibmvfc_cancel_all(sdev, IBMVFC_TMF_SUPPRESS_ABTS);

	if (!cancel_rc && !reset_rc)
		rc = ibmvfc_wait_for_ops(vhost, sdev, ibmvfc_match_lun);

	if (block_rc == FAST_IO_FAIL && rc != FAILED)
		rc = FAST_IO_FAIL;

	LEAVE;
	return rc;
}