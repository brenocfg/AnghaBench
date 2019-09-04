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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int* cdb; int /*<<< orphan*/  request_type; } ;
struct ipr_ioarcb {TYPE_2__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct ipr_ioa_cfg {size_t identify_hrrq_index; size_t hrrq_num; int nvectors; scalar_t__ sis64; struct ipr_hrr_queue* hrrq; TYPE_1__* pdev; } ;
struct ipr_hrr_queue {int size; scalar_t__ host_rrq_dma; } ;
struct ipr_cmnd {int (* job_step ) (struct ipr_cmnd*) ;struct ipr_ioarcb ioarcb; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int IPR_ID_HOST_RR_Q ; 
 int IPR_ID_HRRQ_SELE_ENABLE ; 
 int /*<<< orphan*/  IPR_INTERNAL_TIMEOUT ; 
 int /*<<< orphan*/  IPR_IOA_RES_HANDLE ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_RQTYPE_IOACMD ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipr_ioafp_std_inquiry (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static int ipr_ioafp_identify_hrrq(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	struct ipr_hrr_queue *hrrq;

	ENTER;
	ipr_cmd->job_step = ipr_ioafp_std_inquiry;
	if (ioa_cfg->identify_hrrq_index == 0)
		dev_info(&ioa_cfg->pdev->dev, "Starting IOA initialization sequence.\n");

	if (ioa_cfg->identify_hrrq_index < ioa_cfg->hrrq_num) {
		hrrq = &ioa_cfg->hrrq[ioa_cfg->identify_hrrq_index];

		ioarcb->cmd_pkt.cdb[0] = IPR_ID_HOST_RR_Q;
		ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

		ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
		if (ioa_cfg->sis64)
			ioarcb->cmd_pkt.cdb[1] = 0x1;

		if (ioa_cfg->nvectors == 1)
			ioarcb->cmd_pkt.cdb[1] &= ~IPR_ID_HRRQ_SELE_ENABLE;
		else
			ioarcb->cmd_pkt.cdb[1] |= IPR_ID_HRRQ_SELE_ENABLE;

		ioarcb->cmd_pkt.cdb[2] =
			((u64) hrrq->host_rrq_dma >> 24) & 0xff;
		ioarcb->cmd_pkt.cdb[3] =
			((u64) hrrq->host_rrq_dma >> 16) & 0xff;
		ioarcb->cmd_pkt.cdb[4] =
			((u64) hrrq->host_rrq_dma >> 8) & 0xff;
		ioarcb->cmd_pkt.cdb[5] =
			((u64) hrrq->host_rrq_dma) & 0xff;
		ioarcb->cmd_pkt.cdb[7] =
			((sizeof(u32) * hrrq->size) >> 8) & 0xff;
		ioarcb->cmd_pkt.cdb[8] =
			(sizeof(u32) * hrrq->size) & 0xff;

		if (ioarcb->cmd_pkt.cdb[1] & IPR_ID_HRRQ_SELE_ENABLE)
			ioarcb->cmd_pkt.cdb[9] =
					ioa_cfg->identify_hrrq_index;

		if (ioa_cfg->sis64) {
			ioarcb->cmd_pkt.cdb[10] =
				((u64) hrrq->host_rrq_dma >> 56) & 0xff;
			ioarcb->cmd_pkt.cdb[11] =
				((u64) hrrq->host_rrq_dma >> 48) & 0xff;
			ioarcb->cmd_pkt.cdb[12] =
				((u64) hrrq->host_rrq_dma >> 40) & 0xff;
			ioarcb->cmd_pkt.cdb[13] =
				((u64) hrrq->host_rrq_dma >> 32) & 0xff;
		}

		if (ioarcb->cmd_pkt.cdb[1] & IPR_ID_HRRQ_SELE_ENABLE)
			ioarcb->cmd_pkt.cdb[14] =
					ioa_cfg->identify_hrrq_index;

		ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout,
			   IPR_INTERNAL_TIMEOUT);

		if (++ioa_cfg->identify_hrrq_index < ioa_cfg->hrrq_num)
			ipr_cmd->job_step = ipr_ioafp_identify_hrrq;

		LEAVE;
		return IPR_RC_JOB_RETURN;
	}

	LEAVE;
	return IPR_RC_JOB_CONTINUE;
}