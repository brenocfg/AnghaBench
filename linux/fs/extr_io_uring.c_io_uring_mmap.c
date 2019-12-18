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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_pgoff; } ;
struct page {int dummy; } ;
struct io_ring_ctx {void* sq_sqes; void* rings; } ;
struct file {struct io_ring_ctx* private_data; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
#define  IORING_OFF_CQ_RING 130 
#define  IORING_OFF_SQES 129 
#define  IORING_OFF_SQ_RING 128 
 int PAGE_SHIFT ; 
 unsigned long page_size (struct page*) ; 
 int remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct page* virt_to_head_page (void*) ; 
 int virt_to_phys (void*) ; 

__attribute__((used)) static int io_uring_mmap(struct file *file, struct vm_area_struct *vma)
{
	loff_t offset = (loff_t) vma->vm_pgoff << PAGE_SHIFT;
	unsigned long sz = vma->vm_end - vma->vm_start;
	struct io_ring_ctx *ctx = file->private_data;
	unsigned long pfn;
	struct page *page;
	void *ptr;

	switch (offset) {
	case IORING_OFF_SQ_RING:
	case IORING_OFF_CQ_RING:
		ptr = ctx->rings;
		break;
	case IORING_OFF_SQES:
		ptr = ctx->sq_sqes;
		break;
	default:
		return -EINVAL;
	}

	page = virt_to_head_page(ptr);
	if (sz > page_size(page))
		return -EINVAL;

	pfn = virt_to_phys(ptr) >> PAGE_SHIFT;
	return remap_pfn_range(vma, vma->vm_start, pfn, sz, vma->vm_page_prot);
}