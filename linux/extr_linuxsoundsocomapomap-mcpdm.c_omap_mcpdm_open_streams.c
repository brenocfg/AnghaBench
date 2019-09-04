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
typedef  int u32 ;
struct omap_mcpdm {int dn_rx_offset; TYPE_1__* config; } ;
struct TYPE_2__ {int threshold; } ;

/* Variables and functions */
 int MCPDM_DMA_DN_ENABLE ; 
 int MCPDM_DMA_UP_ENABLE ; 
 int MCPDM_DN_IRQ_EMPTY ; 
 int MCPDM_DN_IRQ_FULL ; 
 int MCPDM_DN_OFST_RX1_EN ; 
 int MCPDM_DN_OFST_RX2_EN ; 
 int /*<<< orphan*/  MCPDM_REG_CTRL ; 
 int /*<<< orphan*/  MCPDM_REG_DMAENABLE_SET ; 
 int /*<<< orphan*/  MCPDM_REG_DN_OFFSET ; 
 int /*<<< orphan*/  MCPDM_REG_FIFO_CTRL_DN ; 
 int /*<<< orphan*/  MCPDM_REG_FIFO_CTRL_UP ; 
 int /*<<< orphan*/  MCPDM_REG_IRQENABLE_SET ; 
 int MCPDM_UP_IRQ_EMPTY ; 
 int MCPDM_UP_IRQ_FULL ; 
 int MCPDM_WD_EN ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int omap_mcpdm_read (struct omap_mcpdm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_mcpdm_write (struct omap_mcpdm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_mcpdm_open_streams(struct omap_mcpdm *mcpdm)
{
	u32 ctrl = omap_mcpdm_read(mcpdm, MCPDM_REG_CTRL);

	omap_mcpdm_write(mcpdm, MCPDM_REG_CTRL, ctrl | MCPDM_WD_EN);

	omap_mcpdm_write(mcpdm, MCPDM_REG_IRQENABLE_SET,
			MCPDM_DN_IRQ_EMPTY | MCPDM_DN_IRQ_FULL |
			MCPDM_UP_IRQ_EMPTY | MCPDM_UP_IRQ_FULL);

	/* Enable DN RX1/2 offset cancellation feature, if configured */
	if (mcpdm->dn_rx_offset) {
		u32 dn_offset = mcpdm->dn_rx_offset;

		omap_mcpdm_write(mcpdm, MCPDM_REG_DN_OFFSET, dn_offset);
		dn_offset |= (MCPDM_DN_OFST_RX1_EN | MCPDM_DN_OFST_RX2_EN);
		omap_mcpdm_write(mcpdm, MCPDM_REG_DN_OFFSET, dn_offset);
	}

	omap_mcpdm_write(mcpdm, MCPDM_REG_FIFO_CTRL_DN,
			 mcpdm->config[SNDRV_PCM_STREAM_PLAYBACK].threshold);
	omap_mcpdm_write(mcpdm, MCPDM_REG_FIFO_CTRL_UP,
			 mcpdm->config[SNDRV_PCM_STREAM_CAPTURE].threshold);

	omap_mcpdm_write(mcpdm, MCPDM_REG_DMAENABLE_SET,
			MCPDM_DMA_DN_ENABLE | MCPDM_DMA_UP_ENABLE);
}