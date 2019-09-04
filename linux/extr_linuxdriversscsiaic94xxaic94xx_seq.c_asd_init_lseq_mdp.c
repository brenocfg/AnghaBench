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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ max_ddbs; } ;
struct asd_ha_struct {TYPE_1__ hw_prof; } ;

/* Variables and functions */
 int ASD_NOTIFY_DOWN_COUNT ; 
 int ASD_NOTIFY_TIMEOUT ; 
 scalar_t__ LSEQ_MODE5_PAGE0_OFFSET ; 
 int LSEQ_MODE_SCRATCH_SIZE ; 
 int LSEQ_PAGE_SIZE ; 
 int LmM0INTEN_MASK ; 
 scalar_t__ LmSCRATCH (int) ; 
 scalar_t__ LmSEQ_BREAK_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_CLOSE_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_COMINIT_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_COPY_SMP_CONN_TAG (int) ; 
 scalar_t__ LmSEQ_DATA_OFFSET (int) ; 
 scalar_t__ LmSEQ_DATA_TO_CSEQ (int) ; 
 scalar_t__ LmSEQ_DEVICE_BITS (int) ; 
 scalar_t__ LmSEQ_DEV_PRES_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_DISPARITY_ERROR_COUNT (int) ; 
 scalar_t__ LmSEQ_DWS_RESET_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_EMPTY_TRANS_CTX (int) ; 
 scalar_t__ LmSEQ_FAILED_OPEN_STATUS (int) ; 
 scalar_t__ LmSEQ_FIRST_INV_DDB_SITE (int) ; 
 scalar_t__ LmSEQ_FIRST_INV_SCB_SITE (int) ; 
 scalar_t__ LmSEQ_FRAME_TYPE_MASK (int) ; 
 scalar_t__ LmSEQ_HASHED_DEST_ADDR_MASK (int) ; 
 scalar_t__ LmSEQ_HASHED_SRC_ADDR_MASK (int) ; 
 scalar_t__ LmSEQ_INI_CONN_TAG (int) ; 
 scalar_t__ LmSEQ_INTEN_SAVE (int) ; 
 scalar_t__ LmSEQ_INVALID_DWORD_COUNT (int) ; 
 scalar_t__ LmSEQ_IP_BITL (int) ; 
 scalar_t__ LmSEQ_LAST_LOADED_SGE (int) ; 
 scalar_t__ LmSEQ_LAST_LOADED_SG_EL (int) ; 
 scalar_t__ LmSEQ_LINK_RESET_RETRY_COUNT (int) ; 
 scalar_t__ LmSEQ_LINK_RST_ERR (int) ; 
 scalar_t__ LmSEQ_LINK_RST_FRM_LEN (int) ; 
 scalar_t__ LmSEQ_LINK_RST_PROTOCOL (int) ; 
 scalar_t__ LmSEQ_LOSS_OF_SYNC_COUNT (int) ; 
 scalar_t__ LmSEQ_M1_EMPTY_TRANS_CTX (int) ; 
 scalar_t__ LmSEQ_M1_LAST_LOADED_SGE (int) ; 
 scalar_t__ LmSEQ_M1_RESP_STATUS (int) ; 
 scalar_t__ LmSEQ_M1_SAVE_SCBPTR (int) ; 
 scalar_t__ LmSEQ_MCTL_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_MODE_FLAGS (int) ; 
 scalar_t__ LmSEQ_NOTIFY_TIMER_DOWN_COUNT (int) ; 
 scalar_t__ LmSEQ_NOTIFY_TIMER_INITIAL_COUNT (int) ; 
 scalar_t__ LmSEQ_NOTIFY_TIMER_TIMEOUT (int) ; 
 scalar_t__ LmSEQ_NUM_LINK_RESET_RETRIES (int) ; 
 scalar_t__ LmSEQ_OOB_INT_ENABLES (int) ; 
 scalar_t__ LmSEQ_OPCODE_TO_CSEQ (int) ; 
 scalar_t__ LmSEQ_OPEN_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_P0M2_OFFS1AH (int) ; 
 scalar_t__ LmSEQ_PM_TABLE_PTR (int) ; 
 scalar_t__ LmSEQ_PORT_COUNTER (int) ; 
 scalar_t__ LmSEQ_Q_LINK_HEAD (int) ; 
 scalar_t__ LmSEQ_Q_XMIT_HEAD (int) ; 
 scalar_t__ LmSEQ_RCV_FIS_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_RCV_ID_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_REG0_MODE (int) ; 
 scalar_t__ LmSEQ_RESP_LEN (int) ; 
 scalar_t__ LmSEQ_RESP_STATUS (int) ; 
 scalar_t__ LmSEQ_RET_ADDR (int) ; 
 scalar_t__ LmSEQ_RET_ADDR1 (int) ; 
 scalar_t__ LmSEQ_RET_ADDR2 (int) ; 
 scalar_t__ LmSEQ_SAS_RESET_MODE (int) ; 
 scalar_t__ LmSEQ_SATA_INTERLOCK_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_SATA_INTERLOCK_TMR_SAVE (int) ; 
 scalar_t__ LmSEQ_SAVED_OOB_MODE (int) ; 
 scalar_t__ LmSEQ_SAVED_OOB_SIGNALS (int) ; 
 scalar_t__ LmSEQ_SAVED_OOB_STATUS (int) ; 
 scalar_t__ LmSEQ_SAVE_SCBPTR (int) ; 
 scalar_t__ LmSEQ_SDB_CURR_TAG (int) ; 
 scalar_t__ LmSEQ_SDB_DDB (int) ; 
 scalar_t__ LmSEQ_SDB_NUM_TAGS (int) ; 
 scalar_t__ LmSEQ_SMP_RCV_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_SRST_AS_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_STP_SHUTDOWN_TIMER_TERM_TS (int) ; 
 scalar_t__ LmSEQ_TX_ID_ADDR_FRAME (int) ; 
 scalar_t__ LmSEQ_XMIT_REQUEST_TYPE (int) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,scalar_t__,int) ; 
 scalar_t__ last_scb_site_no ; 
 int mode2_task ; 

__attribute__((used)) static void asd_init_lseq_mdp(struct asd_ha_struct *asd_ha,  int lseq)
{
	int    i;
	u32    moffs;
	u16 ret_addr[] = {
		0xFFFF,		  /* mode 0 */
		0xFFFF,		  /* mode 1 */
		mode2_task,	  /* mode 2 */
		0,
		0xFFFF,		  /* mode 4/5 */
		0xFFFF,		  /* mode 4/5 */
	};

	/*
	 * Mode 0,1,2 and 4/5 have common field on page 0 for the first
	 * 14 bytes.
	 */
	for (i = 0; i < 3; i++) {
		moffs = i * LSEQ_MODE_SCRATCH_SIZE;
		asd_write_reg_word(asd_ha, LmSEQ_RET_ADDR(lseq)+moffs,
				   ret_addr[i]);
		asd_write_reg_word(asd_ha, LmSEQ_REG0_MODE(lseq)+moffs, 0);
		asd_write_reg_word(asd_ha, LmSEQ_MODE_FLAGS(lseq)+moffs, 0);
		asd_write_reg_word(asd_ha, LmSEQ_RET_ADDR2(lseq)+moffs,0xFFFF);
		asd_write_reg_word(asd_ha, LmSEQ_RET_ADDR1(lseq)+moffs,0xFFFF);
		asd_write_reg_byte(asd_ha, LmSEQ_OPCODE_TO_CSEQ(lseq)+moffs,0);
		asd_write_reg_word(asd_ha, LmSEQ_DATA_TO_CSEQ(lseq)+moffs,0);
	}
	/*
	 *  Mode 5 page 0 overlaps the same scratch page with Mode 0 page 3.
	 */
	asd_write_reg_word(asd_ha,
			 LmSEQ_RET_ADDR(lseq)+LSEQ_MODE5_PAGE0_OFFSET,
			   ret_addr[5]);
	asd_write_reg_word(asd_ha,
			 LmSEQ_REG0_MODE(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0);
	asd_write_reg_word(asd_ha,
			 LmSEQ_MODE_FLAGS(lseq)+LSEQ_MODE5_PAGE0_OFFSET, 0);
	asd_write_reg_word(asd_ha,
			 LmSEQ_RET_ADDR2(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0xFFFF);
	asd_write_reg_word(asd_ha,
			 LmSEQ_RET_ADDR1(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0xFFFF);
	asd_write_reg_byte(asd_ha,
		         LmSEQ_OPCODE_TO_CSEQ(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0);
	asd_write_reg_word(asd_ha,
		         LmSEQ_DATA_TO_CSEQ(lseq)+LSEQ_MODE5_PAGE0_OFFSET, 0);

	/* LSEQ Mode dependent 0, page 0 setup. */
	asd_write_reg_word(asd_ha, LmSEQ_FIRST_INV_DDB_SITE(lseq),
			   (u16)asd_ha->hw_prof.max_ddbs);
	asd_write_reg_word(asd_ha, LmSEQ_EMPTY_TRANS_CTX(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_RESP_LEN(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_FIRST_INV_SCB_SITE(lseq),
			   (u16)last_scb_site_no+1);
	asd_write_reg_word(asd_ha, LmSEQ_INTEN_SAVE(lseq),
			    (u16) ((LmM0INTEN_MASK & 0xFFFF0000) >> 16));
	asd_write_reg_word(asd_ha, LmSEQ_INTEN_SAVE(lseq) + 2,
			    (u16) LmM0INTEN_MASK & 0xFFFF);
	asd_write_reg_byte(asd_ha, LmSEQ_LINK_RST_FRM_LEN(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_LINK_RST_PROTOCOL(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_RESP_STATUS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_LAST_LOADED_SGE(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_SAVE_SCBPTR(lseq), 0);

	/* LSEQ mode dependent, mode 1, page 0 setup. */
	asd_write_reg_word(asd_ha, LmSEQ_Q_XMIT_HEAD(lseq), 0xFFFF);
	asd_write_reg_word(asd_ha, LmSEQ_M1_EMPTY_TRANS_CTX(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_INI_CONN_TAG(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_FAILED_OPEN_STATUS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_XMIT_REQUEST_TYPE(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_M1_RESP_STATUS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_M1_LAST_LOADED_SGE(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_M1_SAVE_SCBPTR(lseq), 0);

	/* LSEQ Mode dependent mode 2, page 0 setup */
	asd_write_reg_word(asd_ha, LmSEQ_PORT_COUNTER(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_PM_TABLE_PTR(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_SATA_INTERLOCK_TMR_SAVE(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_IP_BITL(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_COPY_SMP_CONN_TAG(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_P0M2_OFFS1AH(lseq), 0);

	/* LSEQ Mode dependent, mode 4/5, page 0 setup. */
	asd_write_reg_byte(asd_ha, LmSEQ_SAVED_OOB_STATUS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_SAVED_OOB_MODE(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_Q_LINK_HEAD(lseq), 0xFFFF);
	asd_write_reg_byte(asd_ha, LmSEQ_LINK_RST_ERR(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_SAVED_OOB_SIGNALS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_SAS_RESET_MODE(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_LINK_RESET_RETRY_COUNT(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_NUM_LINK_RESET_RETRIES(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_OOB_INT_ENABLES(lseq), 0);
	/*
	 * Set the desired interval between transmissions of the NOTIFY
	 * (ENABLE SPINUP) primitive.  Must be initialized to val - 1.
	 */
	asd_write_reg_word(asd_ha, LmSEQ_NOTIFY_TIMER_TIMEOUT(lseq),
			   ASD_NOTIFY_TIMEOUT - 1);
	/* No delay for the first NOTIFY to be sent to the attached target. */
	asd_write_reg_word(asd_ha, LmSEQ_NOTIFY_TIMER_DOWN_COUNT(lseq),
			   ASD_NOTIFY_DOWN_COUNT);
	asd_write_reg_word(asd_ha, LmSEQ_NOTIFY_TIMER_INITIAL_COUNT(lseq),
			   ASD_NOTIFY_DOWN_COUNT);

	/* LSEQ Mode dependent, mode 0 and 1, page 1 setup. */
	for (i = 0; i < 2; i++)	{
		int j;
		/* Start from Page 1 of Mode 0 and 1. */
		moffs = LSEQ_PAGE_SIZE + i*LSEQ_MODE_SCRATCH_SIZE;
		/* All the fields of page 1 can be initialized to 0. */
		for (j = 0; j < LSEQ_PAGE_SIZE; j += 4)
			asd_write_reg_dword(asd_ha, LmSCRATCH(lseq)+moffs+j,0);
	}

	/* LSEQ Mode dependent, mode 2, page 1 setup. */
	asd_write_reg_dword(asd_ha, LmSEQ_INVALID_DWORD_COUNT(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_DISPARITY_ERROR_COUNT(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_LOSS_OF_SYNC_COUNT(lseq), 0);

	/* LSEQ Mode dependent, mode 4/5, page 1. */
	for (i = 0; i < LSEQ_PAGE_SIZE; i+=4)
		asd_write_reg_dword(asd_ha, LmSEQ_FRAME_TYPE_MASK(lseq)+i, 0);
	asd_write_reg_byte(asd_ha, LmSEQ_FRAME_TYPE_MASK(lseq), 0xFF);
	asd_write_reg_byte(asd_ha, LmSEQ_HASHED_DEST_ADDR_MASK(lseq), 0xFF);
	asd_write_reg_byte(asd_ha, LmSEQ_HASHED_DEST_ADDR_MASK(lseq)+1,0xFF);
	asd_write_reg_byte(asd_ha, LmSEQ_HASHED_DEST_ADDR_MASK(lseq)+2,0xFF);
	asd_write_reg_byte(asd_ha, LmSEQ_HASHED_SRC_ADDR_MASK(lseq), 0xFF);
	asd_write_reg_byte(asd_ha, LmSEQ_HASHED_SRC_ADDR_MASK(lseq)+1, 0xFF);
	asd_write_reg_byte(asd_ha, LmSEQ_HASHED_SRC_ADDR_MASK(lseq)+2, 0xFF);
	asd_write_reg_dword(asd_ha, LmSEQ_DATA_OFFSET(lseq), 0xFFFFFFFF);

	/* LSEQ Mode dependent, mode 0, page 2 setup. */
	asd_write_reg_dword(asd_ha, LmSEQ_SMP_RCV_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_DEVICE_BITS(lseq), 0);
	asd_write_reg_word(asd_ha, LmSEQ_SDB_DDB(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_SDB_NUM_TAGS(lseq), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_SDB_CURR_TAG(lseq), 0);

	/* LSEQ Mode Dependent 1, page 2 setup. */
	asd_write_reg_dword(asd_ha, LmSEQ_TX_ID_ADDR_FRAME(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_TX_ID_ADDR_FRAME(lseq)+4, 0);
	asd_write_reg_dword(asd_ha, LmSEQ_OPEN_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_SRST_AS_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_LAST_LOADED_SG_EL(lseq), 0);

	/* LSEQ Mode Dependent 2, page 2 setup. */
	/* The LmSEQ_STP_SHUTDOWN_TIMER_TERM_TS is IGNORED by the sequencer,
	 * i.e. always 0. */
	asd_write_reg_dword(asd_ha, LmSEQ_STP_SHUTDOWN_TIMER_TERM_TS(lseq),0);
	asd_write_reg_dword(asd_ha, LmSEQ_CLOSE_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_BREAK_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_DWS_RESET_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha,LmSEQ_SATA_INTERLOCK_TIMER_TERM_TS(lseq),0);
	asd_write_reg_dword(asd_ha, LmSEQ_MCTL_TIMER_TERM_TS(lseq), 0);

	/* LSEQ Mode Dependent 4/5, page 2 setup. */
	asd_write_reg_dword(asd_ha, LmSEQ_COMINIT_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_RCV_ID_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_RCV_FIS_TIMER_TERM_TS(lseq), 0);
	asd_write_reg_dword(asd_ha, LmSEQ_DEV_PRES_TIMER_TERM_TS(lseq),	0);
}