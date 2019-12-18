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
struct gen_pool {int /*<<< orphan*/  data; int /*<<< orphan*/  algo; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* gen_pool_dma_zalloc_algo (struct gen_pool*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *gen_pool_dma_zalloc(struct gen_pool *pool, size_t size, dma_addr_t *dma)
{
	return gen_pool_dma_zalloc_algo(pool, size, dma, pool->algo, pool->data);
}