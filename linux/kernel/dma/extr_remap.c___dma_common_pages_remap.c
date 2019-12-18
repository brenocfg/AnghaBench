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
struct vm_struct {int /*<<< orphan*/  addr; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_DMA_COHERENT ; 
 struct vm_struct* get_vm_area_caller (size_t,int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ map_vm_area (struct vm_struct*,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vm_struct *__dma_common_pages_remap(struct page **pages,
			size_t size, pgprot_t prot, const void *caller)
{
	struct vm_struct *area;

	area = get_vm_area_caller(size, VM_DMA_COHERENT, caller);
	if (!area)
		return NULL;

	if (map_vm_area(area, prot, pages)) {
		vunmap(area->addr);
		return NULL;
	}

	return area;
}