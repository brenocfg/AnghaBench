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
struct vm_struct {void* addr; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PAGE_SHIFT ; 
 struct vm_struct* __dma_common_pages_remap (struct page**,size_t,int /*<<< orphan*/ ,void const*) ; 
 int get_order (size_t) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc (int,int /*<<< orphan*/ ) ; 
 struct page* nth_page (struct page*,int) ; 

void *dma_common_contiguous_remap(struct page *page, size_t size,
			pgprot_t prot, const void *caller)
{
	int i;
	struct page **pages;
	struct vm_struct *area;

	pages = kmalloc(sizeof(struct page *) << get_order(size), GFP_KERNEL);
	if (!pages)
		return NULL;

	for (i = 0; i < (size >> PAGE_SHIFT); i++)
		pages[i] = nth_page(page, i);

	area = __dma_common_pages_remap(pages, size, prot, caller);

	kfree(pages);

	if (!area)
		return NULL;
	return area->addr;
}