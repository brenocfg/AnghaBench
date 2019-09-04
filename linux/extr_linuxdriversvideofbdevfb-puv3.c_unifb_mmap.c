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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int vm_iomap_memory (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int unifb_mmap(struct fb_info *info,
		    struct vm_area_struct *vma)
{
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return vm_iomap_memory(vma, info->fix.smem_start, info->fix.smem_len);
}