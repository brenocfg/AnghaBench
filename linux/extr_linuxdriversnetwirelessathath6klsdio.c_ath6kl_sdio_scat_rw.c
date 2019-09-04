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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mmc_request {int flags; int error; struct mmc_request* data; struct mmc_request* cmd; int /*<<< orphan*/  opcode; int /*<<< orphan*/  blocks; int /*<<< orphan*/  arg; } ;
struct mmc_data {int flags; int error; struct mmc_data* data; struct mmc_data* cmd; int /*<<< orphan*/  opcode; int /*<<< orphan*/  blocks; int /*<<< orphan*/  arg; } ;
struct mmc_command {int flags; int error; struct mmc_command* data; struct mmc_command* cmd; int /*<<< orphan*/  opcode; int /*<<< orphan*/  blocks; int /*<<< orphan*/  arg; } ;
struct hif_scatter_req {int len; int req; scalar_t__ addr; int status; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ ,struct hif_scatter_req*) ;int /*<<< orphan*/  scat_list; int /*<<< orphan*/  scat_entries; int /*<<< orphan*/  virt_dma_buf; scalar_t__ virt_scat; } ;
struct bus_request {struct hif_scatter_req* scat_req; } ;
struct ath6kl_sdio {TYPE_1__* ar; TYPE_2__* func; } ;
struct TYPE_8__ {int /*<<< orphan*/  host; } ;
struct TYPE_7__ {TYPE_4__* card; int /*<<< orphan*/  num; } ;
struct TYPE_6__ {int /*<<< orphan*/  htc_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD53_ARG_BLOCK_BASIS ; 
 int /*<<< orphan*/  CMD53_ARG_FIXED_ADDRESS ; 
 int /*<<< orphan*/  CMD53_ARG_INCR_ADDRESS ; 
 int /*<<< orphan*/  CMD53_ARG_READ ; 
 int /*<<< orphan*/  CMD53_ARG_WRITE ; 
 int HIF_ASYNCHRONOUS ; 
 int HIF_BLOCK_BASIS ; 
 int HIF_FIXED_ADDRESS ; 
 scalar_t__ HIF_MBOX0_EXT_WIDTH ; 
 scalar_t__ HIF_MBOX_BASE_ADDR ; 
 int /*<<< orphan*/  HIF_MBOX_BLOCK_SIZE ; 
 scalar_t__ HIF_MBOX_WIDTH ; 
 int HIF_WRITE ; 
 int MMC_CMD_ADTC ; 
 int MMC_RSP_R5 ; 
 int MMC_RSP_SPI_R5 ; 
 int /*<<< orphan*/  SD_IO_RW_EXTENDED ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_sdio_io (TYPE_2__*,int,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath6kl_sdio_set_cmd53_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_sdio_setup_scat_data (struct hif_scatter_req*,struct mmc_request*) ; 
 int /*<<< orphan*/  memset (struct mmc_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_set_data_timeout (struct mmc_request*,TYPE_4__*) ; 
 int /*<<< orphan*/  mmc_wait_for_req (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_2__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct hif_scatter_req*) ; 
 int /*<<< orphan*/  trace_ath6kl_sdio_scat (scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_sdio_scat_rw(struct ath6kl_sdio *ar_sdio,
			       struct bus_request *req)
{
	struct mmc_request mmc_req;
	struct mmc_command cmd;
	struct mmc_data data;
	struct hif_scatter_req *scat_req;
	u8 opcode, rw;
	int status, len;

	scat_req = req->scat_req;

	if (scat_req->virt_scat) {
		len = scat_req->len;
		if (scat_req->req & HIF_BLOCK_BASIS)
			len = round_down(len, HIF_MBOX_BLOCK_SIZE);

		status = ath6kl_sdio_io(ar_sdio->func, scat_req->req,
					scat_req->addr, scat_req->virt_dma_buf,
					len);
		goto scat_complete;
	}

	memset(&mmc_req, 0, sizeof(struct mmc_request));
	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&data, 0, sizeof(struct mmc_data));

	ath6kl_sdio_setup_scat_data(scat_req, &data);

	opcode = (scat_req->req & HIF_FIXED_ADDRESS) ?
		  CMD53_ARG_FIXED_ADDRESS : CMD53_ARG_INCR_ADDRESS;

	rw = (scat_req->req & HIF_WRITE) ? CMD53_ARG_WRITE : CMD53_ARG_READ;

	/* Fixup the address so that the last byte will fall on MBOX EOM */
	if (scat_req->req & HIF_WRITE) {
		if (scat_req->addr == HIF_MBOX_BASE_ADDR)
			scat_req->addr += HIF_MBOX_WIDTH - scat_req->len;
		else
			/* Uses extended address range */
			scat_req->addr += HIF_MBOX0_EXT_WIDTH - scat_req->len;
	}

	/* set command argument */
	ath6kl_sdio_set_cmd53_arg(&cmd.arg, rw, ar_sdio->func->num,
				  CMD53_ARG_BLOCK_BASIS, opcode, scat_req->addr,
				  data.blocks);

	cmd.opcode = SD_IO_RW_EXTENDED;
	cmd.flags = MMC_RSP_SPI_R5 | MMC_RSP_R5 | MMC_CMD_ADTC;

	mmc_req.cmd = &cmd;
	mmc_req.data = &data;

	sdio_claim_host(ar_sdio->func);

	mmc_set_data_timeout(&data, ar_sdio->func->card);

	trace_ath6kl_sdio_scat(scat_req->addr,
			       scat_req->req,
			       scat_req->len,
			       scat_req->scat_entries,
			       scat_req->scat_list);

	/* synchronous call to process request */
	mmc_wait_for_req(ar_sdio->func->card->host, &mmc_req);

	sdio_release_host(ar_sdio->func);

	status = cmd.error ? cmd.error : data.error;

scat_complete:
	scat_req->status = status;

	if (scat_req->status)
		ath6kl_err("Scatter write request failed:%d\n",
			   scat_req->status);

	if (scat_req->req & HIF_ASYNCHRONOUS)
		scat_req->complete(ar_sdio->ar->htc_target, scat_req);

	return status;
}