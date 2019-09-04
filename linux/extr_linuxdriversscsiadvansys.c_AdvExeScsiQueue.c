#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ target_id; void* scsiq_rptr; int /*<<< orphan*/  carr_pa; int /*<<< orphan*/  carr_va; int /*<<< orphan*/  srb_tag; void* scsiq_ptr; int /*<<< orphan*/  done_status; int /*<<< orphan*/  host_status; } ;
struct TYPE_9__ {int /*<<< orphan*/  req_addr; TYPE_2__ scsi_req_q; } ;
typedef  TYPE_1__ adv_req_t ;
struct TYPE_12__ {int /*<<< orphan*/  carr_pa; int /*<<< orphan*/  next_vpa; void* areq_vpa; int /*<<< orphan*/  carr_va; } ;
struct TYPE_11__ {scalar_t__ chip_type; TYPE_4__* icq_sp; int /*<<< orphan*/  carr_pending_cnt; int /*<<< orphan*/  iop_base; } ;
typedef  int /*<<< orphan*/  AdvPortAddr ;
typedef  TYPE_2__ ADV_SCSI_REQ_Q ;
typedef  TYPE_3__ ADV_DVC_VAR ;
typedef  TYPE_4__ ADV_CARR_T ;

/* Variables and functions */
 int ADV_BUSY ; 
 scalar_t__ ADV_CHIP_ASC3550 ; 
 scalar_t__ ADV_CHIP_ASC38C0800 ; 
 scalar_t__ ADV_CHIP_ASC38C1600 ; 
 int ADV_ERROR ; 
 scalar_t__ ADV_MAX_TID ; 
 int ADV_SUCCESS ; 
 int /*<<< orphan*/  ADV_TICKLE_A ; 
 int /*<<< orphan*/  ADV_TICKLE_NOP ; 
 int /*<<< orphan*/  ASC_DBG (int,char*) ; 
 int /*<<< orphan*/  AdvWriteByteRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdvWriteDWordRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOPB_TICKLE ; 
 int /*<<< orphan*/  IOPDW_COMMA ; 
 int /*<<< orphan*/  QD_WITH_ERROR ; 
 int /*<<< orphan*/  QHSTA_M_INVALID_DEVICE ; 
 TYPE_4__* adv_get_next_carrier (TYPE_3__*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AdvExeScsiQueue(ADV_DVC_VAR *asc_dvc, adv_req_t *reqp)
{
	AdvPortAddr iop_base;
	ADV_CARR_T *new_carrp;
	ADV_SCSI_REQ_Q *scsiq = &reqp->scsi_req_q;

	/*
	 * The ADV_SCSI_REQ_Q 'target_id' field should never exceed ADV_MAX_TID.
	 */
	if (scsiq->target_id > ADV_MAX_TID) {
		scsiq->host_status = QHSTA_M_INVALID_DEVICE;
		scsiq->done_status = QD_WITH_ERROR;
		return ADV_ERROR;
	}

	iop_base = asc_dvc->iop_base;

	/*
	 * Allocate a carrier ensuring at least one carrier always
	 * remains on the freelist and initialize fields.
	 */
	new_carrp = adv_get_next_carrier(asc_dvc);
	if (!new_carrp) {
		ASC_DBG(1, "No free carriers\n");
		return ADV_BUSY;
	}

	asc_dvc->carr_pending_cnt++;

	/* Save virtual and physical address of ADV_SCSI_REQ_Q and carrier. */
	scsiq->scsiq_ptr = cpu_to_le32(scsiq->srb_tag);
	scsiq->scsiq_rptr = cpu_to_le32(reqp->req_addr);

	scsiq->carr_va = asc_dvc->icq_sp->carr_va;
	scsiq->carr_pa = asc_dvc->icq_sp->carr_pa;

	/*
	 * Use the current stopper to send the ADV_SCSI_REQ_Q command to
	 * the microcode. The newly allocated stopper will become the new
	 * stopper.
	 */
	asc_dvc->icq_sp->areq_vpa = scsiq->scsiq_rptr;

	/*
	 * Set the 'next_vpa' pointer for the old stopper to be the
	 * physical address of the new stopper. The RISC can only
	 * follow physical addresses.
	 */
	asc_dvc->icq_sp->next_vpa = new_carrp->carr_pa;

	/*
	 * Set the host adapter stopper pointer to point to the new carrier.
	 */
	asc_dvc->icq_sp = new_carrp;

	if (asc_dvc->chip_type == ADV_CHIP_ASC3550 ||
	    asc_dvc->chip_type == ADV_CHIP_ASC38C0800) {
		/*
		 * Tickle the RISC to tell it to read its Command Queue Head pointer.
		 */
		AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_A);
		if (asc_dvc->chip_type == ADV_CHIP_ASC3550) {
			/*
			 * Clear the tickle value. In the ASC-3550 the RISC flag
			 * command 'clr_tickle_a' does not work unless the host
			 * value is cleared.
			 */
			AdvWriteByteRegister(iop_base, IOPB_TICKLE,
					     ADV_TICKLE_NOP);
		}
	} else if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		/*
		 * Notify the RISC a carrier is ready by writing the physical
		 * address of the new carrier stopper to the COMMA register.
		 */
		AdvWriteDWordRegister(iop_base, IOPDW_COMMA,
				      le32_to_cpu(new_carrp->carr_pa));
	}

	return ADV_SUCCESS;
}