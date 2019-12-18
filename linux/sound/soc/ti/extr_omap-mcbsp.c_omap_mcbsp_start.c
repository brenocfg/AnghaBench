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
typedef  int u16 ;
struct omap_mcbsp {TYPE_1__* pdata; scalar_t__ st_data; } ;
struct TYPE_2__ {scalar_t__ has_ccr; } ;

/* Variables and functions */
 int CLKRM ; 
 int CLKXM ; 
 int FSRM ; 
 int FSXM ; 
 int MCBSP_READ_CACHE (struct omap_mcbsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCBSP_WRITE (struct omap_mcbsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCR0 ; 
 int /*<<< orphan*/  RCCR ; 
 int RDISABLE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SPCR1 ; 
 int /*<<< orphan*/  SPCR2 ; 
 int /*<<< orphan*/  XCCR ; 
 int XDISABLE ; 
 int /*<<< orphan*/  omap_mcbsp_dump_reg (struct omap_mcbsp*) ; 
 int /*<<< orphan*/  omap_mcbsp_st_start (struct omap_mcbsp*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void omap_mcbsp_start(struct omap_mcbsp *mcbsp, int stream)
{
	int tx = (stream == SNDRV_PCM_STREAM_PLAYBACK);
	int rx = !tx;
	int enable_srg = 0;
	u16 w;

	if (mcbsp->st_data)
		omap_mcbsp_st_start(mcbsp);

	/* Only enable SRG, if McBSP is master */
	w = MCBSP_READ_CACHE(mcbsp, PCR0);
	if (w & (FSXM | FSRM | CLKXM | CLKRM))
		enable_srg = !((MCBSP_READ_CACHE(mcbsp, SPCR2) |
				MCBSP_READ_CACHE(mcbsp, SPCR1)) & 1);

	if (enable_srg) {
		/* Start the sample generator */
		w = MCBSP_READ_CACHE(mcbsp, SPCR2);
		MCBSP_WRITE(mcbsp, SPCR2, w | (1 << 6));
	}

	/* Enable transmitter and receiver */
	tx &= 1;
	w = MCBSP_READ_CACHE(mcbsp, SPCR2);
	MCBSP_WRITE(mcbsp, SPCR2, w | tx);

	rx &= 1;
	w = MCBSP_READ_CACHE(mcbsp, SPCR1);
	MCBSP_WRITE(mcbsp, SPCR1, w | rx);

	/*
	 * Worst case: CLKSRG*2 = 8000khz: (1/8000) * 2 * 2 usec
	 * REVISIT: 100us may give enough time for two CLKSRG, however
	 * due to some unknown PM related, clock gating etc. reason it
	 * is now at 500us.
	 */
	udelay(500);

	if (enable_srg) {
		/* Start frame sync */
		w = MCBSP_READ_CACHE(mcbsp, SPCR2);
		MCBSP_WRITE(mcbsp, SPCR2, w | (1 << 7));
	}

	if (mcbsp->pdata->has_ccr) {
		/* Release the transmitter and receiver */
		w = MCBSP_READ_CACHE(mcbsp, XCCR);
		w &= ~(tx ? XDISABLE : 0);
		MCBSP_WRITE(mcbsp, XCCR, w);
		w = MCBSP_READ_CACHE(mcbsp, RCCR);
		w &= ~(rx ? RDISABLE : 0);
		MCBSP_WRITE(mcbsp, RCCR, w);
	}

	/* Dump McBSP Regs */
	omap_mcbsp_dump_reg(mcbsp);
}