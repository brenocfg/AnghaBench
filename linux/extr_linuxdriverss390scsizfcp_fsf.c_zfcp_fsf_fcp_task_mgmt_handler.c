#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_req {int status; TYPE_4__* qtcb; struct scsi_device* data; } ;
struct scsi_device {int dummy; } ;
struct fcp_resp_with_ext {int dummy; } ;
struct fcp_resp_rsp_info {scalar_t__ rsp_code; } ;
struct TYPE_5__ {struct fcp_resp_with_ext iu; } ;
struct TYPE_6__ {TYPE_1__ fcp_rsp; } ;
struct TYPE_7__ {TYPE_2__ io; } ;
struct TYPE_8__ {TYPE_3__ bottom; } ;

/* Variables and functions */
 scalar_t__ FCP_TMF_CMPL ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int ZFCP_STATUS_FSFREQ_TMFUNCFAILED ; 
 int /*<<< orphan*/  zfcp_fsf_fcp_handler_common (struct zfcp_fsf_req*,struct scsi_device*) ; 

__attribute__((used)) static void zfcp_fsf_fcp_task_mgmt_handler(struct zfcp_fsf_req *req)
{
	struct scsi_device *sdev = req->data;
	struct fcp_resp_with_ext *fcp_rsp;
	struct fcp_resp_rsp_info *rsp_info;

	zfcp_fsf_fcp_handler_common(req, sdev);

	fcp_rsp = &req->qtcb->bottom.io.fcp_rsp.iu;
	rsp_info = (struct fcp_resp_rsp_info *) &fcp_rsp[1];

	if ((rsp_info->rsp_code != FCP_TMF_CMPL) ||
	     (req->status & ZFCP_STATUS_FSFREQ_ERROR))
		req->status |= ZFCP_STATUS_FSFREQ_TMFUNCFAILED;
}