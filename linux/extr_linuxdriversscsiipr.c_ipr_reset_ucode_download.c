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
struct ipr_sglist {int buffer_len; } ;
struct ipr_ioa_cfg {scalar_t__ sis64; struct ipr_sglist* ucode_sglist; } ;
struct TYPE_3__ {int* cdb; int /*<<< orphan*/  request_type; } ;
struct TYPE_4__ {TYPE_1__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; TYPE_2__ ioarcb; struct ipr_ioa_cfg* ioa_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  IPR_IOA_RES_HANDLE ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_RQTYPE_SCSICDB ; 
 int /*<<< orphan*/  IPR_WRITE_BUFFER_TIMEOUT ; 
 int IPR_WR_BUF_DOWNLOAD_AND_SAVE ; 
 int /*<<< orphan*/  LEAVE ; 
 int WRITE_BUFFER ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_build_ucode_ioadl (struct ipr_cmnd*,struct ipr_sglist*) ; 
 int /*<<< orphan*/  ipr_build_ucode_ioadl64 (struct ipr_cmnd*,struct ipr_sglist*) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_reset_alert ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_reset_ucode_download_done ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static int ipr_reset_ucode_download(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	struct ipr_sglist *sglist = ioa_cfg->ucode_sglist;

	ENTER;
	ipr_cmd->job_step = ipr_reset_alert;

	if (!sglist)
		return IPR_RC_JOB_CONTINUE;

	ipr_cmd->ioarcb.res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);
	ipr_cmd->ioarcb.cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;
	ipr_cmd->ioarcb.cmd_pkt.cdb[0] = WRITE_BUFFER;
	ipr_cmd->ioarcb.cmd_pkt.cdb[1] = IPR_WR_BUF_DOWNLOAD_AND_SAVE;
	ipr_cmd->ioarcb.cmd_pkt.cdb[6] = (sglist->buffer_len & 0xff0000) >> 16;
	ipr_cmd->ioarcb.cmd_pkt.cdb[7] = (sglist->buffer_len & 0x00ff00) >> 8;
	ipr_cmd->ioarcb.cmd_pkt.cdb[8] = sglist->buffer_len & 0x0000ff;

	if (ioa_cfg->sis64)
		ipr_build_ucode_ioadl64(ipr_cmd, sglist);
	else
		ipr_build_ucode_ioadl(ipr_cmd, sglist);
	ipr_cmd->job_step = ipr_reset_ucode_download_done;

	ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout,
		   IPR_WRITE_BUFFER_TIMEOUT);

	LEAVE;
	return IPR_RC_JOB_RETURN;
}