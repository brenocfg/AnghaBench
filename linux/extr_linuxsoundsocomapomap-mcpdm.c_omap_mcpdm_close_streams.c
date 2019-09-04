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
struct omap_mcpdm {scalar_t__ dn_rx_offset; } ;

/* Variables and functions */
 int MCPDM_DMA_DN_ENABLE ; 
 int MCPDM_DMA_UP_ENABLE ; 
 int MCPDM_DN_IRQ_EMPTY ; 
 int MCPDM_DN_IRQ_FULL ; 
 int /*<<< orphan*/  MCPDM_REG_DMAENABLE_CLR ; 
 int /*<<< orphan*/  MCPDM_REG_DN_OFFSET ; 
 int /*<<< orphan*/  MCPDM_REG_IRQENABLE_CLR ; 
 int MCPDM_UP_IRQ_EMPTY ; 
 int MCPDM_UP_IRQ_FULL ; 
 int /*<<< orphan*/  omap_mcpdm_write (struct omap_mcpdm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_mcpdm_close_streams(struct omap_mcpdm *mcpdm)
{
	/* Disable irq request generation for downlink */
	omap_mcpdm_write(mcpdm, MCPDM_REG_IRQENABLE_CLR,
			MCPDM_DN_IRQ_EMPTY | MCPDM_DN_IRQ_FULL);

	/* Disable DMA request generation for downlink */
	omap_mcpdm_write(mcpdm, MCPDM_REG_DMAENABLE_CLR, MCPDM_DMA_DN_ENABLE);

	/* Disable irq request generation for uplink */
	omap_mcpdm_write(mcpdm, MCPDM_REG_IRQENABLE_CLR,
			MCPDM_UP_IRQ_EMPTY | MCPDM_UP_IRQ_FULL);

	/* Disable DMA request generation for uplink */
	omap_mcpdm_write(mcpdm, MCPDM_REG_DMAENABLE_CLR, MCPDM_DMA_UP_ENABLE);

	/* Disable RX1/2 offset cancellation */
	if (mcpdm->dn_rx_offset)
		omap_mcpdm_write(mcpdm, MCPDM_REG_DN_OFFSET, 0);
}