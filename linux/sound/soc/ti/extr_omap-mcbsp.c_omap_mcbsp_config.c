#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct omap_mcbsp_reg_cfg {int spcr2; int spcr1; int rcr2; int rcr1; int xcr2; int xcr1; int srgr2; int srgr1; int mcr2; int mcr1; int pcr0; int xccr; int rccr; } ;
struct omap_mcbsp {scalar_t__ irq; TYPE_1__* pdata; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ has_wakeup; scalar_t__ has_ccr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQEN ; 
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCR1 ; 
 int /*<<< orphan*/  MCR2 ; 
 int /*<<< orphan*/  PCR0 ; 
 int /*<<< orphan*/  RCCR ; 
 int /*<<< orphan*/  RCR1 ; 
 int /*<<< orphan*/  RCR2 ; 
 int ROVFLEN ; 
 int RRDYEN ; 
 int RSYNCERREN ; 
 int RUNDFLEN ; 
 int /*<<< orphan*/  SPCR1 ; 
 int /*<<< orphan*/  SPCR2 ; 
 int /*<<< orphan*/  SRGR1 ; 
 int /*<<< orphan*/  SRGR2 ; 
 int /*<<< orphan*/  WAKEUPEN ; 
 int /*<<< orphan*/  XCCR ; 
 int /*<<< orphan*/  XCR1 ; 
 int /*<<< orphan*/  XCR2 ; 
 int XOVFLEN ; 
 int XRDYEN ; 
 int XSYNCERREN ; 
 int XUNDFLEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_mcbsp_config(struct omap_mcbsp *mcbsp,
			      const struct omap_mcbsp_reg_cfg *config)
{
	dev_dbg(mcbsp->dev, "Configuring McBSP%d  phys_base: 0x%08lx\n",
		mcbsp->id, mcbsp->phys_base);

	/* We write the given config */
	MCBSP_WRITE(mcbsp, SPCR2, config->spcr2);
	MCBSP_WRITE(mcbsp, SPCR1, config->spcr1);
	MCBSP_WRITE(mcbsp, RCR2, config->rcr2);
	MCBSP_WRITE(mcbsp, RCR1, config->rcr1);
	MCBSP_WRITE(mcbsp, XCR2, config->xcr2);
	MCBSP_WRITE(mcbsp, XCR1, config->xcr1);
	MCBSP_WRITE(mcbsp, SRGR2, config->srgr2);
	MCBSP_WRITE(mcbsp, SRGR1, config->srgr1);
	MCBSP_WRITE(mcbsp, MCR2, config->mcr2);
	MCBSP_WRITE(mcbsp, MCR1, config->mcr1);
	MCBSP_WRITE(mcbsp, PCR0, config->pcr0);
	if (mcbsp->pdata->has_ccr) {
		MCBSP_WRITE(mcbsp, XCCR, config->xccr);
		MCBSP_WRITE(mcbsp, RCCR, config->rccr);
	}
	/* Enable wakeup behavior */
	if (mcbsp->pdata->has_wakeup)
		MCBSP_WRITE(mcbsp, WAKEUPEN, XRDYEN | RRDYEN);

	/* Enable TX/RX sync error interrupts by default */
	if (mcbsp->irq)
		MCBSP_WRITE(mcbsp, IRQEN, RSYNCERREN | XSYNCERREN |
			    RUNDFLEN | ROVFLEN | XUNDFLEN | XOVFLEN);
}