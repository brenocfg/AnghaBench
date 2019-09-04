#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_scsi_dev {TYPE_1__* port; } ;
struct zfcp_fsf_req {int status; int /*<<< orphan*/  completion; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;
struct scsi_device {int dummy; } ;
struct fc_rport {int dummy; } ;
struct TYPE_2__ {struct zfcp_adapter* adapter; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int ZFCP_STATUS_FSFREQ_TMFUNCFAILED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int fc_block_rport (struct fc_rport*) ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_devreset (char*,struct scsi_device*,int /*<<< orphan*/ ,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 
 struct zfcp_fsf_req* zfcp_fsf_fcp_task_mgmt (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_scsi_forget_cmnds (struct zfcp_scsi_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_scsi_task_mgmt_function(struct scsi_device *sdev, u8 tm_flags)
{
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	struct zfcp_adapter *adapter = zfcp_sdev->port->adapter;
	struct fc_rport *rport = starget_to_rport(scsi_target(sdev));
	struct zfcp_fsf_req *fsf_req = NULL;
	int retval = SUCCESS, ret;
	int retry = 3;

	while (retry--) {
		fsf_req = zfcp_fsf_fcp_task_mgmt(sdev, tm_flags);
		if (fsf_req)
			break;

		zfcp_dbf_scsi_devreset("wait", sdev, tm_flags, NULL);
		zfcp_erp_wait(adapter);
		ret = fc_block_rport(rport);
		if (ret) {
			zfcp_dbf_scsi_devreset("fiof", sdev, tm_flags, NULL);
			return ret;
		}

		if (!(atomic_read(&adapter->status) &
		      ZFCP_STATUS_COMMON_RUNNING)) {
			zfcp_dbf_scsi_devreset("nres", sdev, tm_flags, NULL);
			return SUCCESS;
		}
	}
	if (!fsf_req) {
		zfcp_dbf_scsi_devreset("reqf", sdev, tm_flags, NULL);
		return FAILED;
	}

	wait_for_completion(&fsf_req->completion);

	if (fsf_req->status & ZFCP_STATUS_FSFREQ_TMFUNCFAILED) {
		zfcp_dbf_scsi_devreset("fail", sdev, tm_flags, fsf_req);
		retval = FAILED;
	} else {
		zfcp_dbf_scsi_devreset("okay", sdev, tm_flags, fsf_req);
		zfcp_scsi_forget_cmnds(zfcp_sdev, tm_flags);
	}

	zfcp_fsf_req_free(fsf_req);
	return retval;
}