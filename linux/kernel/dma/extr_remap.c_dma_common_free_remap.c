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
struct vm_struct {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 scalar_t__ VM_DMA_COHERENT ; 
 int /*<<< orphan*/  WARN (int,char*,void*) ; 
 struct vm_struct* find_vm_area (void*) ; 
 int /*<<< orphan*/  unmap_kernel_range (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

void dma_common_free_remap(void *cpu_addr, size_t size)
{
	struct vm_struct *area = find_vm_area(cpu_addr);

	if (!area || area->flags != VM_DMA_COHERENT) {
		WARN(1, "trying to free invalid coherent area: %p\n", cpu_addr);
		return;
	}

	unmap_kernel_range((unsigned long)cpu_addr, PAGE_ALIGN(size));
	vunmap(cpu_addr);
}