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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; TYPE_1__* vm_ops; scalar_t__ vm_file; int /*<<< orphan*/  vm_userfaultfd_ctx; int /*<<< orphan*/  anon_vma; int /*<<< orphan*/  vm_flags; struct mm_struct* vm_mm; } ;
struct rb_node {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  unsigned long pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* open ) (struct vm_area_struct*) ;} ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 scalar_t__ anon_vma_clone (struct vm_area_struct*,struct vm_area_struct*) ; 
 scalar_t__ find_vma_links (struct mm_struct*,unsigned long,unsigned long,struct vm_area_struct**,struct rb_node***,struct rb_node**) ; 
 int /*<<< orphan*/  get_file (scalar_t__) ; 
 int /*<<< orphan*/  mpol_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 
 struct vm_area_struct* vm_area_dup (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_area_free (struct vm_area_struct*) ; 
 scalar_t__ vma_dup_policy (struct vm_area_struct*,struct vm_area_struct*) ; 
 scalar_t__ vma_is_anonymous (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_link (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,struct rb_node**,struct rb_node*) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

struct vm_area_struct *copy_vma(struct vm_area_struct **vmap,
	unsigned long addr, unsigned long len, pgoff_t pgoff,
	bool *need_rmap_locks)
{
	struct vm_area_struct *vma = *vmap;
	unsigned long vma_start = vma->vm_start;
	struct mm_struct *mm = vma->vm_mm;
	struct vm_area_struct *new_vma, *prev;
	struct rb_node **rb_link, *rb_parent;
	bool faulted_in_anon_vma = true;

	/*
	 * If anonymous vma has not yet been faulted, update new pgoff
	 * to match new location, to increase its chance of merging.
	 */
	if (unlikely(vma_is_anonymous(vma) && !vma->anon_vma)) {
		pgoff = addr >> PAGE_SHIFT;
		faulted_in_anon_vma = false;
	}

	if (find_vma_links(mm, addr, addr + len, &prev, &rb_link, &rb_parent))
		return NULL;	/* should never get here */
	new_vma = vma_merge(mm, prev, addr, addr + len, vma->vm_flags,
			    vma->anon_vma, vma->vm_file, pgoff, vma_policy(vma),
			    vma->vm_userfaultfd_ctx);
	if (new_vma) {
		/*
		 * Source vma may have been merged into new_vma
		 */
		if (unlikely(vma_start >= new_vma->vm_start &&
			     vma_start < new_vma->vm_end)) {
			/*
			 * The only way we can get a vma_merge with
			 * self during an mremap is if the vma hasn't
			 * been faulted in yet and we were allowed to
			 * reset the dst vma->vm_pgoff to the
			 * destination address of the mremap to allow
			 * the merge to happen. mremap must change the
			 * vm_pgoff linearity between src and dst vmas
			 * (in turn preventing a vma_merge) to be
			 * safe. It is only safe to keep the vm_pgoff
			 * linear if there are no pages mapped yet.
			 */
			VM_BUG_ON_VMA(faulted_in_anon_vma, new_vma);
			*vmap = vma = new_vma;
		}
		*need_rmap_locks = (new_vma->vm_pgoff <= vma->vm_pgoff);
	} else {
		new_vma = vm_area_dup(vma);
		if (!new_vma)
			goto out;
		new_vma->vm_start = addr;
		new_vma->vm_end = addr + len;
		new_vma->vm_pgoff = pgoff;
		if (vma_dup_policy(vma, new_vma))
			goto out_free_vma;
		if (anon_vma_clone(new_vma, vma))
			goto out_free_mempol;
		if (new_vma->vm_file)
			get_file(new_vma->vm_file);
		if (new_vma->vm_ops && new_vma->vm_ops->open)
			new_vma->vm_ops->open(new_vma);
		vma_link(mm, new_vma, prev, rb_link, rb_parent);
		*need_rmap_locks = false;
	}
	return new_vma;

out_free_mempol:
	mpol_put(vma_policy(new_vma));
out_free_vma:
	vm_area_free(new_vma);
out:
	return NULL;
}