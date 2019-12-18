#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {struct mempolicy* vm_policy; TYPE_1__* vm_ops; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_9__ {int /*<<< orphan*/  user_nodemask; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {int mode; int flags; TYPE_3__ w; TYPE_2__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
struct TYPE_10__ {int /*<<< orphan*/  il_prev; struct mempolicy* mempolicy; struct mm_struct* mm; } ;
struct TYPE_7__ {struct mempolicy* (* get_policy ) (struct vm_area_struct*,unsigned long) ;} ;

/* Variables and functions */
 long EFAULT ; 
 long EINVAL ; 
 int MPOL_DEFAULT ; 
 unsigned long MPOL_F_ADDR ; 
 unsigned long MPOL_F_MEMS_ALLOWED ; 
 unsigned long MPOL_F_NODE ; 
 int MPOL_INTERLEAVE ; 
 int MPOL_MODE_FLAGS ; 
 int /*<<< orphan*/  cpuset_current_mems_allowed ; 
 TYPE_4__* current ; 
 struct mempolicy default_policy ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma_intersection (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get_policy_nodemask (struct mempolicy*,int /*<<< orphan*/ *) ; 
 int lookup_node (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  mpol_cond_put (struct mempolicy*) ; 
 int /*<<< orphan*/  mpol_get (struct mempolicy*) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 scalar_t__ mpol_store_user_nodemask (struct mempolicy*) ; 
 int next_node_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mempolicy* stub1 (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  task_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_4__*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long do_get_mempolicy(int *policy, nodemask_t *nmask,
			     unsigned long addr, unsigned long flags)
{
	int err;
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma = NULL;
	struct mempolicy *pol = current->mempolicy, *pol_refcount = NULL;

	if (flags &
		~(unsigned long)(MPOL_F_NODE|MPOL_F_ADDR|MPOL_F_MEMS_ALLOWED))
		return -EINVAL;

	if (flags & MPOL_F_MEMS_ALLOWED) {
		if (flags & (MPOL_F_NODE|MPOL_F_ADDR))
			return -EINVAL;
		*policy = 0;	/* just so it's initialized */
		task_lock(current);
		*nmask  = cpuset_current_mems_allowed;
		task_unlock(current);
		return 0;
	}

	if (flags & MPOL_F_ADDR) {
		/*
		 * Do NOT fall back to task policy if the
		 * vma/shared policy at addr is NULL.  We
		 * want to return MPOL_DEFAULT in this case.
		 */
		down_read(&mm->mmap_sem);
		vma = find_vma_intersection(mm, addr, addr+1);
		if (!vma) {
			up_read(&mm->mmap_sem);
			return -EFAULT;
		}
		if (vma->vm_ops && vma->vm_ops->get_policy)
			pol = vma->vm_ops->get_policy(vma, addr);
		else
			pol = vma->vm_policy;
	} else if (addr)
		return -EINVAL;

	if (!pol)
		pol = &default_policy;	/* indicates default behavior */

	if (flags & MPOL_F_NODE) {
		if (flags & MPOL_F_ADDR) {
			/*
			 * Take a refcount on the mpol, lookup_node()
			 * wil drop the mmap_sem, so after calling
			 * lookup_node() only "pol" remains valid, "vma"
			 * is stale.
			 */
			pol_refcount = pol;
			vma = NULL;
			mpol_get(pol);
			err = lookup_node(mm, addr);
			if (err < 0)
				goto out;
			*policy = err;
		} else if (pol == current->mempolicy &&
				pol->mode == MPOL_INTERLEAVE) {
			*policy = next_node_in(current->il_prev, pol->v.nodes);
		} else {
			err = -EINVAL;
			goto out;
		}
	} else {
		*policy = pol == &default_policy ? MPOL_DEFAULT :
						pol->mode;
		/*
		 * Internal mempolicy flags must be masked off before exposing
		 * the policy to userspace.
		 */
		*policy |= (pol->flags & MPOL_MODE_FLAGS);
	}

	err = 0;
	if (nmask) {
		if (mpol_store_user_nodemask(pol)) {
			*nmask = pol->w.user_nodemask;
		} else {
			task_lock(current);
			get_policy_nodemask(pol, nmask);
			task_unlock(current);
		}
	}

 out:
	mpol_cond_put(pol);
	if (vma)
		up_read(&mm->mmap_sem);
	if (pol_refcount)
		mpol_put(pol_refcount);
	return err;
}