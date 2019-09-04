#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vm_area_struct {unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct TYPE_4__ {unsigned long smem_start; unsigned long mmio_start; scalar_t__ mmio_len; scalar_t__ smem_len; } ;
struct TYPE_3__ {scalar_t__ accel_flags; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_ALIGN (scalar_t__) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  pgprot_cached_wthru (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int vm_iomap_memory (struct vm_area_struct*,unsigned long,scalar_t__) ; 

__attribute__((used)) static int controlfb_mmap(struct fb_info *info,
                       struct vm_area_struct *vma)
{
	unsigned long mmio_pgoff;
	unsigned long start;
	u32 len;

	start = info->fix.smem_start;
	len = info->fix.smem_len;
	mmio_pgoff = PAGE_ALIGN((start & ~PAGE_MASK) + len) >> PAGE_SHIFT;
	if (vma->vm_pgoff >= mmio_pgoff) {
		if (info->var.accel_flags)
			return -EINVAL;
		vma->vm_pgoff -= mmio_pgoff;
		start = info->fix.mmio_start;
		len = info->fix.mmio_len;
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	} else {
		/* framebuffer */
		vma->vm_page_prot = pgprot_cached_wthru(vma->vm_page_prot);
	}

	return vm_iomap_memory(vma, start, len);
}