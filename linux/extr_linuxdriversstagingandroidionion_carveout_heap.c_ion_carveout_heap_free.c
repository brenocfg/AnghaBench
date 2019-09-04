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
struct ion_buffer {int /*<<< orphan*/  size; struct sg_table* sg_table; struct ion_heap* heap; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PFN_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ion_carveout_free (struct ion_heap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ion_heap_buffer_zero (struct ion_buffer*) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 struct page* sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ion_carveout_heap_free(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;
	struct sg_table *table = buffer->sg_table;
	struct page *page = sg_page(table->sgl);
	phys_addr_t paddr = PFN_PHYS(page_to_pfn(page));

	ion_heap_buffer_zero(buffer);

	ion_carveout_free(heap, paddr, buffer->size);
	sg_free_table(table);
	kfree(table);
}