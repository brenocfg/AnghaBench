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
struct TYPE_4__ {TYPE_1__* ptag_state; int /*<<< orphan*/ * mcc_tag_status; int /*<<< orphan*/ * mcc_wait; } ;
struct beiscsi_hba {TYPE_2__ ctrl; int /*<<< orphan*/  state; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_dma_mem {scalar_t__ size; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag_state; struct be_dma_mem tag_mem_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_ONLINE ; 
 int /*<<< orphan*/  BEISCSI_HOST_MBX_TIMEOUT ; 
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_EH ; 
 int BEISCSI_LOG_INIT ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int MAX_MCC_CMD ; 
 int /*<<< orphan*/  MCC_TAG_STATE_RUNNING ; 
 int /*<<< orphan*/  MCC_TAG_STATE_TIMEOUT ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int __beiscsi_mcc_compl_status (struct beiscsi_hba*,unsigned int,struct be_mcc_wrb**,struct be_dma_mem*) ; 
 scalar_t__ beiscsi_hba_in_error (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mcc_wrb (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

int beiscsi_mccq_compl_wait(struct beiscsi_hba *phba,
			    unsigned int tag,
			    struct be_mcc_wrb **wrb,
			    struct be_dma_mem *mbx_cmd_mem)
{
	int rc = 0;

	if (!tag || tag > MAX_MCC_CMD) {
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : invalid tag %u\n", tag);
		return -EINVAL;
	}

	if (beiscsi_hba_in_error(phba)) {
		clear_bit(MCC_TAG_STATE_RUNNING,
			  &phba->ctrl.ptag_state[tag].tag_state);
		return -EIO;
	}

	/* wait for the mccq completion */
	rc = wait_event_interruptible_timeout(phba->ctrl.mcc_wait[tag],
					      phba->ctrl.mcc_tag_status[tag],
					      msecs_to_jiffies(
						BEISCSI_HOST_MBX_TIMEOUT));
	/**
	 * Return EIO if port is being disabled. Associated DMA memory, if any,
	 * is freed by the caller. When port goes offline, MCCQ is cleaned up
	 * so does WRB.
	 */
	if (!test_bit(BEISCSI_HBA_ONLINE, &phba->state)) {
		clear_bit(MCC_TAG_STATE_RUNNING,
			  &phba->ctrl.ptag_state[tag].tag_state);
		return -EIO;
	}

	/**
	 * If MBOX cmd timeout expired, tag and resource allocated
	 * for cmd is not freed until FW returns completion.
	 */
	if (rc <= 0) {
		struct be_dma_mem *tag_mem;

		/**
		 * PCI/DMA memory allocated and posted in non-embedded mode
		 * will have mbx_cmd_mem != NULL.
		 * Save virtual and bus addresses for the command so that it
		 * can be freed later.
		 **/
		tag_mem = &phba->ctrl.ptag_state[tag].tag_mem_state;
		if (mbx_cmd_mem) {
			tag_mem->size = mbx_cmd_mem->size;
			tag_mem->va = mbx_cmd_mem->va;
			tag_mem->dma = mbx_cmd_mem->dma;
		} else
			tag_mem->size = 0;

		/* first make tag_mem_state visible to all */
		wmb();
		set_bit(MCC_TAG_STATE_TIMEOUT,
				&phba->ctrl.ptag_state[tag].tag_state);

		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_EH |
			    BEISCSI_LOG_CONFIG,
			    "BC_%d : MBX Cmd Completion timed out\n");
		return -EBUSY;
	}

	rc = __beiscsi_mcc_compl_status(phba, tag, wrb, mbx_cmd_mem);

	free_mcc_wrb(&phba->ctrl, tag);
	return rc;
}