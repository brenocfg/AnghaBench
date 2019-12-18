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
struct vm_area_struct {unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_start; } ;
struct dma_coherent_mem {void* virt_base; int size; int pfn_base; } ;

/* Variables and functions */
 int ENXIO ; 
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 int remap_pfn_range (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 int vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int __dma_mmap_from_coherent(struct dma_coherent_mem *mem,
		struct vm_area_struct *vma, void *vaddr, size_t size, int *ret)
{
	if (mem && vaddr >= mem->virt_base && vaddr + size <=
		   (mem->virt_base + (mem->size << PAGE_SHIFT))) {
		unsigned long off = vma->vm_pgoff;
		int start = (vaddr - mem->virt_base) >> PAGE_SHIFT;
		int user_count = vma_pages(vma);
		int count = PAGE_ALIGN(size) >> PAGE_SHIFT;

		*ret = -ENXIO;
		if (off < count && user_count <= count - off) {
			unsigned long pfn = mem->pfn_base + start + off;
			*ret = remap_pfn_range(vma, vma->vm_start, pfn,
					       user_count << PAGE_SHIFT,
					       vma->vm_page_prot);
		}
		return 1;
	}
	return 0;
}