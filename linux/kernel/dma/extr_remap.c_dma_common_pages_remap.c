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
struct vm_struct {void* addr; struct page** pages; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 struct vm_struct* __dma_common_pages_remap (struct page**,size_t,int /*<<< orphan*/ ,void const*) ; 

void *dma_common_pages_remap(struct page **pages, size_t size,
			 pgprot_t prot, const void *caller)
{
	struct vm_struct *area;

	area = __dma_common_pages_remap(pages, size, prot, caller);
	if (!area)
		return NULL;

	area->pages = pages;

	return area->addr;
}