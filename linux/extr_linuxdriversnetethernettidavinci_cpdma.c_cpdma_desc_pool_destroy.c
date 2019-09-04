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
struct cpdma_desc_pool {int /*<<< orphan*/  phys; scalar_t__ cpumap; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  gen_pool; } ;
struct cpdma_ctlr {int /*<<< orphan*/  dev; struct cpdma_desc_pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_pool_avail (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_pool_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpdma_desc_pool_destroy(struct cpdma_ctlr *ctlr)
{
	struct cpdma_desc_pool *pool = ctlr->pool;

	if (!pool)
		return;

	WARN(gen_pool_size(pool->gen_pool) != gen_pool_avail(pool->gen_pool),
	     "cpdma_desc_pool size %zd != avail %zd",
	     gen_pool_size(pool->gen_pool),
	     gen_pool_avail(pool->gen_pool));
	if (pool->cpumap)
		dma_free_coherent(ctlr->dev, pool->mem_size, pool->cpumap,
				  pool->phys);
}