#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct jsm_channel {int /*<<< orphan*/  ch_lock; } ;
struct jsm_board {int nasync; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  bd_intr_lock; struct jsm_channel** channels; scalar_t__ re_map_membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  UART_17158_MSR 131 
 scalar_t__ UART_17158_POLL_ADDR_OFFSET ; 
#define  UART_17158_RXRDY_TIMEOUT 130 
#define  UART_17158_RX_LINE_STATUS 129 
#define  UART_17158_TXRDY 128 
 int /*<<< orphan*/  jsm_check_queue_flow_control (struct jsm_channel*) ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int* jsm_offset_table ; 
 int /*<<< orphan*/  neo_copy_data_from_uart_to_queue (struct jsm_channel*) ; 
 int /*<<< orphan*/  neo_parse_isr (struct jsm_board*,int) ; 
 int /*<<< orphan*/  neo_parse_lsr (struct jsm_board*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t neo_intr(int irq, void *voidbrd)
{
	struct jsm_board *brd = voidbrd;
	struct jsm_channel *ch;
	int port = 0;
	int type = 0;
	int current_port;
	u32 tmp;
	u32 uart_poll;
	unsigned long lock_flags;
	unsigned long lock_flags2;
	int outofloop_count = 0;

	/* Lock out the slow poller from running on this board. */
	spin_lock_irqsave(&brd->bd_intr_lock, lock_flags);

	/*
	 * Read in "extended" IRQ information from the 32bit Neo register.
	 * Bits 0-7: What port triggered the interrupt.
	 * Bits 8-31: Each 3bits indicate what type of interrupt occurred.
	 */
	uart_poll = readl(brd->re_map_membase + UART_17158_POLL_ADDR_OFFSET);

	jsm_dbg(INTR, &brd->pci_dev, "%s:%d uart_poll: %x\n",
		__FILE__, __LINE__, uart_poll);

	if (!uart_poll) {
		jsm_dbg(INTR, &brd->pci_dev,
			"Kernel interrupted to me, but no pending interrupts...\n");
		spin_unlock_irqrestore(&brd->bd_intr_lock, lock_flags);
		return IRQ_NONE;
	}

	/* At this point, we have at least SOMETHING to service, dig further... */

	current_port = 0;

	/* Loop on each port */
	while (((uart_poll & 0xff) != 0) && (outofloop_count < 0xff)){

		tmp = uart_poll;
		outofloop_count++;

		/* Check current port to see if it has interrupt pending */
		if ((tmp & jsm_offset_table[current_port]) != 0) {
			port = current_port;
			type = tmp >> (8 + (port * 3));
			type &= 0x7;
		} else {
			current_port++;
			continue;
		}

		jsm_dbg(INTR, &brd->pci_dev, "%s:%d port: %x type: %x\n",
			__FILE__, __LINE__, port, type);

		/* Remove this port + type from uart_poll */
		uart_poll &= ~(jsm_offset_table[port]);

		if (!type) {
			/* If no type, just ignore it, and move onto next port */
			jsm_dbg(INTR, &brd->pci_dev,
				"Interrupt with no type! port: %d\n", port);
			continue;
		}

		/* Switch on type of interrupt we have */
		switch (type) {

		case UART_17158_RXRDY_TIMEOUT:
			/*
			 * RXRDY Time-out is cleared by reading data in the
			* RX FIFO until it falls below the trigger level.
			 */

			/* Verify the port is in range. */
			if (port >= brd->nasync)
				continue;

			ch = brd->channels[port];
			if (!ch)
				continue;

			neo_copy_data_from_uart_to_queue(ch);

			/* Call our tty layer to enforce queue flow control if needed. */
			spin_lock_irqsave(&ch->ch_lock, lock_flags2);
			jsm_check_queue_flow_control(ch);
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags2);

			continue;

		case UART_17158_RX_LINE_STATUS:
			/*
			 * RXRDY and RX LINE Status (logic OR of LSR[4:1])
			 */
			neo_parse_lsr(brd, port);
			continue;

		case UART_17158_TXRDY:
			/*
			 * TXRDY interrupt clears after reading ISR register for the UART channel.
			 */

			/*
			 * Yes, this is odd...
			 * Why would I check EVERY possibility of type of
			 * interrupt, when we know its TXRDY???
			 * Becuz for some reason, even tho we got triggered for TXRDY,
			 * it seems to be occasionally wrong. Instead of TX, which
			 * it should be, I was getting things like RXDY too. Weird.
			 */
			neo_parse_isr(brd, port);
			continue;

		case UART_17158_MSR:
			/*
			 * MSR or flow control was seen.
			 */
			neo_parse_isr(brd, port);
			continue;

		default:
			/*
			 * The UART triggered us with a bogus interrupt type.
			 * It appears the Exar chip, when REALLY bogged down, will throw
			 * these once and awhile.
			 * Its harmless, just ignore it and move on.
			 */
			jsm_dbg(INTR, &brd->pci_dev,
				"%s:%d Unknown Interrupt type: %x\n",
				__FILE__, __LINE__, type);
			continue;
		}
	}

	spin_unlock_irqrestore(&brd->bd_intr_lock, lock_flags);

	jsm_dbg(INTR, &brd->pci_dev, "finish\n");
	return IRQ_HANDLED;
}