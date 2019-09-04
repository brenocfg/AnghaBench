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
struct fst_port_info {int /*<<< orphan*/  index; int /*<<< orphan*/  run; } ;
struct fst_card_info {scalar_t__ state; scalar_t__ family; int /*<<< orphan*/  card_no; struct fst_port_info* ports; scalar_t__ dmatx_in_progress; int /*<<< orphan*/  dma_txpos; int /*<<< orphan*/  dma_len_tx; int /*<<< orphan*/  dma_port_tx; scalar_t__ pci_conf; scalar_t__ dmarx_in_progress; int /*<<< orphan*/  dma_rxpos; int /*<<< orphan*/  dma_skb_rx; int /*<<< orphan*/  dma_len_rx; int /*<<< orphan*/  dma_port_rx; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  rdindex; int /*<<< orphan*/ * evntbuff; int /*<<< orphan*/  wrindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
#define  ABTA_SENT 142 
#define  ABTB_SENT 141 
#define  ABTC_SENT 140 
#define  ABTD_SENT 139 
#define  CTLA_CHG 138 
#define  CTLB_CHG 137 
#define  CTLC_CHG 136 
#define  CTLD_CHG 135 
 int /*<<< orphan*/  DBG_ASS ; 
 int /*<<< orphan*/  DBG_INIT ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int /*<<< orphan*/  DBG_RX ; 
 int /*<<< orphan*/  DBG_TX ; 
 scalar_t__ DMACSR0 ; 
 scalar_t__ DMACSR1 ; 
 scalar_t__ FST_CARD_INT ; 
 scalar_t__ FST_FAMILY_TXU ; 
 scalar_t__ FST_IFAILED ; 
 int FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 unsigned int FST_RDL (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ FST_RUNNING ; 
 scalar_t__ FST_RX_DMA_INT ; 
 scalar_t__ FST_TX_DMA_INT ; 
 int /*<<< orphan*/  FST_WRB (struct fst_card_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FST_WRL (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  INIT_CPLT 134 
#define  INIT_FAIL 133 
 scalar_t__ INTCSR_9054 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX_CIRBUFF ; 
#define  TE1_ALMA 132 
#define  TXA_UNDF 131 
#define  TXB_UNDF 130 
#define  TXC_UNDF 129 
#define  TXD_UNDF 128 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fst_clear_intr (struct fst_card_info*) ; 
 int /*<<< orphan*/  fst_int_task ; 
 int /*<<< orphan*/  fst_intr_ctlchg (struct fst_card_info*,struct fst_port_info*) ; 
 int /*<<< orphan*/  fst_intr_te1_alarm (struct fst_card_info*,struct fst_port_info*) ; 
 int /*<<< orphan*/  fst_q_work_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_rx_dma_complete (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_tx_dma_complete (struct fst_card_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_work_intq ; 
 unsigned int inl (scalar_t__) ; 
 TYPE_3__ interruptEvent ; 
 int /*<<< orphan*/  interruptHandshake ; 
 int /*<<< orphan*/  interruptRetryCount ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_2__* port_to_dev (struct fst_port_info*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
fst_intr(int dummy, void *dev_id)
{
	struct fst_card_info *card = dev_id;
	struct fst_port_info *port;
	int rdidx;		/* Event buffer indices */
	int wridx;
	int event;		/* Actual event for processing */
	unsigned int dma_intcsr = 0;
	unsigned int do_card_interrupt;
	unsigned int int_retry_count;

	/*
	 * Check to see if the interrupt was for this card
	 * return if not
	 * Note that the call to clear the interrupt is important
	 */
	dbg(DBG_INTR, "intr: %d %p\n", card->irq, card);
	if (card->state != FST_RUNNING) {
		pr_err("Interrupt received for card %d in a non running state (%d)\n",
		       card->card_no, card->state);

		/* 
		 * It is possible to really be running, i.e. we have re-loaded
		 * a running card
		 * Clear and reprime the interrupt source 
		 */
		fst_clear_intr(card);
		return IRQ_HANDLED;
	}

	/* Clear and reprime the interrupt source */
	fst_clear_intr(card);

	/*
	 * Is the interrupt for this card (handshake == 1)
	 */
	do_card_interrupt = 0;
	if (FST_RDB(card, interruptHandshake) == 1) {
		do_card_interrupt += FST_CARD_INT;
		/* Set the software acknowledge */
		FST_WRB(card, interruptHandshake, 0xEE);
	}
	if (card->family == FST_FAMILY_TXU) {
		/*
		 * Is it a DMA Interrupt
		 */
		dma_intcsr = inl(card->pci_conf + INTCSR_9054);
		if (dma_intcsr & 0x00200000) {
			/*
			 * DMA Channel 0 (Rx transfer complete)
			 */
			dbg(DBG_RX, "DMA Rx xfer complete\n");
			outb(0x8, card->pci_conf + DMACSR0);
			fst_rx_dma_complete(card, card->dma_port_rx,
					    card->dma_len_rx, card->dma_skb_rx,
					    card->dma_rxpos);
			card->dmarx_in_progress = 0;
			do_card_interrupt += FST_RX_DMA_INT;
		}
		if (dma_intcsr & 0x00400000) {
			/*
			 * DMA Channel 1 (Tx transfer complete)
			 */
			dbg(DBG_TX, "DMA Tx xfer complete\n");
			outb(0x8, card->pci_conf + DMACSR1);
			fst_tx_dma_complete(card, card->dma_port_tx,
					    card->dma_len_tx, card->dma_txpos);
			card->dmatx_in_progress = 0;
			do_card_interrupt += FST_TX_DMA_INT;
		}
	}

	/*
	 * Have we been missing Interrupts
	 */
	int_retry_count = FST_RDL(card, interruptRetryCount);
	if (int_retry_count) {
		dbg(DBG_ASS, "Card %d int_retry_count is  %d\n",
		    card->card_no, int_retry_count);
		FST_WRL(card, interruptRetryCount, 0);
	}

	if (!do_card_interrupt) {
		return IRQ_HANDLED;
	}

	/* Scehdule the bottom half of the ISR */
	fst_q_work_item(&fst_work_intq, card->card_no);
	tasklet_schedule(&fst_int_task);

	/* Drain the event queue */
	rdidx = FST_RDB(card, interruptEvent.rdindex) & 0x1f;
	wridx = FST_RDB(card, interruptEvent.wrindex) & 0x1f;
	while (rdidx != wridx) {
		event = FST_RDB(card, interruptEvent.evntbuff[rdidx]);
		port = &card->ports[event & 0x03];

		dbg(DBG_INTR, "Processing Interrupt event: %x\n", event);

		switch (event) {
		case TE1_ALMA:
			dbg(DBG_INTR, "TE1 Alarm intr\n");
			if (port->run)
				fst_intr_te1_alarm(card, port);
			break;

		case CTLA_CHG:
		case CTLB_CHG:
		case CTLC_CHG:
		case CTLD_CHG:
			if (port->run)
				fst_intr_ctlchg(card, port);
			break;

		case ABTA_SENT:
		case ABTB_SENT:
		case ABTC_SENT:
		case ABTD_SENT:
			dbg(DBG_TX, "Abort complete port %d\n", port->index);
			break;

		case TXA_UNDF:
		case TXB_UNDF:
		case TXC_UNDF:
		case TXD_UNDF:
			/* Difficult to see how we'd get this given that we
			 * always load up the entire packet for DMA.
			 */
			dbg(DBG_TX, "Tx underflow port %d\n", port->index);
			port_to_dev(port)->stats.tx_errors++;
			port_to_dev(port)->stats.tx_fifo_errors++;
			dbg(DBG_ASS, "Tx underflow on card %d port %d\n",
			    card->card_no, port->index);
			break;

		case INIT_CPLT:
			dbg(DBG_INIT, "Card init OK intr\n");
			break;

		case INIT_FAIL:
			dbg(DBG_INIT, "Card init FAILED intr\n");
			card->state = FST_IFAILED;
			break;

		default:
			pr_err("intr: unknown card event %d. ignored\n", event);
			break;
		}

		/* Bump and wrap the index */
		if (++rdidx >= MAX_CIRBUFF)
			rdidx = 0;
	}
	FST_WRB(card, interruptEvent.rdindex, rdidx);
        return IRQ_HANDLED;
}