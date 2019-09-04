#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
typedef  int uchar ;
struct TYPE_6__ {scalar_t__ chip_type; scalar_t__ err_code; int /*<<< orphan*/  iop_base; } ;
typedef  int /*<<< orphan*/  AdvPortAddr ;
typedef  TYPE_1__ ADV_DVC_VAR ;

/* Variables and functions */
 scalar_t__ ADV_CHIP_ASC38C0800 ; 
 scalar_t__ ADV_CHIP_ASC38C1600 ; 
 int /*<<< orphan*/  ADV_CTRL_REG_CMD_RESET ; 
 int /*<<< orphan*/  ADV_CTRL_REG_CMD_WR_IO_REG ; 
 int ADV_FALSE ; 
 int ADV_MAX_TID ; 
 int /*<<< orphan*/  ADV_RISC_CSR_STOP ; 
 int ADV_TRUE ; 
 int /*<<< orphan*/  ASC_MC_BIOS_SIGNATURE ; 
 scalar_t__ ASC_MC_NUMBER_OF_MAX_CMD ; 
 int /*<<< orphan*/  ASC_MC_PPR_ABLE ; 
 int /*<<< orphan*/  ASC_MC_SDTR_ABLE ; 
 int /*<<< orphan*/  ASC_MC_TAGQNG_ABLE ; 
 int /*<<< orphan*/  ASC_MC_WDTR_ABLE ; 
 int AdvInitAsc3550Driver (TYPE_1__*) ; 
 int AdvInitAsc38C0800Driver (TYPE_1__*) ; 
 int AdvInitAsc38C1600Driver (TYPE_1__*) ; 
 int /*<<< orphan*/  AdvReadByteLram (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  AdvReadWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AdvWriteByteLram (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  AdvWriteWordLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AdvWriteWordRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOPW_CTRL_REG ; 
 int /*<<< orphan*/  IOPW_RISC_CSR ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int AdvResetChipAndSB(ADV_DVC_VAR *asc_dvc)
{
	int status;
	ushort wdtr_able, sdtr_able, tagqng_able;
	ushort ppr_able = 0;
	uchar tid, max_cmd[ADV_MAX_TID + 1];
	AdvPortAddr iop_base;
	ushort bios_sig;

	iop_base = asc_dvc->iop_base;

	/*
	 * Save current per TID negotiated values.
	 */
	AdvReadWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvReadWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		AdvReadWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	}
	AdvReadWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	for (tid = 0; tid <= ADV_MAX_TID; tid++) {
		AdvReadByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				max_cmd[tid]);
	}

	/*
	 * Force the AdvInitAsc3550/38C0800Driver() function to
	 * perform a SCSI Bus Reset by clearing the BIOS signature word.
	 * The initialization functions assumes a SCSI Bus Reset is not
	 * needed if the BIOS signature word is present.
	 */
	AdvReadWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, bios_sig);
	AdvWriteWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, 0);

	/*
	 * Stop chip and reset it.
	 */
	AdvWriteWordRegister(iop_base, IOPW_RISC_CSR, ADV_RISC_CSR_STOP);
	AdvWriteWordRegister(iop_base, IOPW_CTRL_REG, ADV_CTRL_REG_CMD_RESET);
	mdelay(100);
	AdvWriteWordRegister(iop_base, IOPW_CTRL_REG,
			     ADV_CTRL_REG_CMD_WR_IO_REG);

	/*
	 * Reset Adv Library error code, if any, and try
	 * re-initializing the chip.
	 */
	asc_dvc->err_code = 0;
	if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		status = AdvInitAsc38C1600Driver(asc_dvc);
	} else if (asc_dvc->chip_type == ADV_CHIP_ASC38C0800) {
		status = AdvInitAsc38C0800Driver(asc_dvc);
	} else {
		status = AdvInitAsc3550Driver(asc_dvc);
	}

	/* Translate initialization return value to status value. */
	if (status == 0) {
		status = ADV_TRUE;
	} else {
		status = ADV_FALSE;
	}

	/*
	 * Restore the BIOS signature word.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_BIOS_SIGNATURE, bios_sig);

	/*
	 * Restore per TID negotiated values.
	 */
	AdvWriteWordLram(iop_base, ASC_MC_WDTR_ABLE, wdtr_able);
	AdvWriteWordLram(iop_base, ASC_MC_SDTR_ABLE, sdtr_able);
	if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		AdvWriteWordLram(iop_base, ASC_MC_PPR_ABLE, ppr_able);
	}
	AdvWriteWordLram(iop_base, ASC_MC_TAGQNG_ABLE, tagqng_able);
	for (tid = 0; tid <= ADV_MAX_TID; tid++) {
		AdvWriteByteLram(iop_base, ASC_MC_NUMBER_OF_MAX_CMD + tid,
				 max_cmd[tid]);
	}

	return status;
}