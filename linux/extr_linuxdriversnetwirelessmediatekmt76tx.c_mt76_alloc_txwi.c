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
struct mt76_txwi_cache {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  txwi; } ;
struct mt76_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int L1_CACHE_BYTES ; 
 struct mt76_txwi_cache* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mt76_txwi_cache *
mt76_alloc_txwi(struct mt76_dev *dev)
{
	struct mt76_txwi_cache *t;
	dma_addr_t addr;
	int size;

	size = (sizeof(*t) + L1_CACHE_BYTES - 1) & ~(L1_CACHE_BYTES - 1);
	t = devm_kzalloc(dev->dev, size, GFP_ATOMIC);
	if (!t)
		return NULL;

	addr = dma_map_single(dev->dev, &t->txwi, sizeof(t->txwi),
			      DMA_TO_DEVICE);
	t->dma_addr = addr;

	return t;
}