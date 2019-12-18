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
typedef  scalar_t__ u32 ;
struct davinci_mcasp {int /*<<< orphan*/ * irq_request; scalar_t__ fifo_base; scalar_t__ rxnumevt; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_EVTCTLR_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_GBLCTLR_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_GBLCTLX_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXSTAT_REG ; 
 int /*<<< orphan*/  FIFO_ENABLE ; 
 scalar_t__ MCASP_RFIFOCTL_OFFSET ; 
 int /*<<< orphan*/  RXCLKRST ; 
 int /*<<< orphan*/  RXFSRST ; 
 int /*<<< orphan*/  RXHCLKRST ; 
 int /*<<< orphan*/  RXSERCLR ; 
 int /*<<< orphan*/  RXSMRST ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  TXCLKRST ; 
 int /*<<< orphan*/  TXFSRST ; 
 int /*<<< orphan*/  TXHCLKRST ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mcasp_is_synchronous (struct davinci_mcasp*) ; 
 int /*<<< orphan*/  mcasp_set_bits (struct davinci_mcasp*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_clk_pdir (struct davinci_mcasp*,int) ; 
 int /*<<< orphan*/  mcasp_set_ctl_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcasp_start_rx(struct davinci_mcasp *mcasp)
{
	if (mcasp->rxnumevt) {	/* enable FIFO */
		u32 reg = mcasp->fifo_base + MCASP_RFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
		mcasp_set_bits(mcasp, reg, FIFO_ENABLE);
	}

	/* Start clocks */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXHCLKRST);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXCLKRST);
	/*
	 * When ASYNC == 0 the transmit and receive sections operate
	 * synchronously from the transmit clock and frame sync. We need to make
	 * sure that the TX signlas are enabled when starting reception.
	 */
	if (mcasp_is_synchronous(mcasp)) {
		mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXHCLKRST);
		mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXCLKRST);
		mcasp_set_clk_pdir(mcasp, true);
	}

	/* Activate serializer(s) */
	mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXSERCLR);
	/* Release RX state machine */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXSMRST);
	/* Release Frame Sync generator */
	mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, RXFSRST);
	if (mcasp_is_synchronous(mcasp))
		mcasp_set_ctl_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, TXFSRST);

	/* enable receive IRQs */
	mcasp_set_bits(mcasp, DAVINCI_MCASP_EVTCTLR_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE]);
}