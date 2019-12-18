#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct mempolicy {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 long EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 long EPERM ; 
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIGRATE_SYNC ; 
 unsigned short MPOL_DEFAULT ; 
 int /*<<< orphan*/  MPOL_F_MOF ; 
 unsigned long MPOL_MF_DISCONTIG_OK ; 
 unsigned long MPOL_MF_INVERT ; 
 unsigned long MPOL_MF_LAZY ; 
 unsigned long MPOL_MF_MOVE ; 
 unsigned long MPOL_MF_MOVE_ALL ; 
 unsigned long MPOL_MF_STRICT ; 
 scalar_t__ MPOL_MF_VALID ; 
 int /*<<< orphan*/  MR_MEMPOLICY_MBIND ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH (scalar_t__) ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH_FREE (scalar_t__) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 long PTR_ERR (struct mempolicy*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned long) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int mbind_range (struct mm_struct*,unsigned long,unsigned long,struct mempolicy*) ; 
 int migrate_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int migrate_prep () ; 
 struct mempolicy* mpol_new (unsigned short,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int mpol_set_nodemask (struct mempolicy*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  new_page ; 
 int /*<<< orphan*/ * nodes_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagelist ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long,unsigned short,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putback_movable_pages (int /*<<< orphan*/ *) ; 
 int queue_pages_range (struct mm_struct*,unsigned long,unsigned long,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ scratch ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long do_mbind(unsigned long start, unsigned long len,
		     unsigned short mode, unsigned short mode_flags,
		     nodemask_t *nmask, unsigned long flags)
{
	struct mm_struct *mm = current->mm;
	struct mempolicy *new;
	unsigned long end;
	int err;
	int ret;
	LIST_HEAD(pagelist);

	if (flags & ~(unsigned long)MPOL_MF_VALID)
		return -EINVAL;
	if ((flags & MPOL_MF_MOVE_ALL) && !capable(CAP_SYS_NICE))
		return -EPERM;

	if (start & ~PAGE_MASK)
		return -EINVAL;

	if (mode == MPOL_DEFAULT)
		flags &= ~MPOL_MF_STRICT;

	len = (len + PAGE_SIZE - 1) & PAGE_MASK;
	end = start + len;

	if (end < start)
		return -EINVAL;
	if (end == start)
		return 0;

	new = mpol_new(mode, mode_flags, nmask);
	if (IS_ERR(new))
		return PTR_ERR(new);

	if (flags & MPOL_MF_LAZY)
		new->flags |= MPOL_F_MOF;

	/*
	 * If we are using the default policy then operation
	 * on discontinuous address spaces is okay after all
	 */
	if (!new)
		flags |= MPOL_MF_DISCONTIG_OK;

	pr_debug("mbind %lx-%lx mode:%d flags:%d nodes:%lx\n",
		 start, start + len, mode, mode_flags,
		 nmask ? nodes_addr(*nmask)[0] : NUMA_NO_NODE);

	if (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) {

		err = migrate_prep();
		if (err)
			goto mpol_out;
	}
	{
		NODEMASK_SCRATCH(scratch);
		if (scratch) {
			down_write(&mm->mmap_sem);
			task_lock(current);
			err = mpol_set_nodemask(new, nmask, scratch);
			task_unlock(current);
			if (err)
				up_write(&mm->mmap_sem);
		} else
			err = -ENOMEM;
		NODEMASK_SCRATCH_FREE(scratch);
	}
	if (err)
		goto mpol_out;

	ret = queue_pages_range(mm, start, end, nmask,
			  flags | MPOL_MF_INVERT, &pagelist);

	if (ret < 0) {
		err = -EIO;
		goto up_out;
	}

	err = mbind_range(mm, start, end, new);

	if (!err) {
		int nr_failed = 0;

		if (!list_empty(&pagelist)) {
			WARN_ON_ONCE(flags & MPOL_MF_LAZY);
			nr_failed = migrate_pages(&pagelist, new_page, NULL,
				start, MIGRATE_SYNC, MR_MEMPOLICY_MBIND);
			if (nr_failed)
				putback_movable_pages(&pagelist);
		}

		if ((ret > 0) || (nr_failed && (flags & MPOL_MF_STRICT)))
			err = -EIO;
	} else
		putback_movable_pages(&pagelist);

up_out:
	up_write(&mm->mmap_sem);
mpol_out:
	mpol_put(new);
	return err;
}