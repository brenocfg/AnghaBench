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
typedef  scalar_t__ uint ;
struct jsm_board {scalar_t__ nasync; int /*<<< orphan*/  bd_intr_lock; int /*<<< orphan*/  pci_dev; scalar_t__ re_map_membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ UART_CLASSIC_POLL_ADDR_OFFSET ; 
 int /*<<< orphan*/  cls_parse_isr (struct jsm_board*,scalar_t__) ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t cls_intr(int irq, void *voidbrd)
{
	struct jsm_board *brd = voidbrd;
	unsigned long lock_flags;
	unsigned char uart_poll;
	uint i = 0;

	/* Lock out the slow poller from running on this board. */
	spin_lock_irqsave(&brd->bd_intr_lock, lock_flags);

	/*
	 * Check the board's global interrupt offset to see if we
	 * acctually do have an interrupt pending on us.
	 */
	uart_poll = readb(brd->re_map_membase + UART_CLASSIC_POLL_ADDR_OFFSET);

	jsm_dbg(INTR, &brd->pci_dev, "%s:%d uart_poll: %x\n",
		__FILE__, __LINE__, uart_poll);

	if (!uart_poll) {
		jsm_dbg(INTR, &brd->pci_dev,
			"Kernel interrupted to me, but no pending interrupts...\n");
		spin_unlock_irqrestore(&brd->bd_intr_lock, lock_flags);
		return IRQ_NONE;
	}

	/* At this point, we have at least SOMETHING to service, dig further. */

	/* Parse each port to find out what caused the interrupt */
	for (i = 0; i < brd->nasync; i++)
		cls_parse_isr(brd, i);

	spin_unlock_irqrestore(&brd->bd_intr_lock, lock_flags);

	return IRQ_HANDLED;
}