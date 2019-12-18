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
struct vm_struct {scalar_t__ flags; struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ VM_DMA_COHERENT ; 
 struct vm_struct* find_vm_area (void*) ; 

struct page **dma_common_find_pages(void *cpu_addr)
{
	struct vm_struct *area = find_vm_area(cpu_addr);

	if (!area || area->flags != VM_DMA_COHERENT)
		return NULL;
	return area->pages;
}