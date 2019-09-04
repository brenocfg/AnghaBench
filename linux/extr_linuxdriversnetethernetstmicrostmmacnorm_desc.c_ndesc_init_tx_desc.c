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
struct dma_desc {int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 int STMMAC_CHAIN_MODE ; 
 int /*<<< orphan*/  TDES0_OWN ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndesc_end_tx_desc_on_ring (struct dma_desc*,int) ; 
 int /*<<< orphan*/  ndesc_tx_set_on_chain (struct dma_desc*) ; 

__attribute__((used)) static void ndesc_init_tx_desc(struct dma_desc *p, int mode, int end)
{
	p->des0 &= cpu_to_le32(~TDES0_OWN);
	if (mode == STMMAC_CHAIN_MODE)
		ndesc_tx_set_on_chain(p);
	else
		ndesc_end_tx_desc_on_ring(p, end);
}