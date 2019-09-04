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
struct vm_area_struct {unsigned int vm_pgoff; } ;
struct TYPE_2__ {unsigned int smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  screen_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_SHIFT ; 
 int dma_mmap_wc (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ep93xxfb_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	unsigned int offset = vma->vm_pgoff << PAGE_SHIFT;

	if (offset < info->fix.smem_len) {
		return dma_mmap_wc(info->dev, vma, info->screen_base,
				   info->fix.smem_start, info->fix.smem_len);
	}

	return -EINVAL;
}