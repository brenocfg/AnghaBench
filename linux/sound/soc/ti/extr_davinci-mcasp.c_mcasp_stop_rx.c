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
struct davinci_mcasp {scalar_t__ fifo_base; scalar_t__ rxnumevt; int /*<<< orphan*/  streams; int /*<<< orphan*/ * irq_request; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_EVTCTLR_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_GBLCTLR_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_GBLCTLX_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXSTAT_REG ; 
 int /*<<< orphan*/  FIFO_ENABLE ; 
 scalar_t__ MCASP_RFIFOCTL_OFFSET ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mcasp_is_synchronous (struct davinci_mcasp*) ; 
 int /*<<< orphan*/  mcasp_set_clk_pdir (struct davinci_mcasp*,int) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcasp_stop_rx(struct davinci_mcasp *mcasp)
{
	/* disable IRQ sources */
	mcasp_clr_bits(mcasp, DAVINCI_MCASP_EVTCTLR_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_CAPTURE]);

	/*
	 * In synchronous mode stop the TX clocks if no other stream is
	 * running
	 */
	if (mcasp_is_synchronous(mcasp) && !mcasp->streams) {
		mcasp_set_clk_pdir(mcasp, false);
		mcasp_set_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, 0);
	}

	mcasp_set_reg(mcasp, DAVINCI_MCASP_GBLCTLR_REG, 0);
	mcasp_set_reg(mcasp, DAVINCI_MCASP_RXSTAT_REG, 0xFFFFFFFF);

	if (mcasp->rxnumevt) {	/* disable FIFO */
		u32 reg = mcasp->fifo_base + MCASP_RFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
	}
}