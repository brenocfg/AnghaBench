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
struct wcn36xx_dxe_mem_pool {int chunk_size; int phy_addr; void* virt_addr; } ;
struct wcn36xx_dxe_ctl {int bd_phy_addr; struct wcn36xx_dxe_ctl* next; int /*<<< orphan*/ * bd_cpu_addr; } ;
struct wcn36xx_dxe_ch {int desc_num; struct wcn36xx_dxe_ctl* head_blk_ctl; } ;
typedef  int dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static void wcn36xx_dxe_init_tx_bd(struct wcn36xx_dxe_ch *ch,
				   struct wcn36xx_dxe_mem_pool *pool)
{
	int i, chunk_size = pool->chunk_size;
	dma_addr_t bd_phy_addr = pool->phy_addr;
	void *bd_cpu_addr = pool->virt_addr;
	struct wcn36xx_dxe_ctl *cur = ch->head_blk_ctl;

	for (i = 0; i < ch->desc_num; i++) {
		/* Only every second dxe needs a bd pointer,
		   the other will point to the skb data */
		if (!(i & 1)) {
			cur->bd_phy_addr = bd_phy_addr;
			cur->bd_cpu_addr = bd_cpu_addr;
			bd_phy_addr += chunk_size;
			bd_cpu_addr += chunk_size;
		} else {
			cur->bd_phy_addr = 0;
			cur->bd_cpu_addr = NULL;
		}
		cur = cur->next;
	}
}