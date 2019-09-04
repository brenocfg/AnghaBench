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
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct scatterlist {int dummy; } ;
struct iscsi_task {TYPE_2__* hdr; struct scsi_cmnd* sc; struct beiscsi_io_task* dd_data; } ;
struct beiscsi_io_task {int num_sg; int /*<<< orphan*/  libiscsi_itt; TYPE_4__* cmd_bhs; struct scsi_cmnd* scsi_cmnd; TYPE_1__* conn; } ;
struct beiscsi_hba {int (* iotask_fn ) (struct iscsi_task*,struct scatterlist*,int,unsigned int,unsigned int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  itt; } ;
struct TYPE_8__ {TYPE_3__ iscsi_hdr; } ;
struct TYPE_6__ {scalar_t__ exp_statsn; } ;
struct TYPE_5__ {int /*<<< orphan*/  login_in_progress; struct beiscsi_hba* phba; } ;

/* Variables and functions */
 int BEISCSI_LOG_IO ; 
 int BEISCSI_LOG_ISCSI ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_hba_is_online (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int beiscsi_mtask (struct iscsi_task*) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_dma_map (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int stub1 (struct iscsi_task*,struct scatterlist*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int beiscsi_task_xmit(struct iscsi_task *task)
{
	struct beiscsi_io_task *io_task = task->dd_data;
	struct scsi_cmnd *sc = task->sc;
	struct beiscsi_hba *phba;
	struct scatterlist *sg;
	int num_sg;
	unsigned int  writedir = 0, xferlen = 0;

	phba = io_task->conn->phba;
	/**
	 * HBA in error includes BEISCSI_HBA_FW_TIMEOUT. IO path might be
	 * operational if FW still gets heartbeat from EP FW. Is management
	 * path really needed to continue further?
	 */
	if (!beiscsi_hba_is_online(phba))
		return -EIO;

	if (!io_task->conn->login_in_progress)
		task->hdr->exp_statsn = 0;

	if (!sc)
		return beiscsi_mtask(task);

	io_task->scsi_cmnd = sc;
	io_task->num_sg = 0;
	num_sg = scsi_dma_map(sc);
	if (num_sg < 0) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_IO | BEISCSI_LOG_ISCSI,
			    "BM_%d : scsi_dma_map Failed "
			    "Driver_ITT : 0x%x ITT : 0x%x Xferlen : 0x%x\n",
			    be32_to_cpu(io_task->cmd_bhs->iscsi_hdr.itt),
			    io_task->libiscsi_itt, scsi_bufflen(sc));

		return num_sg;
	}
	/**
	 * For scsi cmd task, check num_sg before unmapping in cleanup_task.
	 * For management task, cleanup_task checks mtask_addr before unmapping.
	 */
	io_task->num_sg = num_sg;
	xferlen = scsi_bufflen(sc);
	sg = scsi_sglist(sc);
	if (sc->sc_data_direction == DMA_TO_DEVICE)
		writedir = 1;
	else
		writedir = 0;

	return phba->iotask_fn(task, sg, num_sg, xferlen, writedir);
}