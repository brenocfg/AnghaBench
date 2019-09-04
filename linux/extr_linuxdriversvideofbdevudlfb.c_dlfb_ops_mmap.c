#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; } ;
struct TYPE_2__ {unsigned long smem_len; scalar_t__ smem_start; } ;
struct fb_info {int /*<<< orphan*/  dev; TYPE_1__ fix; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long vmalloc_to_pfn (void*) ; 

__attribute__((used)) static int dlfb_ops_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	unsigned long start = vma->vm_start;
	unsigned long size = vma->vm_end - vma->vm_start;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long page, pos;

	if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		return -EINVAL;
	if (size > info->fix.smem_len)
		return -EINVAL;
	if (offset > info->fix.smem_len - size)
		return -EINVAL;

	pos = (unsigned long)info->fix.smem_start + offset;

	dev_dbg(info->dev, "mmap() framebuffer addr:%lu size:%lu\n",
		pos, size);

	while (size > 0) {
		page = vmalloc_to_pfn((void *)pos);
		if (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED))
			return -EAGAIN;

		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		else
			size = 0;
	}

	return 0;
}