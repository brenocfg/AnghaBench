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
struct nfit_test {int dummy; } ;
struct genpool_data_align {int /*<<< orphan*/  align; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 size_t DIMM_SIZE ; 
 int /*<<< orphan*/  SZ_128M ; 
 void* __test_alloc (struct nfit_test*,size_t,unsigned long*,void*) ; 
 unsigned long gen_pool_alloc_algo (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,struct genpool_data_align*) ; 
 int /*<<< orphan*/  gen_pool_first_fit_align ; 
 int /*<<< orphan*/  nfit_pool ; 
 void* vmalloc (size_t) ; 

__attribute__((used)) static void *test_alloc(struct nfit_test *t, size_t size, dma_addr_t *dma)
{
	struct genpool_data_align data = {
		.align = SZ_128M,
	};
	void *buf = vmalloc(size);

	if (size >= DIMM_SIZE)
		*dma = gen_pool_alloc_algo(nfit_pool, size,
				gen_pool_first_fit_align, &data);
	else
		*dma = (unsigned long) buf;
	return __test_alloc(t, size, dma, buf);
}