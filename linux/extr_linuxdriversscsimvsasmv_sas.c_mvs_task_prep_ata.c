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
typedef  int u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {scalar_t__ command; int sector_count; int flags; } ;
struct TYPE_6__ {TYPE_3__* atapi_packet; TYPE_3__ fis; int /*<<< orphan*/  device_control_reg_update; scalar_t__ use_ncq; } ;
struct sas_task {scalar_t__ data_dir; size_t total_xfer_len; int /*<<< orphan*/  scatter; TYPE_2__ ata_task; struct domain_device* dev; } ;
struct mvs_task_exec_info {size_t tag; size_t n_elem; struct mvs_cmd_hdr* hdr; struct sas_task* task; } ;
struct mvs_slot_info {size_t tx; size_t buf_dma; void* response; void* buf; } ;
struct mvs_info {size_t tx_prod; int flags; void** tx; struct mvs_slot_info* slot_info; } ;
struct mvs_err_info {int dummy; } ;
struct mvs_device {size_t taskfileset; scalar_t__ device_id; } ;
struct mvs_cmd_hdr {void* lens; scalar_t__* reserved; void* status_buf; void* prd_tbl; void* open_frame; void* cmd_tbl; void* data_len; void* tags; void* flags; } ;
struct host_to_dev_fis {int dummy; } ;
struct TYPE_5__ {scalar_t__ class; } ;
struct domain_device {size_t const linkrate; TYPE_3__* sas_addr; TYPE_1__ sata_dev; struct asd_sas_port* port; struct mvs_device* lldd_dev; } ;
struct asd_sas_port {size_t phy_mask; size_t linkrate; } ;
typedef  size_t dma_addr_t ;
struct TYPE_8__ {size_t (* prd_count ) () ;size_t (* prd_size ) () ;int /*<<< orphan*/  (* dma_fix ) (struct mvs_info*,size_t,int /*<<< orphan*/ ,size_t,void*) ;int /*<<< orphan*/  (* make_prd ) (int /*<<< orphan*/ ,size_t,void*) ;} ;

/* Variables and functions */
 scalar_t__ ATA_CMD_ID_ATAPI ; 
 scalar_t__ ATA_DEV_ATAPI ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int EBUSY ; 
 size_t MCH_ATAPI ; 
 size_t MCH_FPDMA ; 
 size_t MCH_PRD_LEN_SHIFT ; 
 int MVF_FLAG_SOC ; 
 int MVS_ATA_CMD_SZ ; 
 TYPE_4__* MVS_CHIP_DISP ; 
 scalar_t__ MVS_ID_NOT_MAPPED ; 
 scalar_t__ MVS_OAF_SZ ; 
 int MVS_SLOT_BUF_SZ ; 
 int PROTOCOL_STP ; 
 int SAS_ADDR_SIZE ; 
 size_t SB_RFB_MAX ; 
 int STP_ATAPI_CMD ; 
 int /*<<< orphan*/  TRASH_BUCKET_SIZE ; 
 size_t TXQ_CMD_SHIFT ; 
 size_t TXQ_CMD_STP ; 
 size_t TXQ_MODE_I ; 
 size_t TXQ_PHY_MASK ; 
 size_t TXQ_PHY_SHIFT ; 
 size_t TXQ_SRS_SHIFT ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 void* cpu_to_le32 (size_t) ; 
 void* cpu_to_le64 (size_t) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_3__*,int) ; 
 int min (size_t,size_t const) ; 
 int /*<<< orphan*/  mv_dprintk (char*,scalar_t__) ; 
 scalar_t__ mvs_assign_reg_set (struct mvs_info*,struct mvs_device*) ; 
 scalar_t__ mvs_get_ncq_tag (struct sas_task*,size_t*) ; 
 size_t stub1 () ; 
 size_t stub2 () ; 
 size_t stub3 () ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,size_t,void*) ; 
 int /*<<< orphan*/  stub5 (struct mvs_info*,size_t,int /*<<< orphan*/ ,size_t,void*) ; 

__attribute__((used)) static int mvs_task_prep_ata(struct mvs_info *mvi,
			     struct mvs_task_exec_info *tei)
{
	struct sas_task *task = tei->task;
	struct domain_device *dev = task->dev;
	struct mvs_device *mvi_dev = dev->lldd_dev;
	struct mvs_cmd_hdr *hdr = tei->hdr;
	struct asd_sas_port *sas_port = dev->port;
	struct mvs_slot_info *slot;
	void *buf_prd;
	u32 tag = tei->tag, hdr_tag;
	u32 flags, del_q;
	void *buf_tmp;
	u8 *buf_cmd, *buf_oaf;
	dma_addr_t buf_tmp_dma;
	u32 i, req_len, resp_len;
	const u32 max_resp_len = SB_RFB_MAX;

	if (mvs_assign_reg_set(mvi, mvi_dev) == MVS_ID_NOT_MAPPED) {
		mv_dprintk("Have not enough regiset for dev %d.\n",
			mvi_dev->device_id);
		return -EBUSY;
	}
	slot = &mvi->slot_info[tag];
	slot->tx = mvi->tx_prod;
	del_q = TXQ_MODE_I | tag |
		(TXQ_CMD_STP << TXQ_CMD_SHIFT) |
		((sas_port->phy_mask & TXQ_PHY_MASK) << TXQ_PHY_SHIFT) |
		(mvi_dev->taskfileset << TXQ_SRS_SHIFT);
	mvi->tx[mvi->tx_prod] = cpu_to_le32(del_q);

	if (task->data_dir == DMA_FROM_DEVICE)
		flags = (MVS_CHIP_DISP->prd_count() << MCH_PRD_LEN_SHIFT);
	else
		flags = (tei->n_elem << MCH_PRD_LEN_SHIFT);

	if (task->ata_task.use_ncq)
		flags |= MCH_FPDMA;
	if (dev->sata_dev.class == ATA_DEV_ATAPI) {
		if (task->ata_task.fis.command != ATA_CMD_ID_ATAPI)
			flags |= MCH_ATAPI;
	}

	hdr->flags = cpu_to_le32(flags);

	if (task->ata_task.use_ncq && mvs_get_ncq_tag(task, &hdr_tag))
		task->ata_task.fis.sector_count |= (u8) (hdr_tag << 3);
	else
		hdr_tag = tag;

	hdr->tags = cpu_to_le32(hdr_tag);

	hdr->data_len = cpu_to_le32(task->total_xfer_len);

	/*
	 * arrange MVS_SLOT_BUF_SZ-sized DMA buffer according to our needs
	 */

	/* region 1: command table area (MVS_ATA_CMD_SZ bytes) ************** */
	buf_cmd = buf_tmp = slot->buf;
	buf_tmp_dma = slot->buf_dma;

	hdr->cmd_tbl = cpu_to_le64(buf_tmp_dma);

	buf_tmp += MVS_ATA_CMD_SZ;
	buf_tmp_dma += MVS_ATA_CMD_SZ;

	/* region 2: open address frame area (MVS_OAF_SZ bytes) ********* */
	/* used for STP.  unused for SATA? */
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
	i = MVS_CHIP_DISP->prd_size() * MVS_CHIP_DISP->prd_count();

	buf_tmp += i;
	buf_tmp_dma += i;

	/* region 4: status buffer (larger the PRD, smaller this buf) ****** */
	slot->response = buf_tmp;
	hdr->status_buf = cpu_to_le64(buf_tmp_dma);
	if (mvi->flags & MVF_FLAG_SOC)
		hdr->reserved[0] = 0;

	req_len = sizeof(struct host_to_dev_fis);
	resp_len = MVS_SLOT_BUF_SZ - MVS_ATA_CMD_SZ -
	    sizeof(struct mvs_err_info) - i;

	/* request, response lengths */
	resp_len = min(resp_len, max_resp_len);
	hdr->lens = cpu_to_le32(((resp_len / 4) << 16) | (req_len / 4));

	if (likely(!task->ata_task.device_control_reg_update))
		task->ata_task.fis.flags |= 0x80; /* C=1: update ATA cmd reg */
	/* fill in command FIS and ATAPI CDB */
	memcpy(buf_cmd, &task->ata_task.fis, sizeof(struct host_to_dev_fis));
	if (dev->sata_dev.class == ATA_DEV_ATAPI)
		memcpy(buf_cmd + STP_ATAPI_CMD,
			task->ata_task.atapi_packet, 16);

	/* generate open address frame hdr (first 12 bytes) */
	/* initiator, STP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PROTOCOL_STP << 4) | 0x1;
	buf_oaf[1] = min(sas_port->linkrate, dev->linkrate) & 0xf;
	*(u16 *)(buf_oaf + 2) = cpu_to_be16(mvi_dev->device_id + 1);
	memcpy(buf_oaf + 4, dev->sas_addr, SAS_ADDR_SIZE);

	/* fill in PRD (scatter/gather) table, if any */
	MVS_CHIP_DISP->make_prd(task->scatter, tei->n_elem, buf_prd);

	if (task->data_dir == DMA_FROM_DEVICE)
		MVS_CHIP_DISP->dma_fix(mvi, sas_port->phy_mask,
				TRASH_BUCKET_SIZE, tei->n_elem, buf_prd);

	return 0;
}