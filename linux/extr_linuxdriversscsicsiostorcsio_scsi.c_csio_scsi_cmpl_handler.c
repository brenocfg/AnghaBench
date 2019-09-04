#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_scsi_read_wr {scalar_t__ cookie; } ;
struct fw_scsi_abrt_cls_wr {scalar_t__ cookie; } ;
struct csio_scsim {int dummy; } ;
struct csio_ioreq {scalar_t__ wr_status; } ;
struct csio_hw {int dummy; } ;
struct csio_fl_dma_buf {int dummy; } ;
struct cpl_fw6_msg {scalar_t__ opcode; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ CPL_FW6_MSG ; 
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
 scalar_t__ FW_SCSI_ABRT_CLS_WR ; 
 scalar_t__ FW_SCSI_CMD_WR ; 
 scalar_t__ FW_SCSI_READ_WR ; 
 scalar_t__ FW_SCSI_WRITE_WR ; 
 struct csio_scsim* csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_warn (struct csio_hw*,char*,scalar_t__) ; 
 scalar_t__ csio_wr_status (scalar_t__*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  n_inval_cplop ; 
 int /*<<< orphan*/  n_inval_scsiop ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_addr_valid (struct csio_ioreq*) ; 

struct csio_ioreq *
csio_scsi_cmpl_handler(struct csio_hw *hw, void *wr, uint32_t len,
		     struct csio_fl_dma_buf *flb, void *priv, uint8_t **scsiwr)
{
	struct csio_ioreq *ioreq = NULL;
	struct cpl_fw6_msg *cpl;
	uint8_t *tempwr;
	uint8_t	status;
	struct csio_scsim *scm = csio_hw_to_scsim(hw);

	/* skip RSS header */
	cpl = (struct cpl_fw6_msg *)((uintptr_t)wr + sizeof(__be64));

	if (unlikely(cpl->opcode != CPL_FW6_MSG)) {
		csio_warn(hw, "Error: Invalid CPL msg %x recvd on SCSI q\n",
			  cpl->opcode);
		CSIO_INC_STATS(scm, n_inval_cplop);
		return NULL;
	}

	tempwr = (uint8_t *)(cpl->data);
	status = csio_wr_status(tempwr);
	*scsiwr = tempwr;

	if (likely((*tempwr == FW_SCSI_READ_WR) ||
			(*tempwr == FW_SCSI_WRITE_WR) ||
			(*tempwr == FW_SCSI_CMD_WR))) {
		ioreq = (struct csio_ioreq *)((uintptr_t)
				 (((struct fw_scsi_read_wr *)tempwr)->cookie));
		CSIO_DB_ASSERT(virt_addr_valid(ioreq));

		ioreq->wr_status = status;

		return ioreq;
	}

	if (*tempwr == FW_SCSI_ABRT_CLS_WR) {
		ioreq = (struct csio_ioreq *)((uintptr_t)
			 (((struct fw_scsi_abrt_cls_wr *)tempwr)->cookie));
		CSIO_DB_ASSERT(virt_addr_valid(ioreq));

		ioreq->wr_status = status;
		return ioreq;
	}

	csio_warn(hw, "WR with invalid opcode in SCSI IQ: %x\n", *tempwr);
	CSIO_INC_STATS(scm, n_inval_scsiop);
	return NULL;
}