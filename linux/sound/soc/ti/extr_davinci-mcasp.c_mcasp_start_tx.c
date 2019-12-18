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
struct davinci_mcasp {int fifo_base; int /*<<< orphan*/ * irq_request; scalar_t__ txnumevt; } ;

/* Variables and functions */
 int DAVINCI_MCASP_EVTCTLX_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_GBLCTLX_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXSTAT_REG ; 
 int /*<<< orphan*/  FIFO_ENABLE ; 
 int MCASP_WFIFOCTL_OFFSET ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TXCLKRST ; 
 int /*<<< orphan*/  TXFSRST ; 
 int /*<<< orphan*/  TXHCLKRST ; 
 int /*<<< orphan*/  TXSERCLR ; 
 int /*<<< orphan*/  TXSMRST ; 
 int XRDATA ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,int,int /*<<< orphan*/ ) ; 
 int mcasp_get_reg (struct davinci_mcasp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_axr_pdir (struct davinci_mcasp*,int) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_clk_pdir (struct davinci_mcasp*,int) ; 
 int /*<<< orphan*/  mcasp_set_ctl_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcasp_start_tx(struct davinci_mcasp *mcasp)
{
	u32 cnt;

	if (mcasp->txnumevt) {	/* enable FIFO */
		u32 reg = mcasp->fifo_base + MCASP_WFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
		mcasp_set_bits(mcasp, reg, FIFO_ENABLE);
	}

	/* Start clocks */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXHCLKRST);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXCLKRST);
	mcasp_set_clk_pdir(mcasp, true);

	/* Activate serializer(s) */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXSERCLR);

	/* wait for XDATA to be cleared */
	cnt = 0;
	while ((mcasp_get_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG) & XRDATA) &&
	       (cnt < 100000))
		cnt++;

	mcasp_set_axr_pdir(mcasp, true);

	/* Release TX state machine */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXSMRST);
	/* Release Frame Sync generator */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXFSRST);

	/* enable transmit IRQs */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_EVTCTLX_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK]);
}