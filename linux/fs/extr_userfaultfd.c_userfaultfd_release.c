#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct userfaultfd_ctx* ctx; } ;
struct vm_area_struct {unsigned long vm_flags; TYPE_1__ vm_userfaultfd_ctx; int /*<<< orphan*/  vm_pgoff; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  anon_vma; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct vm_area_struct* vm_next; } ;
struct userfaultfd_wake_range {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct userfaultfd_ctx {int /*<<< orphan*/  fd_wqh; int /*<<< orphan*/  event_wqh; TYPE_2__ fault_pending_wqh; int /*<<< orphan*/  fault_wqh; int /*<<< orphan*/  released; struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
struct inode {int dummy; } ;
struct file {struct userfaultfd_ctx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EPOLLHUP ; 
 TYPE_1__ NULL_VM_UFFD_CTX ; 
 int /*<<< orphan*/  TASK_NORMAL ; 
 unsigned long VM_UFFD_MISSING ; 
 unsigned long VM_UFFD_WP ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct userfaultfd_wake_range*) ; 
 int /*<<< orphan*/  __wake_up_locked_key (TYPE_2__*,int /*<<< orphan*/ ,struct userfaultfd_wake_range*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmget_not_zero (struct mm_struct*) ; 
 int mmget_still_valid (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userfaultfd_ctx_put (struct userfaultfd_ctx*) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int userfaultfd_release(struct inode *inode, struct file *file)
{
	struct userfaultfd_ctx *ctx = file->private_data;
	struct mm_struct *mm = ctx->mm;
	struct vm_area_struct *vma, *prev;
	/* len == 0 means wake all */
	struct userfaultfd_wake_range range = { .len = 0, };
	unsigned long new_flags;
	bool still_valid;

	WRITE_ONCE(ctx->released, true);

	if (!mmget_not_zero(mm))
		goto wakeup;

	/*
	 * Flush page faults out of all CPUs. NOTE: all page faults
	 * must be retried without returning VM_FAULT_SIGBUS if
	 * userfaultfd_ctx_get() succeeds but vma->vma_userfault_ctx
	 * changes while handle_userfault released the mmap_sem. So
	 * it's critical that released is set to true (above), before
	 * taking the mmap_sem for writing.
	 */
	down_write(&mm->mmap_sem);
	still_valid = mmget_still_valid(mm);
	prev = NULL;
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		cond_resched();
		BUG_ON(!!vma->vm_userfaultfd_ctx.ctx ^
		       !!(vma->vm_flags & (VM_UFFD_MISSING | VM_UFFD_WP)));
		if (vma->vm_userfaultfd_ctx.ctx != ctx) {
			prev = vma;
			continue;
		}
		new_flags = vma->vm_flags & ~(VM_UFFD_MISSING | VM_UFFD_WP);
		if (still_valid) {
			prev = vma_merge(mm, prev, vma->vm_start, vma->vm_end,
					 new_flags, vma->anon_vma,
					 vma->vm_file, vma->vm_pgoff,
					 vma_policy(vma),
					 NULL_VM_UFFD_CTX);
			if (prev)
				vma = prev;
			else
				prev = vma;
		}
		vma->vm_flags = new_flags;
		vma->vm_userfaultfd_ctx = NULL_VM_UFFD_CTX;
	}
	up_write(&mm->mmap_sem);
	mmput(mm);
wakeup:
	/*
	 * After no new page faults can wait on this fault_*wqh, flush
	 * the last page faults that may have been already waiting on
	 * the fault_*wqh.
	 */
	spin_lock_irq(&ctx->fault_pending_wqh.lock);
	__wake_up_locked_key(&ctx->fault_pending_wqh, TASK_NORMAL, &range);
	__wake_up(&ctx->fault_wqh, TASK_NORMAL, 1, &range);
	spin_unlock_irq(&ctx->fault_pending_wqh.lock);

	/* Flush pending events that may still wait on event_wqh */
	wake_up_all(&ctx->event_wqh);

	wake_up_poll(&ctx->fd_wqh, EPOLLHUP);
	userfaultfd_ctx_put(ctx);
	return 0;
}