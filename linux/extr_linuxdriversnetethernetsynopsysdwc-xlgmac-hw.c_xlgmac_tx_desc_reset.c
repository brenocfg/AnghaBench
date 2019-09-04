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
struct xlgmac_dma_desc {scalar_t__ desc3; scalar_t__ desc2; scalar_t__ desc1; scalar_t__ desc0; } ;
struct xlgmac_desc_data {struct xlgmac_dma_desc* dma_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_wmb () ; 

__attribute__((used)) static void xlgmac_tx_desc_reset(struct xlgmac_desc_data *desc_data)
{
	struct xlgmac_dma_desc *dma_desc = desc_data->dma_desc;

	/* Reset the Tx descriptor
	 *   Set buffer 1 (lo) address to zero
	 *   Set buffer 1 (hi) address to zero
	 *   Reset all other control bits (IC, TTSE, B2L & B1L)
	 *   Reset all other control bits (OWN, CTXT, FD, LD, CPC, CIC, etc)
	 */
	dma_desc->desc0 = 0;
	dma_desc->desc1 = 0;
	dma_desc->desc2 = 0;
	dma_desc->desc3 = 0;

	/* Make sure ownership is written to the descriptor */
	dma_wmb();
}