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
struct page {int dummy; } ;
struct ion_platform_heap {size_t size; int /*<<< orphan*/  base; } ;
struct ion_heap {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct ion_carveout_heap {struct ion_heap heap; int /*<<< orphan*/  base; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ion_heap* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ION_HEAP_FLAG_DEFER_FREE ; 
 int /*<<< orphan*/  ION_HEAP_TYPE_CARVEOUT ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carveout_heap_ops ; 
 int /*<<< orphan*/  gen_pool_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  gen_pool_create (int /*<<< orphan*/ ,int) ; 
 int ion_heap_pages_zero (struct page*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ion_carveout_heap*) ; 
 struct ion_carveout_heap* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 

struct ion_heap *ion_carveout_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_carveout_heap *carveout_heap;
	int ret;

	struct page *page;
	size_t size;

	page = pfn_to_page(PFN_DOWN(heap_data->base));
	size = heap_data->size;

	ret = ion_heap_pages_zero(page, size, pgprot_writecombine(PAGE_KERNEL));
	if (ret)
		return ERR_PTR(ret);

	carveout_heap = kzalloc(sizeof(*carveout_heap), GFP_KERNEL);
	if (!carveout_heap)
		return ERR_PTR(-ENOMEM);

	carveout_heap->pool = gen_pool_create(PAGE_SHIFT, -1);
	if (!carveout_heap->pool) {
		kfree(carveout_heap);
		return ERR_PTR(-ENOMEM);
	}
	carveout_heap->base = heap_data->base;
	gen_pool_add(carveout_heap->pool, carveout_heap->base, heap_data->size,
		     -1);
	carveout_heap->heap.ops = &carveout_heap_ops;
	carveout_heap->heap.type = ION_HEAP_TYPE_CARVEOUT;
	carveout_heap->heap.flags = ION_HEAP_FLAG_DEFER_FREE;

	return &carveout_heap->heap;
}