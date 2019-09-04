#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* Status; } ;
struct scsi_cmnd {int result; TYPE_1__ SCp; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_8__ {unsigned int BaseAddress; int msgout_len; struct scsi_cmnd* CurrentSC; struct Scsi_Host* Host; } ;
typedef  TYPE_2__ nsp32_hw_data ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned short AUTOSCSI_BUSY ; 
 int /*<<< orphan*/  BM_CNT ; 
 unsigned char BUSMON_PHASE_MASK ; 
#define  BUSPHASE_DATA_IN 131 
#define  BUSPHASE_DATA_OUT 130 
#define  BUSPHASE_MESSAGE_IN 129 
#define  BUSPHASE_STATUS 128 
 unsigned short BUS_FREE_OCCUER ; 
 unsigned short COMMAND_PHASE ; 
 unsigned short DATA_IN_PHASE ; 
 unsigned short DATA_OUT_PHASE ; 
 int DID_BAD_TARGET ; 
 int DID_RESET ; 
 int DID_TIME_OUT ; 
 int /*<<< orphan*/  FIFO_REST_CNT ; 
 unsigned short FIFO_REST_MASK ; 
 unsigned short ILLEGAL_PHASE ; 
 unsigned short IRQSTATUS_ANY_IRQ ; 
 unsigned short IRQSTATUS_AUTOSCSI_IRQ ; 
 unsigned short IRQSTATUS_BMCNTERR_IRQ ; 
 unsigned short IRQSTATUS_FIFO_SHLD_IRQ ; 
 unsigned short IRQSTATUS_PCI_IRQ ; 
 unsigned short IRQSTATUS_PHASE_CHANGE_IRQ ; 
 unsigned short IRQSTATUS_SCSIRESET_IRQ ; 
 unsigned short IRQSTATUS_TIMER_IRQ ; 
 int /*<<< orphan*/  IRQ_CONTROL ; 
 int /*<<< orphan*/  IRQ_CONTROL_ALL_IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned short MSGOUT_PHASE ; 
 unsigned short MSG_IN_OCCUER ; 
 unsigned short MSG_OUT_OCCUER ; 
 int /*<<< orphan*/  NEGATE ; 
 int /*<<< orphan*/  NSP32_DEBUG_INTR ; 
 int /*<<< orphan*/  SACK_CNT ; 
 int /*<<< orphan*/  SAVED_SACK_CNT ; 
 int /*<<< orphan*/  SCSI_BUS_MONITOR ; 
 int /*<<< orphan*/  SCSI_CSB_IN ; 
 int /*<<< orphan*/  SCSI_EXECUTE_PHASE ; 
 unsigned short SELECTION_TIMEOUT ; 
 int /*<<< orphan*/  SGT_ADR ; 
 unsigned short STATUS_PHASE ; 
 int /*<<< orphan*/  TIMER_SET ; 
 int /*<<< orphan*/  TIMER_STOP ; 
 int /*<<< orphan*/  TRANSFER_STATUS ; 
 int TRUE ; 
 int nsp32_busfree_occur (struct scsi_cmnd*,unsigned short) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp32_do_bus_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp32_msgin_occur (struct scsi_cmnd*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  nsp32_msgout_occur (struct scsi_cmnd*) ; 
 void* nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned short nsp32_read2 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_read4 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_sack_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  nsp32_sack_negate (TYPE_2__*) ; 
 int /*<<< orphan*/  nsp32_scsi_done (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_wait_req (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_autophase (unsigned short) ; 
 int /*<<< orphan*/  show_busphase (unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t do_nsp32_isr(int irq, void *dev_id)
{
	nsp32_hw_data *data = dev_id;
	unsigned int base = data->BaseAddress;
	struct scsi_cmnd *SCpnt = data->CurrentSC;
	unsigned short auto_stat, irq_stat, trans_stat;
	unsigned char busmon, busphase;
	unsigned long flags;
	int ret;
	int handled = 0;
	struct Scsi_Host *host = data->Host;

	spin_lock_irqsave(host->host_lock, flags);

	/*
	 * IRQ check, then enable IRQ mask
	 */
	irq_stat = nsp32_read2(base, IRQ_STATUS);
	nsp32_dbg(NSP32_DEBUG_INTR, 
		  "enter IRQ: %d, IRQstatus: 0x%x", irq, irq_stat);
	/* is this interrupt comes from Ninja asic? */
	if ((irq_stat & IRQSTATUS_ANY_IRQ) == 0) {
		nsp32_dbg(NSP32_DEBUG_INTR, "shared interrupt: irq other 0x%x", irq_stat);
		goto out2;
	}
	handled = 1;
	nsp32_write2(base, IRQ_CONTROL, IRQ_CONTROL_ALL_IRQ_MASK);

	busmon = nsp32_read1(base, SCSI_BUS_MONITOR);
	busphase = busmon & BUSMON_PHASE_MASK;

	trans_stat = nsp32_read2(base, TRANSFER_STATUS);
	if ((irq_stat == 0xffff) && (trans_stat == 0xffff)) {
		nsp32_msg(KERN_INFO, "card disconnect");
		if (data->CurrentSC != NULL) {
			nsp32_msg(KERN_INFO, "clean up current SCSI command");
			SCpnt->result = DID_BAD_TARGET << 16;
			nsp32_scsi_done(SCpnt);
		}
		goto out;
	}

	/* Timer IRQ */
	if (irq_stat & IRQSTATUS_TIMER_IRQ) {
		nsp32_dbg(NSP32_DEBUG_INTR, "timer stop");
		nsp32_write2(base, TIMER_SET, TIMER_STOP);
		goto out;
	}

	/* SCSI reset */
	if (irq_stat & IRQSTATUS_SCSIRESET_IRQ) {
		nsp32_msg(KERN_INFO, "detected someone do bus reset");
		nsp32_do_bus_reset(data);
		if (SCpnt != NULL) {
			SCpnt->result = DID_RESET << 16;
			nsp32_scsi_done(SCpnt);
		}
		goto out;
	}

	if (SCpnt == NULL) {
		nsp32_msg(KERN_WARNING, "SCpnt==NULL this can't be happened");
		nsp32_msg(KERN_WARNING, "irq_stat=0x%x trans_stat=0x%x", irq_stat, trans_stat);
		goto out;
	}

	/*
	 * AutoSCSI Interrupt.
	 * Note: This interrupt is occurred when AutoSCSI is finished.  Then
	 * check SCSIEXECUTEPHASE, and do appropriate action.  Each phases are
	 * recorded when AutoSCSI sequencer has been processed.
	 */
	if(irq_stat & IRQSTATUS_AUTOSCSI_IRQ) {
		/* getting SCSI executed phase */
		auto_stat = nsp32_read2(base, SCSI_EXECUTE_PHASE);
		nsp32_write2(base, SCSI_EXECUTE_PHASE, 0);

		/* Selection Timeout, go busfree phase. */
		if (auto_stat & SELECTION_TIMEOUT) {
			nsp32_dbg(NSP32_DEBUG_INTR,
				  "selection timeout occurred");

			SCpnt->result = DID_TIME_OUT << 16;
			nsp32_scsi_done(SCpnt);
			goto out;
		}

		if (auto_stat & MSGOUT_PHASE) {
			/*
			 * MsgOut phase was processed.
			 * If MSG_IN_OCCUER is not set, then MsgOut phase is
			 * completed. Thus, msgout_len must reset.  Otherwise,
			 * nothing to do here. If MSG_OUT_OCCUER is occurred,
			 * then we will encounter the condition and check.
			 */
			if (!(auto_stat & MSG_IN_OCCUER) &&
			     (data->msgout_len <= 3)) {
				/*
				 * !MSG_IN_OCCUER && msgout_len <=3
				 *   ---> AutoSCSI with MSGOUTreg is processed.
				 */
				data->msgout_len = 0;
			};

			nsp32_dbg(NSP32_DEBUG_INTR, "MsgOut phase processed");
		}

		if ((auto_stat & DATA_IN_PHASE) &&
		    (scsi_get_resid(SCpnt) > 0) &&
		    ((nsp32_read2(base, FIFO_REST_CNT) & FIFO_REST_MASK) != 0)) {
			printk( "auto+fifo\n");
			//nsp32_pio_read(SCpnt);
		}

		if (auto_stat & (DATA_IN_PHASE | DATA_OUT_PHASE)) {
			/* DATA_IN_PHASE/DATA_OUT_PHASE was processed. */
			nsp32_dbg(NSP32_DEBUG_INTR,
				  "Data in/out phase processed");

			/* read BMCNT, SGT pointer addr */
			nsp32_dbg(NSP32_DEBUG_INTR, "BMCNT=0x%lx", 
				    nsp32_read4(base, BM_CNT));
			nsp32_dbg(NSP32_DEBUG_INTR, "addr=0x%lx", 
				    nsp32_read4(base, SGT_ADR));
			nsp32_dbg(NSP32_DEBUG_INTR, "SACK=0x%lx", 
				    nsp32_read4(base, SACK_CNT));
			nsp32_dbg(NSP32_DEBUG_INTR, "SSACK=0x%lx", 
				    nsp32_read4(base, SAVED_SACK_CNT));

			scsi_set_resid(SCpnt, 0); /* all data transferred! */
		}

		/*
		 * MsgIn Occur
		 */
		if (auto_stat & MSG_IN_OCCUER) {
			nsp32_msgin_occur(SCpnt, irq_stat, auto_stat);
		}

		/*
		 * MsgOut Occur
		 */
		if (auto_stat & MSG_OUT_OCCUER) {
			nsp32_msgout_occur(SCpnt);
		}

		/*
		 * Bus Free Occur
		 */
		if (auto_stat & BUS_FREE_OCCUER) {
			ret = nsp32_busfree_occur(SCpnt, auto_stat);
			if (ret == TRUE) {
				goto out;
			}
		}

		if (auto_stat & STATUS_PHASE) {
			/*
			 * Read CSB and substitute CSB for SCpnt->result
			 * to save status phase stutas byte.
			 * scsi error handler checks host_byte (DID_*:
			 * low level driver to indicate status), then checks 
			 * status_byte (SCSI status byte).
			 */
			SCpnt->result =	(int)nsp32_read1(base, SCSI_CSB_IN);
		}

		if (auto_stat & ILLEGAL_PHASE) {
			/* Illegal phase is detected. SACK is not back. */
			nsp32_msg(KERN_WARNING, 
				  "AUTO SCSI ILLEGAL PHASE OCCUR!!!!");

			/* TODO: currently we don't have any action... bus reset? */

			/*
			 * To send back SACK, assert, wait, and negate.
			 */
			nsp32_sack_assert(data);
			nsp32_wait_req(data, NEGATE);
			nsp32_sack_negate(data);

		}

		if (auto_stat & COMMAND_PHASE) {
			/* nothing to do */
			nsp32_dbg(NSP32_DEBUG_INTR, "Command phase processed");
		}

		if (auto_stat & AUTOSCSI_BUSY) {
			/* AutoSCSI is running */
		}

		show_autophase(auto_stat);
	}

	/* FIFO_SHLD_IRQ */
	if (irq_stat & IRQSTATUS_FIFO_SHLD_IRQ) {
		nsp32_dbg(NSP32_DEBUG_INTR, "FIFO IRQ");

		switch(busphase) {
		case BUSPHASE_DATA_OUT:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/write");

			//nsp32_pio_write(SCpnt);

			break;

		case BUSPHASE_DATA_IN:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/read");

			//nsp32_pio_read(SCpnt);

			break;

		case BUSPHASE_STATUS:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/status");

			SCpnt->SCp.Status = nsp32_read1(base, SCSI_CSB_IN);

			break;
		default:
			nsp32_dbg(NSP32_DEBUG_INTR, "fifo/other phase");
			nsp32_dbg(NSP32_DEBUG_INTR, "irq_stat=0x%x trans_stat=0x%x", irq_stat, trans_stat);
			show_busphase(busphase);
			break;
		}

		goto out;
	}

	/* Phase Change IRQ */
	if (irq_stat & IRQSTATUS_PHASE_CHANGE_IRQ) {
		nsp32_dbg(NSP32_DEBUG_INTR, "phase change IRQ");

		switch(busphase) {
		case BUSPHASE_MESSAGE_IN:
			nsp32_dbg(NSP32_DEBUG_INTR, "phase chg/msg in");
			nsp32_msgin_occur(SCpnt, irq_stat, 0);
			break;
		default:
			nsp32_msg(KERN_WARNING, "phase chg/other phase?");
			nsp32_msg(KERN_WARNING, "irq_stat=0x%x trans_stat=0x%x\n",
				  irq_stat, trans_stat);
			show_busphase(busphase);
			break;
		}
		goto out;
	}

	/* PCI_IRQ */
	if (irq_stat & IRQSTATUS_PCI_IRQ) {
		nsp32_dbg(NSP32_DEBUG_INTR, "PCI IRQ occurred");
		/* Do nothing */
	}

	/* BMCNTERR_IRQ */
	if (irq_stat & IRQSTATUS_BMCNTERR_IRQ) {
		nsp32_msg(KERN_ERR, "Received unexpected BMCNTERR IRQ! ");
		/*
		 * TODO: To be implemented improving bus master
		 * transfer reliability when BMCNTERR is occurred in
		 * AutoSCSI phase described in specification.
		 */
	}

#if 0
	nsp32_dbg(NSP32_DEBUG_INTR,
		  "irq_stat=0x%x trans_stat=0x%x", irq_stat, trans_stat);
	show_busphase(busphase);
#endif

 out:
	/* disable IRQ mask */
	nsp32_write2(base, IRQ_CONTROL, 0);

 out2:
	spin_unlock_irqrestore(host->host_lock, flags);

	nsp32_dbg(NSP32_DEBUG_INTR, "exit");

	return IRQ_RETVAL(handled);
}