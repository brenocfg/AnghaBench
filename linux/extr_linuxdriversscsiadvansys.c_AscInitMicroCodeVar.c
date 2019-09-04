#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
typedef  int /*<<< orphan*/  uchar ;
struct asc_board {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {scalar_t__ overrun_dma; int /*<<< orphan*/  err_code; TYPE_1__* cfg; scalar_t__ overrun_buf; int /*<<< orphan*/  iop_base; } ;
struct TYPE_6__ {void* mcode_version; void* mcode_date; int /*<<< orphan*/  chip_scsi_id; int /*<<< orphan*/  disc_enable; int /*<<< orphan*/ * sdtr_period_offset; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_2__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_DISC_ENABLE_B ; 
 int /*<<< orphan*/  ASCV_HOSTSCSI_ID_B ; 
 scalar_t__ ASCV_MC_DATE_W ; 
 scalar_t__ ASCV_MC_VER_W ; 
 int /*<<< orphan*/  ASCV_OVERRUN_BSIZE_D ; 
 int /*<<< orphan*/  ASCV_OVERRUN_PADDR_D ; 
 int /*<<< orphan*/  ASC_IERR_SET_PC_ADDR ; 
 int /*<<< orphan*/  ASC_IERR_START_STOP_CHIP ; 
 int ASC_MAX_TID ; 
 scalar_t__ ASC_MCODE_START_ADDR ; 
 scalar_t__ ASC_OVERRUN_BSIZE ; 
 int /*<<< orphan*/  ASC_TID_TO_TARGET_ID (int /*<<< orphan*/ ) ; 
 scalar_t__ AscGetPCAddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscInitQLinkVar (TYPE_2__*) ; 
 int /*<<< orphan*/  AscMemDWordCopyPtrToLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AscPutMCodeInitSDTRAtID (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* AscReadLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetPCAddr (int /*<<< orphan*/ ,scalar_t__) ; 
 int AscStartChip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (unsigned long) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 struct asc_board* asc_dvc_to_board (TYPE_2__*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AscInitMicroCodeVar(ASC_DVC_VAR *asc_dvc)
{
	int i;
	int warn_code;
	PortAddr iop_base;
	__le32 phy_addr;
	__le32 phy_size;
	struct asc_board *board = asc_dvc_to_board(asc_dvc);

	iop_base = asc_dvc->iop_base;
	warn_code = 0;
	for (i = 0; i <= ASC_MAX_TID; i++) {
		AscPutMCodeInitSDTRAtID(iop_base, i,
					asc_dvc->cfg->sdtr_period_offset[i]);
	}

	AscInitQLinkVar(asc_dvc);
	AscWriteLramByte(iop_base, ASCV_DISC_ENABLE_B,
			 asc_dvc->cfg->disc_enable);
	AscWriteLramByte(iop_base, ASCV_HOSTSCSI_ID_B,
			 ASC_TID_TO_TARGET_ID(asc_dvc->cfg->chip_scsi_id));

	/* Ensure overrun buffer is aligned on an 8 byte boundary. */
	BUG_ON((unsigned long)asc_dvc->overrun_buf & 7);
	asc_dvc->overrun_dma = dma_map_single(board->dev, asc_dvc->overrun_buf,
					ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
	if (dma_mapping_error(board->dev, asc_dvc->overrun_dma)) {
		warn_code = -ENOMEM;
		goto err_dma_map;
	}
	phy_addr = cpu_to_le32(asc_dvc->overrun_dma);
	AscMemDWordCopyPtrToLram(iop_base, ASCV_OVERRUN_PADDR_D,
				 (uchar *)&phy_addr, 1);
	phy_size = cpu_to_le32(ASC_OVERRUN_BSIZE);
	AscMemDWordCopyPtrToLram(iop_base, ASCV_OVERRUN_BSIZE_D,
				 (uchar *)&phy_size, 1);

	asc_dvc->cfg->mcode_date =
	    AscReadLramWord(iop_base, (ushort)ASCV_MC_DATE_W);
	asc_dvc->cfg->mcode_version =
	    AscReadLramWord(iop_base, (ushort)ASCV_MC_VER_W);

	AscSetPCAddr(iop_base, ASC_MCODE_START_ADDR);
	if (AscGetPCAddr(iop_base) != ASC_MCODE_START_ADDR) {
		asc_dvc->err_code |= ASC_IERR_SET_PC_ADDR;
		warn_code = -EINVAL;
		goto err_mcode_start;
	}
	if (AscStartChip(iop_base) != 1) {
		asc_dvc->err_code |= ASC_IERR_START_STOP_CHIP;
		warn_code = -EIO;
		goto err_mcode_start;
	}

	return warn_code;

err_mcode_start:
	dma_unmap_single(board->dev, asc_dvc->overrun_dma,
			 ASC_OVERRUN_BSIZE, DMA_FROM_DEVICE);
err_dma_map:
	asc_dvc->overrun_dma = 0;
	return warn_code;
}