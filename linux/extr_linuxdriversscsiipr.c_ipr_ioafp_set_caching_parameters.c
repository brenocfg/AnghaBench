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
struct TYPE_3__ {int* cdb; } ;
struct ipr_ioarcb {TYPE_1__ cmd_pkt; } ;
struct ipr_ioa_cfg {TYPE_2__* vpd_cbs; } ;
struct ipr_inquiry_pageC4 {int* cache_cap; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step_failed; int /*<<< orphan*/  job_step; struct ipr_ioa_cfg* ioa_cfg; struct ipr_ioarcb ioarcb; } ;
struct TYPE_4__ {struct ipr_inquiry_pageC4 pageC4_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int IPR_CAP_SYNC_CACHE ; 
 int /*<<< orphan*/  IPR_IOA_RES_HANDLE ; 
 int /*<<< orphan*/  IPR_IOA_SA_CHANGE_CACHE_PARAMS ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_SET_SUP_DEVICE_TIMEOUT ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_build_ioa_service_action (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_ioa_service_action_failed ; 
 int /*<<< orphan*/  ipr_ioafp_query_ioa_cfg ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static int ipr_ioafp_set_caching_parameters(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_inquiry_pageC4 *pageC4 = &ioa_cfg->vpd_cbs->pageC4_data;

	ENTER;

	ipr_cmd->job_step = ipr_ioafp_query_ioa_cfg;

	if (pageC4->cache_cap[0] & IPR_CAP_SYNC_CACHE) {
		ipr_build_ioa_service_action(ipr_cmd,
					     cpu_to_be32(IPR_IOA_RES_HANDLE),
					     IPR_IOA_SA_CHANGE_CACHE_PARAMS);

		ioarcb->cmd_pkt.cdb[2] = 0x40;

		ipr_cmd->job_step_failed = ipr_ioa_service_action_failed;
		ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout,
			   IPR_SET_SUP_DEVICE_TIMEOUT);

		LEAVE;
		return IPR_RC_JOB_RETURN;
	}

	LEAVE;
	return IPR_RC_JOB_CONTINUE;
}