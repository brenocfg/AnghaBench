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
struct vm_area_struct {scalar_t__ anon_vma; struct vm_area_struct* vm_next; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int unuse_vma (struct vm_area_struct*,unsigned int,int,unsigned long*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unuse_mm(struct mm_struct *mm, unsigned int type,
		    bool frontswap, unsigned long *fs_pages_to_unuse)
{
	struct vm_area_struct *vma;
	int ret = 0;

	down_read(&mm->mmap_sem);
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		if (vma->anon_vma) {
			ret = unuse_vma(vma, type, frontswap,
					fs_pages_to_unuse);
			if (ret)
				break;
		}
		cond_resched();
	}
	up_read(&mm->mmap_sem);
	return ret;
}