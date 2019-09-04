#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfio_dma {TYPE_1__* task; int /*<<< orphan*/  lock_cap; } ;
struct mm_struct {long locked_vm; int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_3__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ESRCH ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int down_write_killable (int /*<<< orphan*/ *) ; 
 struct mm_struct* get_task_mm (TYPE_1__*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 unsigned long task_rlimit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_lock_acct(struct vfio_dma *dma, long npage, bool async)
{
	struct mm_struct *mm;
	int ret;

	if (!npage)
		return 0;

	mm = async ? get_task_mm(dma->task) : dma->task->mm;
	if (!mm)
		return -ESRCH; /* process exited */

	ret = down_write_killable(&mm->mmap_sem);
	if (!ret) {
		if (npage > 0) {
			if (!dma->lock_cap) {
				unsigned long limit;

				limit = task_rlimit(dma->task,
						RLIMIT_MEMLOCK) >> PAGE_SHIFT;

				if (mm->locked_vm + npage > limit)
					ret = -ENOMEM;
			}
		}

		if (!ret)
			mm->locked_vm += npage;

		up_write(&mm->mmap_sem);
	}

	if (async)
		mmput(mm);

	return ret;
}