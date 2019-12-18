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
struct gen_pool {int dummy; } ;
typedef  int /*<<< orphan*/  genpool_algo_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long gen_pool_alloc_algo (struct gen_pool*,size_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gen_pool_virt_to_phys (struct gen_pool*,unsigned long) ; 

void *gen_pool_dma_alloc_algo(struct gen_pool *pool, size_t size,
		dma_addr_t *dma, genpool_algo_t algo, void *data)
{
	unsigned long vaddr;

	if (!pool)
		return NULL;

	vaddr = gen_pool_alloc_algo(pool, size, algo, data);
	if (!vaddr)
		return NULL;

	if (dma)
		*dma = gen_pool_virt_to_phys(pool, vaddr);

	return (void *)vaddr;
}