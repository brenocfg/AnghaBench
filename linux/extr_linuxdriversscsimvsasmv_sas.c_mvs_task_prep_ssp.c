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
typedef  int u8 ;
typedef  size_t u32 ;
typedef  void* u16 ;
struct ssp_frame_hdr {scalar_t__ frame_type; int* hashed_dest_addr; int* hashed_src_addr; void* tag; } ;
struct TYPE_5__ {int task_attr; int task_prio; TYPE_1__* cmd; int /*<<< orphan*/  LUN; scalar_t__ enable_first_burst; } ;
struct sas_task {size_t total_xfer_len; int /*<<< orphan*/  scatter; TYPE_2__ ssp_task; struct domain_device* dev; } ;
struct mvs_tmf_task {int tmf; int tag_of_task_to_be_managed; } ;
struct mvs_task_exec_info {size_t tag; size_t n_elem; struct mvs_port* port; struct mvs_cmd_hdr* hdr; struct sas_task* task; } ;
struct mvs_slot_info {size_t tx; size_t buf_dma; void* response; void* buf; } ;
struct mvs_port {size_t wide_port_phymap; } ;
struct mvs_info {size_t tx_prod; int flags; void** tx; struct mvs_slot_info* slot_info; } ;
struct mvs_err_info {int dummy; } ;
struct mvs_device {size_t device_id; } ;
struct mvs_cmd_hdr {void* lens; scalar_t__* reserved; void* status_buf; void* prd_tbl; void* open_frame; void* cmd_tbl; void* data_len; void* tags; void* flags; } ;
struct domain_device {size_t const linkrate; int /*<<< orphan*/ * hashed_sas_addr; int /*<<< orphan*/ * sas_addr; struct asd_sas_port* port; struct mvs_device* lldd_dev; } ;
struct asd_sas_port {size_t phy_mask; size_t linkrate; } ;
typedef  size_t dma_addr_t ;
struct TYPE_6__ {size_t (* prd_size ) () ;int /*<<< orphan*/  (* make_prd ) (int /*<<< orphan*/ ,size_t,void*) ;} ;
struct TYPE_4__ {int cmd_len; int /*<<< orphan*/ * cmnd; } ;

/* Variables and functions */
 int HASHED_SAS_ADDR_SIZE ; 
 size_t MCH_FBURST ; 
 size_t MCH_PRD_LEN_SHIFT ; 
 size_t MCH_RETRY ; 
 size_t MCH_SSP_FR_CMD ; 
 size_t MCH_SSP_FR_TASK ; 
 size_t MCH_SSP_FR_TYPE_SHIFT ; 
 int MVF_FLAG_SOC ; 
 TYPE_3__* MVS_CHIP_DISP ; 
 int MVS_OAF_SZ ; 
 int MVS_SLOT_BUF_SZ ; 
 int MVS_SSP_CMD_SZ ; 
 int PROTOCOL_SSP ; 
 int SAS_ADDR_SIZE ; 
 size_t SB_RFB_MAX ; 
 scalar_t__ SSP_COMMAND ; 
 scalar_t__ SSP_TASK ; 
#define  TMF_ABORT_TASK 129 
#define  TMF_QUERY_TASK 128 
 size_t TXQ_CMD_SHIFT ; 
 size_t TXQ_CMD_SSP ; 
 size_t TXQ_MODE_I ; 
 size_t TXQ_PHY_MASK ; 
 size_t TXQ_PHY_SHIFT ; 
 void* cpu_to_be16 (size_t) ; 
 void* cpu_to_le32 (size_t) ; 
 void* cpu_to_le64 (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int min (size_t,size_t const) ; 
 size_t stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,size_t,void*) ; 

__attribute__((used)) static int mvs_task_prep_ssp(struct mvs_info *mvi,
			     struct mvs_task_exec_info *tei, int is_tmf,
			     struct mvs_tmf_task *tmf)
{
	struct sas_task *task = tei->task;
	struct mvs_cmd_hdr *hdr = tei->hdr;
	struct mvs_port *port = tei->port;
	struct domain_device *dev = task->dev;
	struct mvs_device *mvi_dev = dev->lldd_dev;
	struct asd_sas_port *sas_port = dev->port;
	struct mvs_slot_info *slot;
	void *buf_prd;
	struct ssp_frame_hdr *ssp_hdr;
	void *buf_tmp;
	u8 *buf_cmd, *buf_oaf, fburst = 0;
	dma_addr_t buf_tmp_dma;
	u32 flags;
	u32 resp_len, req_len, i, tag = tei->tag;
	const u32 max_resp_len = SB_RFB_MAX;
	u32 phy_mask;

	slot = &mvi->slot_info[tag];

	phy_mask = ((port->wide_port_phymap) ? port->wide_port_phymap :
		sas_port->phy_mask) & TXQ_PHY_MASK;

	slot->tx = mvi->tx_prod;
	mvi->tx[mvi->tx_prod] = cpu_to_le32(TXQ_MODE_I | tag |
				(TXQ_CMD_SSP << TXQ_CMD_SHIFT) |
				(phy_mask << TXQ_PHY_SHIFT));

	flags = MCH_RETRY;
	if (task->ssp_task.enable_first_burst) {
		flags |= MCH_FBURST;
		fburst = (1 << 7);
	}
	if (is_tmf)
		flags |= (MCH_SSP_FR_TASK << MCH_SSP_FR_TYPE_SHIFT);
	else
		flags |= (MCH_SSP_FR_CMD << MCH_SSP_FR_TYPE_SHIFT);

	hdr->flags = cpu_to_le32(flags | (tei->n_elem << MCH_PRD_LEN_SHIFT));
	hdr->tags = cpu_to_le32(tag);
	hdr->data_len = cpu_to_le32(task->total_xfer_len);

	/*
	 * arrange MVS_SLOT_BUF_SZ-sized DMA buffer according to our needs
	 */

	/* region 1: command table area (MVS_SSP_CMD_SZ bytes) ************** */
	buf_cmd = buf_tmp = slot->buf;
	buf_tmp_dma = slot->buf_dma;

	hdr->cmd_tbl = cpu_to_le64(buf_tmp_dma);

	buf_tmp += MVS_SSP_CMD_SZ;
	buf_tmp_dma += MVS_SSP_CMD_SZ;

	/* region 2: open address frame area (MVS_OAF_SZ bytes) ********* */
	buf_oaf = buf_tmp;
	hdr->open_frame = cpu_to_le64(buf_tmp_dma);

	buf_tmp += MVS_OAF_SZ;
	buf_tmp_dma += MVS_OAF_SZ;

	/* region 3: PRD table ********************************************* */
	buf_prd = buf_tmp;
	if (tei->n_elem)
		hdr->prd_tbl = cpu_to_le64(buf_tmp_dma);
	else
		hdr->prd_tbl = 0;

	i = MVS_CHIP_DISP->prd_size() * tei->n_elem;
	buf_tmp += i;
	buf_tmp_dma += i;

	/* region 4: status buffer (larger the PRD, smaller this buf) ****** */
	slot->response = buf_tmp;
	hdr->status_buf = cpu_to_le64(buf_tmp_dma);
	if (mvi->flags & MVF_FLAG_SOC)
		hdr->reserved[0] = 0;

	resp_len = MVS_SLOT_BUF_SZ - MVS_SSP_CMD_SZ - MVS_OAF_SZ -
	    sizeof(struct mvs_err_info) - i;
	resp_len = min(resp_len, max_resp_len);

	req_len = sizeof(struct ssp_frame_hdr) + 28;

	/* request, response lengths */
	hdr->lens = cpu_to_le32(((resp_len / 4) << 16) | (req_len / 4));

	/* generate open address frame hdr (first 12 bytes) */
	/* initiator, SSP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PROTOCOL_SSP << 4) | 0x1;
	buf_oaf[1] = min(sas_port->linkrate, dev->linkrate) & 0xf;
	*(u16 *)(buf_oaf + 2) = cpu_to_be16(mvi_dev->device_id + 1);
	memcpy(buf_oaf + 4, dev->sas_addr, SAS_ADDR_SIZE);

	/* fill in SSP frame header (Command Table.SSP frame header) */
	ssp_hdr = (struct ssp_frame_hdr *)buf_cmd;

	if (is_tmf)
		ssp_hdr->frame_type = SSP_TASK;
	else
		ssp_hdr->frame_type = SSP_COMMAND;

	memcpy(ssp_hdr->hashed_dest_addr, dev->hashed_sas_addr,
	       HASHED_SAS_ADDR_SIZE);
	memcpy(ssp_hdr->hashed_src_addr,
	       dev->hashed_sas_addr, HASHED_SAS_ADDR_SIZE);
	ssp_hdr->tag = cpu_to_be16(tag);

	/* fill in IU for TASK and Command Frame */
	buf_cmd += sizeof(*ssp_hdr);
	memcpy(buf_cmd, &task->ssp_task.LUN, 8);

	if (ssp_hdr->frame_type != SSP_TASK) {
		buf_cmd[9] = fburst | task->ssp_task.task_attr |
				(task->ssp_task.task_prio << 3);
		memcpy(buf_cmd + 12, task->ssp_task.cmd->cmnd,
		       task->ssp_task.cmd->cmd_len);
	} else{
		buf_cmd[10] = tmf->tmf;
		switch (tmf->tmf) {
		case TMF_ABORT_TASK:
		case TMF_QUERY_TASK:
			buf_cmd[12] =
				(tmf->tag_of_task_to_be_managed >> 8) & 0xff;
			buf_cmd[13] =
				tmf->tag_of_task_to_be_managed & 0xff;
			break;
		default:
			break;
		}
	}
	/* fill in PRD (scatter/gather) table, if any */
	MVS_CHIP_DISP->make_prd(task->scatter, tei->n_elem, buf_prd);
	return 0;
}