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
struct vm_area_struct {int vm_start; int vm_flags; int vm_pgoff; int /*<<< orphan*/  anon_vma; int /*<<< orphan*/  vm_end; } ;
struct rb_node {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int VM_ACCOUNT ; 
 scalar_t__ find_vma_links (struct mm_struct*,int,int /*<<< orphan*/ ,struct vm_area_struct**,struct rb_node***,struct rb_node**) ; 
 scalar_t__ security_vm_enough_memory_mm (struct mm_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ vma_is_anonymous (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_link (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,struct rb_node**,struct rb_node*) ; 
 int /*<<< orphan*/  vma_pages (struct vm_area_struct*) ; 

int insert_vm_struct(struct mm_struct *mm, struct vm_area_struct *vma)
{
	struct vm_area_struct *prev;
	struct rb_node **rb_link, *rb_parent;

	if (find_vma_links(mm, vma->vm_start, vma->vm_end,
			   &prev, &rb_link, &rb_parent))
		return -ENOMEM;
	if ((vma->vm_flags & VM_ACCOUNT) &&
	     security_vm_enough_memory_mm(mm, vma_pages(vma)))
		return -ENOMEM;

	/*
	 * The vm_pgoff of a purely anonymous vma should be irrelevant
	 * until its first write fault, when page's anon_vma and index
	 * are set.  But now set the vm_pgoff it will almost certainly
	 * end up with (unless mremap moves it elsewhere before that
	 * first wfault), so /proc/pid/maps tells a consistent story.
	 *
	 * By setting it to reflect the virtual start address of the
	 * vma, merges and splits can happen in a seamless way, just
	 * using the existing file pgoff checks and manipulations.
	 * Similarly in do_mmap_pgoff and in do_brk.
	 */
	if (vma_is_anonymous(vma)) {
		BUG_ON(vma->anon_vma);
		vma->vm_pgoff = vma->vm_start >> PAGE_SHIFT;
	}

	vma_link(mm, vma, prev, rb_link, rb_parent);
	return 0;
}