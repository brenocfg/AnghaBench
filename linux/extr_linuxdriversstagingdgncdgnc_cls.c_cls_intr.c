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
struct dgnc_board {scalar_t__ nasync; int /*<<< orphan*/  bd_intr_lock; int /*<<< orphan*/  helper_tasklet; scalar_t__ re_map_membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ UART_CLASSIC_POLL_ADDR_OFFSET ; 
 int /*<<< orphan*/  cls_parse_isr (struct dgnc_board*,scalar_t__) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cls_intr(int irq, void *voidbrd)
{
	struct dgnc_board *brd = voidbrd;
	uint i = 0;
	unsigned char poll_reg;
	unsigned long flags;

	if (!brd)
		return IRQ_NONE;

	spin_lock_irqsave(&brd->bd_intr_lock, flags);

	poll_reg = readb(brd->re_map_membase + UART_CLASSIC_POLL_ADDR_OFFSET);
	if (!poll_reg) {
		spin_unlock_irqrestore(&brd->bd_intr_lock, flags);
		return IRQ_NONE;
	}

	for (i = 0; i < brd->nasync; i++)
		cls_parse_isr(brd, i);

	tasklet_schedule(&brd->helper_tasklet);

	spin_unlock_irqrestore(&brd->bd_intr_lock, flags);

	return IRQ_HANDLED;
}