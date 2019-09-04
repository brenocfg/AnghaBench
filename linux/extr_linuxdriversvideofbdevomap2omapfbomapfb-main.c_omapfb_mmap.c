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
typedef  int /*<<< orphan*/  u32 ;
struct vm_area_struct {int vm_pgoff; struct omapfb2_mem_region* vm_private_data; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; } ;
struct omapfb_info {struct omapfb2_mem_region* region; } ;
struct omapfb2_mem_region {int /*<<< orphan*/  map_count; } ;
struct fb_fix_screeninfo {int /*<<< orphan*/  smem_len; } ;
struct fb_info {struct fb_fix_screeninfo fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long,int /*<<< orphan*/ ,int) ; 
 struct omapfb_info* FB2OFB (struct fb_info*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmap_user_ops ; 
 struct omapfb2_mem_region* omapfb_get_mem_region (struct omapfb2_mem_region*) ; 
 unsigned long omapfb_get_region_paddr (struct omapfb_info*) ; 
 int /*<<< orphan*/  omapfb_put_mem_region (struct omapfb2_mem_region*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int vm_iomap_memory (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapfb_mmap(struct fb_info *fbi, struct vm_area_struct *vma)
{
	struct omapfb_info *ofbi = FB2OFB(fbi);
	struct fb_fix_screeninfo *fix = &fbi->fix;
	struct omapfb2_mem_region *rg;
	unsigned long start;
	u32 len;
	int r;

	rg = omapfb_get_mem_region(ofbi->region);

	start = omapfb_get_region_paddr(ofbi);
	len = fix->smem_len;

	DBG("user mmap region start %lx, len %d, off %lx\n", start, len,
			vma->vm_pgoff << PAGE_SHIFT);

	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	vma->vm_ops = &mmap_user_ops;
	vma->vm_private_data = rg;

	r = vm_iomap_memory(vma, start, len);
	if (r)
		goto error;

	/* vm_ops.open won't be called for mmap itself. */
	atomic_inc(&rg->map_count);

	omapfb_put_mem_region(rg);

	return 0;

error:
	omapfb_put_mem_region(ofbi->region);

	return r;
}