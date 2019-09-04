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
typedef  void* u8 ;
struct TYPE_2__ {void** cdb; int /*<<< orphan*/  request_type; } ;
struct ipr_ioarcb {TYPE_1__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct ipr_cmnd {struct ipr_ioarcb ioarcb; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 void* INQUIRY ; 
 int /*<<< orphan*/  IPR_INTERNAL_TIMEOUT ; 
 int /*<<< orphan*/  IPR_IOADL_FLAGS_READ_LAST ; 
 int /*<<< orphan*/  IPR_IOA_RES_HANDLE ; 
 int /*<<< orphan*/  IPR_RQTYPE_SCSICDB ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_init_ioadl (struct ipr_cmnd*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_reset_ioa_job ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static void ipr_ioafp_inquiry(struct ipr_cmnd *ipr_cmd, u8 flags, u8 page,
			      dma_addr_t dma_addr, u8 xfer_len)
{
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ENTER;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;
	ioarcb->res_handle = cpu_to_be32(IPR_IOA_RES_HANDLE);

	ioarcb->cmd_pkt.cdb[0] = INQUIRY;
	ioarcb->cmd_pkt.cdb[1] = flags;
	ioarcb->cmd_pkt.cdb[2] = page;
	ioarcb->cmd_pkt.cdb[4] = xfer_len;

	ipr_init_ioadl(ipr_cmd, dma_addr, xfer_len, IPR_IOADL_FLAGS_READ_LAST);

	ipr_do_req(ipr_cmd, ipr_reset_ioa_job, ipr_timeout, IPR_INTERNAL_TIMEOUT);
	LEAVE;
}