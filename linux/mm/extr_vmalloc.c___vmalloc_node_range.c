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
struct vm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long VM_ALLOC ; 
 unsigned long VM_UNINITIALIZED ; 
 struct vm_struct* __get_vm_area_node (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,int,int /*<<< orphan*/ ,void const*) ; 
 void* __vmalloc_area_node (struct vm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_vm_uninitialized_flag (struct vm_struct*) ; 
 int /*<<< orphan*/  kmemleak_vmalloc (struct vm_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long totalram_pages () ; 
 int /*<<< orphan*/  warn_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned long) ; 

void *__vmalloc_node_range(unsigned long size, unsigned long align,
			unsigned long start, unsigned long end, gfp_t gfp_mask,
			pgprot_t prot, unsigned long vm_flags, int node,
			const void *caller)
{
	struct vm_struct *area;
	void *addr;
	unsigned long real_size = size;

	size = PAGE_ALIGN(size);
	if (!size || (size >> PAGE_SHIFT) > totalram_pages())
		goto fail;

	area = __get_vm_area_node(size, align, VM_ALLOC | VM_UNINITIALIZED |
				vm_flags, start, end, node, gfp_mask, caller);
	if (!area)
		goto fail;

	addr = __vmalloc_area_node(area, gfp_mask, prot, node);
	if (!addr)
		return NULL;

	/*
	 * In this function, newly allocated vm_struct has VM_UNINITIALIZED
	 * flag. It means that vm_struct is not fully initialized.
	 * Now, it is fully initialized, so remove this flag here.
	 */
	clear_vm_uninitialized_flag(area);

	kmemleak_vmalloc(area, size, gfp_mask);

	return addr;

fail:
	warn_alloc(gfp_mask, NULL,
			  "vmalloc: allocation failure: %lu bytes", real_size);
	return NULL;
}