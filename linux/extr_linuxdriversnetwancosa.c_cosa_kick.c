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
struct cosa_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dma; scalar_t__ rxtx; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXBIT ; 
 int /*<<< orphan*/  TXBIT ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosa_getdata8 (struct cosa_data*) ; 
 int /*<<< orphan*/  cosa_putdata8 (struct cosa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosa_putstatus (struct cosa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  put_driver_status_nolock (struct cosa_data*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cosa_kick(struct cosa_data *cosa)
{
	unsigned long flags, flags1;
	char *s = "(probably) IRQ";

	if (test_bit(RXBIT, &cosa->rxtx))
		s = "RX DMA";
	if (test_bit(TXBIT, &cosa->rxtx))
		s = "TX DMA";

	pr_info("%s: %s timeout - restarting\n", cosa->name, s);
	spin_lock_irqsave(&cosa->lock, flags);
	cosa->rxtx = 0;

	flags1 = claim_dma_lock();
	disable_dma(cosa->dma);
	clear_dma_ff(cosa->dma);
	release_dma_lock(flags1);

	/* FIXME: Anything else? */
	udelay(100);
	cosa_putstatus(cosa, 0);
	udelay(100);
	(void) cosa_getdata8(cosa);
	udelay(100);
	cosa_putdata8(cosa, 0);
	udelay(100);
	put_driver_status_nolock(cosa);
	spin_unlock_irqrestore(&cosa->lock, flags);
}