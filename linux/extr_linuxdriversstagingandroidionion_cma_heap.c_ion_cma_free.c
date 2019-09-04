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
struct ion_cma_heap {int /*<<< orphan*/  cma; } ;
struct ion_buffer {int /*<<< orphan*/  sg_table; int /*<<< orphan*/  size; struct page* priv_virt; int /*<<< orphan*/  heap; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  cma_release (int /*<<< orphan*/ ,struct page*,unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (int /*<<< orphan*/ ) ; 
 struct ion_cma_heap* to_cma_heap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ion_cma_free(struct ion_buffer *buffer)
{
	struct ion_cma_heap *cma_heap = to_cma_heap(buffer->heap);
	struct page *pages = buffer->priv_virt;
	unsigned long nr_pages = PAGE_ALIGN(buffer->size) >> PAGE_SHIFT;

	/* release memory */
	cma_release(cma_heap->cma, pages, nr_pages);
	/* release sg table */
	sg_free_table(buffer->sg_table);
	kfree(buffer->sg_table);
}