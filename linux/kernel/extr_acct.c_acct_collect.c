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
typedef  scalar_t__ u64 ;
struct vm_area_struct {struct vm_area_struct* vm_next; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct pacct_struct {unsigned long ac_mem; long ac_exitcode; int /*<<< orphan*/  ac_majflt; int /*<<< orphan*/  ac_minflt; int /*<<< orphan*/  ac_stime; int /*<<< orphan*/  ac_utime; int /*<<< orphan*/  ac_flag; } ;
struct TYPE_10__ {int flags; TYPE_3__* sighand; scalar_t__ maj_flt; scalar_t__ min_flt; TYPE_2__* mm; TYPE_1__* signal; } ;
struct TYPE_9__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_8__ {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
struct TYPE_7__ {struct pacct_struct pacct; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACORE ; 
 int /*<<< orphan*/  AFORK ; 
 int /*<<< orphan*/  ASU ; 
 int /*<<< orphan*/  AXSIG ; 
 int PF_DUMPCORE ; 
 int PF_FORKNOEXEC ; 
 int PF_SIGNALED ; 
 int PF_SUPERPRIV ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_cputime (TYPE_4__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ thread_group_leader (TYPE_4__*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void acct_collect(long exitcode, int group_dead)
{
	struct pacct_struct *pacct = &current->signal->pacct;
	u64 utime, stime;
	unsigned long vsize = 0;

	if (group_dead && current->mm) {
		struct vm_area_struct *vma;

		down_read(&current->mm->mmap_sem);
		vma = current->mm->mmap;
		while (vma) {
			vsize += vma->vm_end - vma->vm_start;
			vma = vma->vm_next;
		}
		up_read(&current->mm->mmap_sem);
	}

	spin_lock_irq(&current->sighand->siglock);
	if (group_dead)
		pacct->ac_mem = vsize / 1024;
	if (thread_group_leader(current)) {
		pacct->ac_exitcode = exitcode;
		if (current->flags & PF_FORKNOEXEC)
			pacct->ac_flag |= AFORK;
	}
	if (current->flags & PF_SUPERPRIV)
		pacct->ac_flag |= ASU;
	if (current->flags & PF_DUMPCORE)
		pacct->ac_flag |= ACORE;
	if (current->flags & PF_SIGNALED)
		pacct->ac_flag |= AXSIG;

	task_cputime(current, &utime, &stime);
	pacct->ac_utime += utime;
	pacct->ac_stime += stime;
	pacct->ac_minflt += current->min_flt;
	pacct->ac_majflt += current->maj_flt;
	spin_unlock_irq(&current->sighand->siglock);
}