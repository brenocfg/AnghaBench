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
struct davinci_mcasp {int fifo_base; scalar_t__ txnumevt; scalar_t__ streams; int /*<<< orphan*/ * irq_request; } ;

/* Variables and functions */
 int DAVINCI_MCASP_EVTCTLX_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_GBLCTLX_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_TXSTAT_REG ; 
 int /*<<< orphan*/  FIFO_ENABLE ; 
 int MCASP_WFIFOCTL_OFFSET ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int TXCLKRST ; 
 int TXFSRST ; 
 int TXHCLKRST ; 
 int /*<<< orphan*/  mcasp_clr_bits (struct davinci_mcasp*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mcasp_is_synchronous (struct davinci_mcasp*) ; 
 int /*<<< orphan*/  mcasp_set_axr_pdir (struct davinci_mcasp*,int) ; 
 int /*<<< orphan*/  mcasp_set_clk_pdir (struct davinci_mcasp*,int) ; 
 int /*<<< orphan*/  mcasp_set_reg (struct davinci_mcasp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcasp_stop_tx(struct davinci_mcasp *mcasp)
{
	u32 val = 0;

	/* disable IRQ sources */
	mcasp_clr_bits(mcasp, DAVINCI_MCASP_EVTCTLX_REG,
		       mcasp->irq_request[SNDRV_PCM_STREAM_PLAYBACK]);

	/*
	 * In synchronous mode keep TX clocks running if the capture stream is
	 * still running.
	 */
	if (mcasp_is_synchronous(mcasp) && mcasp->streams)
		val =  TXHCLKRST | TXCLKRST | TXFSRST;
	else
		mcasp_set_clk_pdir(mcasp, false);


	mcasp_set_reg(mcasp, DAVINCI_MCASP_GBLCTLX_REG, val);
	mcasp_set_reg(mcasp, DAVINCI_MCASP_TXSTAT_REG, 0xFFFFFFFF);

	if (mcasp->txnumevt) {	/* disable FIFO */
		u32 reg = mcasp->fifo_base + MCASP_WFIFOCTL_OFFSET;

		mcasp_clr_bits(mcasp, reg, FIFO_ENABLE);
	}

	mcasp_set_axr_pdir(mcasp, false);
}