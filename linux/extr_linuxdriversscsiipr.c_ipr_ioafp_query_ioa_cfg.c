#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* cdb; int /*<<< orphan*/  request_type; } ;
struct ipr_ioarcb {TYPE_3__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct ipr_ioa_cfg {int dual_raid; int cfg_table_size; int /*<<< orphan*/  cfg_table_dma; TYPE_2__* pdev; TYPE_1__* vpd_cbs; } ;
struct ipr_inquiry_page3 {int /*<<< orphan*/ * minor_release; int /*<<< orphan*/  card_type; int /*<<< orphan*/  major_release; } ;
struct ipr_inquiry_cap {int cap; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; struct ipr_ioarcb ioarcb; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct ipr_inquiry_cap cap; struct ipr_inquiry_page3 page3_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int IPR_CAP_DUAL_IOA_RAID ; 
 int /*<<< orphan*/  IPR_INTERNAL_TIMEOUT ; 
 int /*<<< orphan*/  IPR_IOADL_FLAGS_READ_LAST ; 
 int /*<<< orphan*/  IPR_IOA_RES_HANDLE ; 
 int IPR_QUERY_IOA_CONFIG ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_RQTYPE_IOACMD ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_init_ioadl (struct ipr_cmnd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_init_res_table ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static int ipr_ioafp_query_ioa_cfg(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	struct ipr_inquiry_page3 *ucode_vpd = &ioa_cfg->vpd_cbs->page3_data;
	struct ipr_inquiry_cap *cap = &ioa_cfg->vpd_cbs->cap;

	ENTER;
	if (cap->cap & IPR_CAP_DUAL_IOA_RAID)
		ioa_cfg->dual_raid = 1;
	dev_info(&ioa_cfg->pdev->dev, "Adapter firmware version: %02X%02X%02X%02X\n",
		 ucode_vpd->major_release, ucode_vpd->card_type,
		 ucode_vpd->minor_release[0], ucode_vpd->minor_release[1]);
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_IOACMD;
	ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

	ioarcb->cmd_pkt.cdb[0] = IPR_QUERY_IOA_CONFIG;
	ioarcb->cmd_pkt.cdb[6] = (ioa_cfg->cfg_table_size >> 16) & 0xff;
	ioarcb->cmd_pkt.cdb[7] = (ioa_cfg->cfg_table_size >> 8) & 0xff;
	ioarcb->cmd_pkt.cdb[8] = ioa_cfg->cfg_table_size & 0xff;

	ipr_init_ioadl(ipr_cmd, ioa_cfg->cfg_table_dma, ioa_cfg->cfg_table_size,
		       IPR_IOADL_FLAGS_READ_LAST);

	ipr_cmd->job_step = ipr_init_res_table;

	ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout, IPR_INTERNAL_TIMEOUT);

	LEAVE;
	return IPR_RC_JOB_RETURN;
}