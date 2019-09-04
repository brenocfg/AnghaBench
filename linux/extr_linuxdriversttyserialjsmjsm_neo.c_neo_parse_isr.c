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
typedef  int u8 ;
typedef  size_t u32 ;
struct jsm_channel {int ch_flags; int ch_mostat; TYPE_2__* ch_neo_uart; TYPE_1__* ch_bd; int /*<<< orphan*/  ch_lock; } ;
struct jsm_board {size_t maxports; struct jsm_channel** channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  msr; int /*<<< orphan*/  mcr; int /*<<< orphan*/  xoffchar1; int /*<<< orphan*/  isr_fcr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int CH_STOP ; 
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int /*<<< orphan*/  INTR ; 
 int UART_17158_IIR_FIFO_ENABLED ; 
 int UART_17158_IIR_HWFLOW_STATE_CHANGE ; 
 int UART_17158_IIR_RDI_TIMEOUT ; 
 int UART_17158_IIR_XONXOFF ; 
 int UART_17158_XOFF_DETECT ; 
 int UART_17158_XON_DETECT ; 
 int UART_IIR_NO_INT ; 
 int UART_IIR_RDI ; 
 int UART_IIR_THRI ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  jsm_check_queue_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  neo_copy_data_from_queue_to_uart (struct jsm_channel*) ; 
 int /*<<< orphan*/  neo_copy_data_from_uart_to_queue (struct jsm_channel*) ; 
 int /*<<< orphan*/  neo_parse_modem (struct jsm_channel*,int) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void neo_parse_isr(struct jsm_board *brd, u32 port)
{
	struct jsm_channel *ch;
	u8 isr;
	u8 cause;
	unsigned long lock_flags;

	if (!brd)
		return;

	if (port >= brd->maxports)
		return;

	ch = brd->channels[port];
	if (!ch)
		return;

	/* Here we try to figure out what caused the interrupt to happen */
	while (1) {

		isr = readb(&ch->ch_neo_uart->isr_fcr);

		/* Bail if no pending interrupt */
		if (isr & UART_IIR_NO_INT)
			break;

		/*
		 * Yank off the upper 2 bits, which just show that the FIFO's are enabled.
		 */
		isr &= ~(UART_17158_IIR_FIFO_ENABLED);

		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d isr: %x\n",
			__FILE__, __LINE__, isr);

		if (isr & (UART_17158_IIR_RDI_TIMEOUT | UART_IIR_RDI)) {
			/* Read data from uart -> queue */
			neo_copy_data_from_uart_to_queue(ch);

			/* Call our tty layer to enforce queue flow control if needed. */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			jsm_check_queue_flow_control(ch);
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		}

		if (isr & UART_IIR_THRI) {
			/* Transfer data (if any) from Write Queue -> UART. */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
			neo_copy_data_from_queue_to_uart(ch);
		}

		if (isr & UART_17158_IIR_XONXOFF) {
			cause = readb(&ch->ch_neo_uart->xoffchar1);

			jsm_dbg(INTR, &ch->ch_bd->pci_dev,
				"Port %d. Got ISR_XONXOFF: cause:%x\n",
				port, cause);

			/*
			 * Since the UART detected either an XON or
			 * XOFF match, we need to figure out which
			 * one it was, so we can suspend or resume data flow.
			 */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			if (cause == UART_17158_XON_DETECT) {
				/* Is output stopped right now, if so, resume it */
				if (brd->channels[port]->ch_flags & CH_STOP) {
					ch->ch_flags &= ~(CH_STOP);
				}
				jsm_dbg(INTR, &ch->ch_bd->pci_dev,
					"Port %d. XON detected in incoming data\n",
					port);
			}
			else if (cause == UART_17158_XOFF_DETECT) {
				if (!(brd->channels[port]->ch_flags & CH_STOP)) {
					ch->ch_flags |= CH_STOP;
					jsm_dbg(INTR, &ch->ch_bd->pci_dev,
						"Setting CH_STOP\n");
				}
				jsm_dbg(INTR, &ch->ch_bd->pci_dev,
					"Port: %d. XOFF detected in incoming data\n",
					port);
			}
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		}

		if (isr & UART_17158_IIR_HWFLOW_STATE_CHANGE) {
			/*
			 * If we get here, this means the hardware is doing auto flow control.
			 * Check to see whether RTS/DTR or CTS/DSR caused this interrupt.
			 */
			cause = readb(&ch->ch_neo_uart->mcr);

			/* Which pin is doing auto flow? RTS or DTR? */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			if ((cause & 0x4) == 0) {
				if (cause & UART_MCR_RTS)
					ch->ch_mostat |= UART_MCR_RTS;
				else
					ch->ch_mostat &= ~(UART_MCR_RTS);
			} else {
				if (cause & UART_MCR_DTR)
					ch->ch_mostat |= UART_MCR_DTR;
				else
					ch->ch_mostat &= ~(UART_MCR_DTR);
			}
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		}

		/* Parse any modem signal changes */
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"MOD_STAT: sending to parse_modem_sigs\n");
		neo_parse_modem(ch, readb(&ch->ch_neo_uart->msr));
	}
}