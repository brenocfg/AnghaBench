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
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MCBSP_READ (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCBSP_READ_CACHE (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPCR2 ; 
 int XSYNC_ERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static irqreturn_t omap_mcbsp_tx_irq_handler(int irq, void *data)
{
	struct omap_mcbsp *mcbsp = data;
	u16 irqst_spcr2;

	irqst_spcr2 = MCBSP_READ(mcbsp, SPCR2);
	dev_dbg(mcbsp->dev, "TX IRQ callback : 0x%x\n", irqst_spcr2);

	if (irqst_spcr2 & XSYNC_ERR) {
		dev_err(mcbsp->dev, "TX Frame Sync Error! : 0x%x\n",
			irqst_spcr2);
		/* Writing zero to XSYNC_ERR clears the IRQ */
		MCBSP_WRITE(mcbsp, SPCR2, MCBSP_READ_CACHE(mcbsp, SPCR2));
	}

	return IRQ_HANDLED;
}