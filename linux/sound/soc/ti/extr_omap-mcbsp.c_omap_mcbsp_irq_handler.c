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
typedef  int u16 ;
struct omap_mcbsp {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MCBSP_READ (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int) ; 
 int REOFEN ; 
 int RFSREN ; 
 int ROVFLEN ; 
 int RRDYEN ; 
 int RSYNCERREN ; 
 int RUNDFLEN ; 
 int XEMPTYEOFEN ; 
 int XEOFEN ; 
 int XFSXEN ; 
 int XOVFLEN ; 
 int XRDYEN ; 
 int XSYNCERREN ; 
 int XUNDFLEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static irqreturn_t omap_mcbsp_irq_handler(int irq, void *data)
{
	struct omap_mcbsp *mcbsp = data;
	u16 irqst;

	irqst = MCBSP_READ(mcbsp, IRQST);
	dev_dbg(mcbsp->dev, "IRQ callback : 0x%x\n", irqst);

	if (irqst & RSYNCERREN)
		dev_err(mcbsp->dev, "RX Frame Sync Error!\n");
	if (irqst & RFSREN)
		dev_dbg(mcbsp->dev, "RX Frame Sync\n");
	if (irqst & REOFEN)
		dev_dbg(mcbsp->dev, "RX End Of Frame\n");
	if (irqst & RRDYEN)
		dev_dbg(mcbsp->dev, "RX Buffer Threshold Reached\n");
	if (irqst & RUNDFLEN)
		dev_err(mcbsp->dev, "RX Buffer Underflow!\n");
	if (irqst & ROVFLEN)
		dev_err(mcbsp->dev, "RX Buffer Overflow!\n");

	if (irqst & XSYNCERREN)
		dev_err(mcbsp->dev, "TX Frame Sync Error!\n");
	if (irqst & XFSXEN)
		dev_dbg(mcbsp->dev, "TX Frame Sync\n");
	if (irqst & XEOFEN)
		dev_dbg(mcbsp->dev, "TX End Of Frame\n");
	if (irqst & XRDYEN)
		dev_dbg(mcbsp->dev, "TX Buffer threshold Reached\n");
	if (irqst & XUNDFLEN)
		dev_err(mcbsp->dev, "TX Buffer Underflow!\n");
	if (irqst & XOVFLEN)
		dev_err(mcbsp->dev, "TX Buffer Overflow!\n");
	if (irqst & XEMPTYEOFEN)
		dev_dbg(mcbsp->dev, "TX Buffer empty at end of frame\n");

	MCBSP_WRITE(mcbsp, IRQST, irqst);

	return IRQ_HANDLED;
}