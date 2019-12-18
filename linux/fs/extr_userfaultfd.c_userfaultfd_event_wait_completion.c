#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {struct userfaultfd_ctx* ctx; } ;
struct vm_area_struct {int vm_flags; TYPE_9__ vm_userfaultfd_ctx; struct vm_area_struct* vm_next; } ;
struct TYPE_10__ {scalar_t__ reserved1; } ;
struct TYPE_11__ {TYPE_1__ reserved; } ;
struct TYPE_12__ {scalar_t__ event; TYPE_2__ arg; } ;
struct userfaultfd_wait_queue {TYPE_3__ msg; int /*<<< orphan*/  wq; struct userfaultfd_ctx* ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; } ;
struct userfaultfd_ctx {int /*<<< orphan*/  mmap_changing; struct mm_struct* mm; TYPE_7__ event_wqh; int /*<<< orphan*/  fd_wqh; int /*<<< orphan*/  released; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
struct TYPE_13__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 TYPE_9__ NULL_VM_UFFD_CTX ; 
 int PF_EXITING ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 scalar_t__ UFFD_EVENT_FORK ; 
 int VM_UFFD_MISSING ; 
 int VM_UFFD_WP ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __add_wait_queue (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __remove_wait_queue (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ fatal_signal_pending (TYPE_4__*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  mmget_still_valid (struct mm_struct*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userfaultfd_ctx_put (struct userfaultfd_ctx*) ; 
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void userfaultfd_event_wait_completion(struct userfaultfd_ctx *ctx,
					      struct userfaultfd_wait_queue *ewq)
{
	struct userfaultfd_ctx *release_new_ctx;

	if (WARN_ON_ONCE(current->flags & PF_EXITING))
		goto out;

	ewq->ctx = ctx;
	init_waitqueue_entry(&ewq->wq, current);
	release_new_ctx = NULL;

	spin_lock_irq(&ctx->event_wqh.lock);
	/*
	 * After the __add_wait_queue the uwq is visible to userland
	 * through poll/read().
	 */
	__add_wait_queue(&ctx->event_wqh, &ewq->wq);
	for (;;) {
		set_current_state(TASK_KILLABLE);
		if (ewq->msg.event == 0)
			break;
		if (READ_ONCE(ctx->released) ||
		    fatal_signal_pending(current)) {
			/*
			 * &ewq->wq may be queued in fork_event, but
			 * __remove_wait_queue ignores the head
			 * parameter. It would be a problem if it
			 * didn't.
			 */
			__remove_wait_queue(&ctx->event_wqh, &ewq->wq);
			if (ewq->msg.event == UFFD_EVENT_FORK) {
				struct userfaultfd_ctx *new;

				new = (struct userfaultfd_ctx *)
					(unsigned long)
					ewq->msg.arg.reserved.reserved1;
				release_new_ctx = new;
			}
			break;
		}

		spin_unlock_irq(&ctx->event_wqh.lock);

		wake_up_poll(&ctx->fd_wqh, EPOLLIN);
		schedule();

		spin_lock_irq(&ctx->event_wqh.lock);
	}
	__set_current_state(TASK_RUNNING);
	spin_unlock_irq(&ctx->event_wqh.lock);

	if (release_new_ctx) {
		struct vm_area_struct *vma;
		struct mm_struct *mm = release_new_ctx->mm;

		/* the various vma->vm_userfaultfd_ctx still points to it */
		down_write(&mm->mmap_sem);
		/* no task can run (and in turn coredump) yet */
		VM_WARN_ON(!mmget_still_valid(mm));
		for (vma = mm->mmap; vma; vma = vma->vm_next)
			if (vma->vm_userfaultfd_ctx.ctx == release_new_ctx) {
				vma->vm_userfaultfd_ctx = NULL_VM_UFFD_CTX;
				vma->vm_flags &= ~(VM_UFFD_WP | VM_UFFD_MISSING);
			}
		up_write(&mm->mmap_sem);

		userfaultfd_ctx_put(release_new_ctx);
	}

	/*
	 * ctx may go away after this if the userfault pseudo fd is
	 * already released.
	 */
out:
	WRITE_ONCE(ctx->mmap_changing, false);
	userfaultfd_ctx_put(ctx);
}