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
struct omap_mcpdm {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MCPDM_DN_IRQ ; 
 int MCPDM_DN_IRQ_EMPTY ; 
 int MCPDM_DN_IRQ_FULL ; 
 int /*<<< orphan*/  MCPDM_REG_IRQSTATUS ; 
 int MCPDM_UP_IRQ ; 
 int MCPDM_UP_IRQ_EMPTY ; 
 int MCPDM_UP_IRQ_FULL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int omap_mcpdm_read (struct omap_mcpdm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_mcpdm_write (struct omap_mcpdm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t omap_mcpdm_irq_handler(int irq, void *dev_id)
{
	struct omap_mcpdm *mcpdm = dev_id;
	int irq_status;

	irq_status = omap_mcpdm_read(mcpdm, MCPDM_REG_IRQSTATUS);

	/* Acknowledge irq event */
	omap_mcpdm_write(mcpdm, MCPDM_REG_IRQSTATUS, irq_status);

	if (irq_status & MCPDM_DN_IRQ_FULL)
		dev_dbg(mcpdm->dev, "DN (playback) FIFO Full\n");

	if (irq_status & MCPDM_DN_IRQ_EMPTY)
		dev_dbg(mcpdm->dev, "DN (playback) FIFO Empty\n");

	if (irq_status & MCPDM_DN_IRQ)
		dev_dbg(mcpdm->dev, "DN (playback) write request\n");

	if (irq_status & MCPDM_UP_IRQ_FULL)
		dev_dbg(mcpdm->dev, "UP (capture) FIFO Full\n");

	if (irq_status & MCPDM_UP_IRQ_EMPTY)
		dev_dbg(mcpdm->dev, "UP (capture) FIFO Empty\n");

	if (irq_status & MCPDM_UP_IRQ)
		dev_dbg(mcpdm->dev, "UP (capture) write request\n");

	return IRQ_HANDLED;
}