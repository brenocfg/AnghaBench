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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;
typedef  int u16 ;
struct ScsiReqBlk {int state; unsigned int total_xfer_length; TYPE_2__* dcb; int /*<<< orphan*/  status; TYPE_3__* cmd; } ;
struct AdapterCtlBlk {int dummy; } ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int sync_period; } ;
struct TYPE_4__ {scalar_t__ lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DBG_KG ; 
 unsigned int DC395x_read32 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int PARITYERROR ; 
 int /*<<< orphan*/  PARITY_ERROR ; 
 int PHASEMASK ; 
 int PH_DATA_IN ; 
 int SCSIXFERCNT_2_ZERO ; 
 int SRB_XFERPAD ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CXCNT ; 
 int /*<<< orphan*/  TRM_S1040_DMA_FIFOCNT ; 
 int /*<<< orphan*/  TRM_S1040_DMA_FIFOSTAT ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COUNTER ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_FIFOCNT ; 
 int WIDE_SYNC ; 
 int /*<<< orphan*/  cleanup_after_transfer (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  sg_update_list (struct ScsiReqBlk*,unsigned int) ; 

__attribute__((used)) static void data_in_phase0(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	u16 scsi_status = *pscsi_status;

	dprintkdbg(DBG_0, "data_in_phase0: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);

	/*
	 * KG: DataIn is much more tricky than DataOut. When the device is finished
	 * and switches to another phase, the SCSI engine should be finished too.
	 * But: There might still be bytes left in its FIFO to be fetched by the DMA
	 * engine and transferred to memory.
	 * We should wait for the FIFOs to be emptied by that (is there any way to 
	 * enforce this?) and then stop the DMA engine, because it might think, that
	 * there are more bytes to follow. Yes, the device might disconnect prior to
	 * having all bytes transferred! 
	 * Also we should make sure that all data from the DMA engine buffer's really
	 * made its way to the system memory! Some documentation on this would not
	 * seem to be a bad idea, actually.
	 */
	if (!(srb->state & SRB_XFERPAD)) {
		u32 d_left_counter;
		unsigned int sc, fc;

		if (scsi_status & PARITYERROR) {
			dprintkl(KERN_INFO, "data_in_phase0: (0x%p) "
				"Parity Error\n", srb->cmd);
			srb->status |= PARITY_ERROR;
		}
		/*
		 * KG: We should wait for the DMA FIFO to be empty ...
		 * but: it would be better to wait first for the SCSI FIFO and then the
		 * the DMA FIFO to become empty? How do we know, that the device not already
		 * sent data to the FIFO in a MsgIn phase, eg.?
		 */
		if (!(DC395x_read8(acb, TRM_S1040_DMA_FIFOSTAT) & 0x80)) {
#if 0
			int ctr = 6000000;
			dprintkl(KERN_DEBUG,
				"DIP0: Wait for DMA FIFO to flush ...\n");
			/*DC395x_write8  (TRM_S1040_DMA_CONTROL, STOPDMAXFER); */
			/*DC395x_write32 (TRM_S1040_SCSI_COUNTER, 7); */
			/*DC395x_write8  (TRM_S1040_SCSI_COMMAND, SCMD_DMA_IN); */
			while (!
			       (DC395x_read16(acb, TRM_S1040_DMA_FIFOSTAT) &
				0x80) && --ctr);
			if (ctr < 6000000 - 1)
				dprintkl(KERN_DEBUG
				       "DIP0: Had to wait for DMA ...\n");
			if (!ctr)
				dprintkl(KERN_ERR,
				       "Deadlock in DIP0 waiting for DMA FIFO empty!!\n");
			/*DC395x_write32 (TRM_S1040_SCSI_COUNTER, 0); */
#endif
			dprintkdbg(DBG_KG, "data_in_phase0: "
				"DMA{fifocnt=0x%02x fifostat=0x%02x}\n",
				DC395x_read8(acb, TRM_S1040_DMA_FIFOCNT),
				DC395x_read8(acb, TRM_S1040_DMA_FIFOSTAT));
		}
		/* Now: Check remainig data: The SCSI counters should tell us ... */
		sc = DC395x_read32(acb, TRM_S1040_SCSI_COUNTER);
		fc = DC395x_read8(acb, TRM_S1040_SCSI_FIFOCNT);
		d_left_counter = sc + ((fc & 0x1f)
		       << ((srb->dcb->sync_period & WIDE_SYNC) ? 1 :
			   0));
		dprintkdbg(DBG_KG, "data_in_phase0: "
			"SCSI{fifocnt=0x%02x%s ctr=0x%08x} "
			"DMA{fifocnt=0x%02x fifostat=0x%02x ctr=0x%08x} "
			"Remain{totxfer=%i scsi_fifo+ctr=%i}\n",
			fc,
			(srb->dcb->sync_period & WIDE_SYNC) ? "words" : "bytes",
			sc,
			fc,
			DC395x_read8(acb, TRM_S1040_DMA_FIFOSTAT),
			DC395x_read32(acb, TRM_S1040_DMA_CXCNT),
			srb->total_xfer_length, d_left_counter);
#if DC395x_LASTPIO
		/* KG: Less than or equal to 4 bytes can not be transferred via DMA, it seems. */
		if (d_left_counter
		    && srb->total_xfer_length <= DC395x_LASTPIO) {
			size_t left_io = srb->total_xfer_length;

			/*u32 addr = (srb->segment_x[srb->sg_index].address); */
			/*sg_update_list (srb, d_left_counter); */
			dprintkdbg(DBG_PIO, "data_in_phase0: PIO (%i %s) "
				   "for remaining %i bytes:",
				fc & 0x1f,
				(srb->dcb->sync_period & WIDE_SYNC) ?
				    "words" : "bytes",
				srb->total_xfer_length);
			if (srb->dcb->sync_period & WIDE_SYNC)
				DC395x_write8(acb, TRM_S1040_SCSI_CONFIG2,
					      CFG2_WIDEFIFO);
			while (left_io) {
				unsigned char *virt, *base = NULL;
				unsigned long flags = 0;
				size_t len = left_io;
				size_t offset = srb->request_length - left_io;

				local_irq_save(flags);
				/* Assumption: it's inside one page as it's at most 4 bytes and
				   I just assume it's on a 4-byte boundary */
				base = scsi_kmap_atomic_sg(scsi_sglist(srb->cmd),
							   srb->sg_count, &offset, &len);
				virt = base + offset;

				left_io -= len;

				while (len) {
					u8 byte;
					byte = DC395x_read8(acb, TRM_S1040_SCSI_FIFO);
					*virt++ = byte;

					if (debug_enabled(DBG_PIO))
						printk(" %02x", byte);

					d_left_counter--;
					sg_subtract_one(srb);

					len--;

					fc = DC395x_read8(acb, TRM_S1040_SCSI_FIFOCNT);

					if (fc == 0x40) {
						left_io = 0;
						break;
					}
				}

				WARN_ON((fc != 0x40) == !d_left_counter);

				if (fc == 0x40 && (srb->dcb->sync_period & WIDE_SYNC)) {
					/* Read the last byte ... */
					if (srb->total_xfer_length > 0) {
						u8 byte = DC395x_read8(acb, TRM_S1040_SCSI_FIFO);

						*virt++ = byte;
						srb->total_xfer_length--;
						if (debug_enabled(DBG_PIO))
							printk(" %02x", byte);
					}

					DC395x_write8(acb, TRM_S1040_SCSI_CONFIG2, 0);
				}

				scsi_kunmap_atomic_sg(base);
				local_irq_restore(flags);
			}
			/*printk(" %08x", *(u32*)(bus_to_virt (addr))); */
			/*srb->total_xfer_length = 0; */
			if (debug_enabled(DBG_PIO))
				printk("\n");
		}
#endif				/* DC395x_LASTPIO */

#if 0
		/*
		 * KG: This was in DATAOUT. Does it also belong here?
		 * Nobody seems to know what counter and fifo_cnt count exactly ...
		 */
		if (!(scsi_status & SCSIXFERDONE)) {
			/*
			 * when data transfer from DMA FIFO to SCSI FIFO
			 * if there was some data left in SCSI FIFO
			 */
			d_left_counter =
			    (u32)(DC395x_read8(acb, TRM_S1040_SCSI_FIFOCNT) &
				  0x1F);
			if (srb->dcb->sync_period & WIDE_SYNC)
				d_left_counter <<= 1;
			/*
			 * if WIDE scsi SCSI FIFOCNT unit is word !!!
			 * so need to *= 2
			 * KG: Seems to be correct ...
			 */
		}
#endif
		/* KG: This should not be needed any more! */
		if (d_left_counter == 0
		    || (scsi_status & SCSIXFERCNT_2_ZERO)) {
#if 0
			int ctr = 6000000;
			u8 TempDMAstatus;
			do {
				TempDMAstatus =
				    DC395x_read8(acb, TRM_S1040_DMA_STATUS);
			} while (!(TempDMAstatus & DMAXFERCOMP) && --ctr);
			if (!ctr)
				dprintkl(KERN_ERR,
				       "Deadlock in DataInPhase0 waiting for DMA!!\n");
			srb->total_xfer_length = 0;
#endif
			srb->total_xfer_length = d_left_counter;
		} else {	/* phase changed */
			/*
			 * parsing the case:
			 * when a transfer not yet complete 
			 * but be disconnected by target
			 * if transfer not yet complete
			 * there were some data residue in SCSI FIFO or
			 * SCSI transfer counter not empty
			 */
			sg_update_list(srb, d_left_counter);
		}
	}
	/* KG: The target may decide to disconnect: Empty FIFO before! */
	if ((*pscsi_status & PHASEMASK) != PH_DATA_IN) {
		cleanup_after_transfer(acb, srb);
	}
}