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
struct scsi_lun {int /*<<< orphan*/  scsi_lun; } ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct sas_internal {TYPE_1__* dft; } ;
struct domain_device {int dummy; } ;
struct Scsi_Host {scalar_t__ ehandler; int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {int /*<<< orphan*/  lun; struct Scsi_Host* host; } ;
struct TYPE_3__ {int (* lldd_lu_reset ) (struct domain_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  SAS_DEV_LU_RESET ; 
 int SUCCESS ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_SUCC ; 
 struct domain_device* cmd_to_domain_dev (struct scsi_cmnd*) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int sas_queue_reset (struct domain_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct domain_device*,int /*<<< orphan*/ ) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

int sas_eh_device_reset_handler(struct scsi_cmnd *cmd)
{
	int res;
	struct scsi_lun lun;
	struct Scsi_Host *host = cmd->device->host;
	struct domain_device *dev = cmd_to_domain_dev(cmd);
	struct sas_internal *i = to_sas_internal(host->transportt);

	if (current != host->ehandler)
		return sas_queue_reset(dev, SAS_DEV_LU_RESET, cmd->device->lun, 0);

	int_to_scsilun(cmd->device->lun, &lun);

	if (!i->dft->lldd_lu_reset)
		return FAILED;

	res = i->dft->lldd_lu_reset(dev, lun.scsi_lun);
	if (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		return SUCCESS;

	return FAILED;
}