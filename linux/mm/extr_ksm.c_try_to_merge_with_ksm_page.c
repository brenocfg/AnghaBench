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
struct vm_area_struct {int /*<<< orphan*/  anon_vma; } ;
struct rmap_item {int /*<<< orphan*/  anon_vma; int /*<<< orphan*/  address; struct mm_struct* mm; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_mergeable_vma (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_anon_vma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_rmap_item_from_tree (struct rmap_item*) ; 
 int try_to_merge_one_page (struct vm_area_struct*,struct page*,struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_to_merge_with_ksm_page(struct rmap_item *rmap_item,
				      struct page *page, struct page *kpage)
{
	struct mm_struct *mm = rmap_item->mm;
	struct vm_area_struct *vma;
	int err = -EFAULT;

	down_read(&mm->mmap_sem);
	vma = find_mergeable_vma(mm, rmap_item->address);
	if (!vma)
		goto out;

	err = try_to_merge_one_page(vma, page, kpage);
	if (err)
		goto out;

	/* Unstable nid is in union with stable anon_vma: remove first */
	remove_rmap_item_from_tree(rmap_item);

	/* Must get reference to anon_vma while still holding mmap_sem */
	rmap_item->anon_vma = vma->anon_vma;
	get_anon_vma(vma->anon_vma);
out:
	up_read(&mm->mmap_sem);
	return err;
}