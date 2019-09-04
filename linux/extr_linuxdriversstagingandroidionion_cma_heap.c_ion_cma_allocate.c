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
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct page {int dummy; } ;
struct ion_heap {int dummy; } ;
struct ion_cma_heap {int /*<<< orphan*/  cma; } ;
struct ion_buffer {struct sg_table* sg_table; struct page* priv_virt; } ;

/* Variables and functions */
 unsigned long CONFIG_CMA_ALIGNMENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 struct page* cma_alloc (int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  cma_release (int /*<<< orphan*/ ,struct page*,unsigned long) ; 
 unsigned long get_order (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 void* page_address (struct page*) ; 
 int sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ ,struct page*,unsigned long,int /*<<< orphan*/ ) ; 
 struct ion_cma_heap* to_cma_heap (struct ion_heap*) ; 

__attribute__((used)) static int ion_cma_allocate(struct ion_heap *heap, struct ion_buffer *buffer,
			    unsigned long len,
			    unsigned long flags)
{
	struct ion_cma_heap *cma_heap = to_cma_heap(heap);
	struct sg_table *table;
	struct page *pages;
	unsigned long size = PAGE_ALIGN(len);
	unsigned long nr_pages = size >> PAGE_SHIFT;
	unsigned long align = get_order(size);
	int ret;

	if (align > CONFIG_CMA_ALIGNMENT)
		align = CONFIG_CMA_ALIGNMENT;

	pages = cma_alloc(cma_heap->cma, nr_pages, align, false);
	if (!pages)
		return -ENOMEM;

	if (PageHighMem(pages)) {
		unsigned long nr_clear_pages = nr_pages;
		struct page *page = pages;

		while (nr_clear_pages > 0) {
			void *vaddr = kmap_atomic(page);

			memset(vaddr, 0, PAGE_SIZE);
			kunmap_atomic(vaddr);
			page++;
			nr_clear_pages--;
		}
	} else {
		memset(page_address(pages), 0, size);
	}

	table = kmalloc(sizeof(*table), GFP_KERNEL);
	if (!table)
		goto err;

	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret)
		goto free_mem;

	sg_set_page(table->sgl, pages, size, 0);

	buffer->priv_virt = pages;
	buffer->sg_table = table;
	return 0;

free_mem:
	kfree(table);
err:
	cma_release(cma_heap->cma, pages, nr_pages);
	return -ENOMEM;
}