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
 int /*<<< orphan*/  ETDES0_OWN ; 
 int STMMAC_CHAIN_MODE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enh_desc_end_tx_desc_on_chain (struct dma_desc*) ; 
 int /*<<< orphan*/  enh_desc_end_tx_desc_on_ring (struct dma_desc*,int) ; 

__attribute__((used)) static void enh_desc_init_tx_desc(struct dma_desc *p, int mode, int end)
{
	p->des0 &= cpu_to_le32(~ETDES0_OWN);
	if (mode == STMMAC_CHAIN_MODE)
		enh_desc_end_tx_desc_on_chain(p);
	else
		enh_desc_end_tx_desc_on_ring(p, end);
}