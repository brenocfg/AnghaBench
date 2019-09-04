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
typedef  size_t u32 ;
struct jsm_channel {int ch_cached_lsr; int ch_flags; int /*<<< orphan*/  ch_lock; TYPE_2__* ch_bd; int /*<<< orphan*/  ch_err_overrun; int /*<<< orphan*/  ch_err_break; int /*<<< orphan*/  ch_err_frame; int /*<<< orphan*/  ch_err_parity; TYPE_1__* ch_neo_uart; } ;
struct jsm_board {size_t maxports; struct jsm_channel** channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lsr; } ;

/* Variables and functions */
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int /*<<< orphan*/  INTR ; 
 int UART_17158_RX_FIFO_DATA_ERROR ; 
 int UART_17158_TX_AND_FIFO_CLR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  jsm_check_queue_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int,size_t,...) ; 
 int /*<<< orphan*/  neo_copy_data_from_queue_to_uart (struct jsm_channel*) ; 
 int /*<<< orphan*/  neo_copy_data_from_uart_to_queue (struct jsm_channel*) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void neo_parse_lsr(struct jsm_board *brd, u32 port)
{
	struct jsm_channel *ch;
	int linestatus;
	unsigned long lock_flags;

	if (!brd)
		return;

	if (port >= brd->maxports)
		return;

	ch = brd->channels[port];
	if (!ch)
		return;

	linestatus = readb(&ch->ch_neo_uart->lsr);

	jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d port: %d linestatus: %x\n",
		__FILE__, __LINE__, port, linestatus);

	ch->ch_cached_lsr |= linestatus;

	if (ch->ch_cached_lsr & UART_LSR_DR) {
		/* Read data from uart -> queue */
		neo_copy_data_from_uart_to_queue(ch);
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		jsm_check_queue_flow_control(ch);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
	}

	/*
	 * This is a special flag. It indicates that at least 1
	 * RX error (parity, framing, or break) has happened.
	 * Mark this in our struct, which will tell me that I have
	 *to do the special RX+LSR read for this FIFO load.
	 */
	if (linestatus & UART_17158_RX_FIFO_DATA_ERROR)
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d Got an RX error, need to parse LSR\n",
			__FILE__, __LINE__, port);

	/*
	 * The next 3 tests should *NOT* happen, as the above test
	 * should encapsulate all 3... At least, thats what Exar says.
	 */

	if (linestatus & UART_LSR_PE) {
		ch->ch_err_parity++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d Port: %d. PAR ERR!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_FE) {
		ch->ch_err_frame++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d Port: %d. FRM ERR!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_BI) {
		ch->ch_err_break++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d. BRK INTR!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_OE) {
		/*
		 * Rx Oruns. Exar says that an orun will NOT corrupt
		 * the FIFO. It will just replace the holding register
		 * with this new data byte. So basically just ignore this.
		 * Probably we should eventually have an orun stat in our driver...
		 */
		ch->ch_err_overrun++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d. Rx Overrun!\n",
			__FILE__, __LINE__, port);
	}

	if (linestatus & UART_LSR_THRE) {
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);

		/* Transfer data (if any) from Write Queue -> UART. */
		neo_copy_data_from_queue_to_uart(ch);
	}
	else if (linestatus & UART_17158_TX_AND_FIFO_CLR) {
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);

		/* Transfer data (if any) from Write Queue -> UART. */
		neo_copy_data_from_queue_to_uart(ch);
	}
}