#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int flags; int /*<<< orphan*/  address; TYPE_2__* vma; } ;
struct TYPE_13__ {int /*<<< orphan*/  entry; TYPE_3__* private; } ;
struct userfaultfd_wait_queue {int waken; TYPE_5__ wq; struct userfaultfd_ctx* ctx; int /*<<< orphan*/  msg; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; } ;
struct userfaultfd_ctx {int features; int released; TYPE_8__ fault_pending_wqh; int /*<<< orphan*/  fd_wqh; struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_12__ {int flags; } ;
struct TYPE_10__ {struct userfaultfd_ctx* ctx; } ;
struct TYPE_11__ {TYPE_1__ vm_userfaultfd_ctx; struct mm_struct* vm_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int FAULT_FLAG_ALLOW_RETRY ; 
 int FAULT_FLAG_KILLABLE ; 
 int FAULT_FLAG_RETRY_NOWAIT ; 
 int FAULT_FLAG_USER ; 
 int PF_DUMPCORE ; 
 int PF_EXITING ; 
 int READ_ONCE (int) ; 
 long TASK_INTERRUPTIBLE ; 
 long TASK_KILLABLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int UFFD_FEATURE_SIGBUS ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_FAULT_MAJOR ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_RETRY ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 unsigned long VM_UFFD_MISSING ; 
 unsigned long VM_UFFD_WP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __add_wait_queue (TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fatal_signal_pending (TYPE_3__*) ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (TYPE_2__*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (long) ; 
 scalar_t__ signal_pending (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userfault_msg (int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  userfaultfd_ctx_get (struct userfaultfd_ctx*) ; 
 int /*<<< orphan*/  userfaultfd_ctx_put (struct userfaultfd_ctx*) ; 
 int userfaultfd_huge_must_wait (struct userfaultfd_ctx*,TYPE_2__*,int /*<<< orphan*/ ,int,unsigned long) ; 
 int userfaultfd_must_wait (struct userfaultfd_ctx*,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  userfaultfd_wake_function ; 
 int /*<<< orphan*/  wake_up_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

vm_fault_t handle_userfault(struct vm_fault *vmf, unsigned long reason)
{
	struct mm_struct *mm = vmf->vma->vm_mm;
	struct userfaultfd_ctx *ctx;
	struct userfaultfd_wait_queue uwq;
	vm_fault_t ret = VM_FAULT_SIGBUS;
	bool must_wait, return_to_userland;
	long blocking_state;

	/*
	 * We don't do userfault handling for the final child pid update.
	 *
	 * We also don't do userfault handling during
	 * coredumping. hugetlbfs has the special
	 * follow_hugetlb_page() to skip missing pages in the
	 * FOLL_DUMP case, anon memory also checks for FOLL_DUMP with
	 * the no_page_table() helper in follow_page_mask(), but the
	 * shmem_vm_ops->fault method is invoked even during
	 * coredumping without mmap_sem and it ends up here.
	 */
	if (current->flags & (PF_EXITING|PF_DUMPCORE))
		goto out;

	/*
	 * Coredumping runs without mmap_sem so we can only check that
	 * the mmap_sem is held, if PF_DUMPCORE was not set.
	 */
	WARN_ON_ONCE(!rwsem_is_locked(&mm->mmap_sem));

	ctx = vmf->vma->vm_userfaultfd_ctx.ctx;
	if (!ctx)
		goto out;

	BUG_ON(ctx->mm != mm);

	VM_BUG_ON(reason & ~(VM_UFFD_MISSING|VM_UFFD_WP));
	VM_BUG_ON(!(reason & VM_UFFD_MISSING) ^ !!(reason & VM_UFFD_WP));

	if (ctx->features & UFFD_FEATURE_SIGBUS)
		goto out;

	/*
	 * If it's already released don't get it. This avoids to loop
	 * in __get_user_pages if userfaultfd_release waits on the
	 * caller of handle_userfault to release the mmap_sem.
	 */
	if (unlikely(READ_ONCE(ctx->released))) {
		/*
		 * Don't return VM_FAULT_SIGBUS in this case, so a non
		 * cooperative manager can close the uffd after the
		 * last UFFDIO_COPY, without risking to trigger an
		 * involuntary SIGBUS if the process was starting the
		 * userfaultfd while the userfaultfd was still armed
		 * (but after the last UFFDIO_COPY). If the uffd
		 * wasn't already closed when the userfault reached
		 * this point, that would normally be solved by
		 * userfaultfd_must_wait returning 'false'.
		 *
		 * If we were to return VM_FAULT_SIGBUS here, the non
		 * cooperative manager would be instead forced to
		 * always call UFFDIO_UNREGISTER before it can safely
		 * close the uffd.
		 */
		ret = VM_FAULT_NOPAGE;
		goto out;
	}

	/*
	 * Check that we can return VM_FAULT_RETRY.
	 *
	 * NOTE: it should become possible to return VM_FAULT_RETRY
	 * even if FAULT_FLAG_TRIED is set without leading to gup()
	 * -EBUSY failures, if the userfaultfd is to be extended for
	 * VM_UFFD_WP tracking and we intend to arm the userfault
	 * without first stopping userland access to the memory. For
	 * VM_UFFD_MISSING userfaults this is enough for now.
	 */
	if (unlikely(!(vmf->flags & FAULT_FLAG_ALLOW_RETRY))) {
		/*
		 * Validate the invariant that nowait must allow retry
		 * to be sure not to return SIGBUS erroneously on
		 * nowait invocations.
		 */
		BUG_ON(vmf->flags & FAULT_FLAG_RETRY_NOWAIT);
#ifdef CONFIG_DEBUG_VM
		if (printk_ratelimit()) {
			printk(KERN_WARNING
			       "FAULT_FLAG_ALLOW_RETRY missing %x\n",
			       vmf->flags);
			dump_stack();
		}
#endif
		goto out;
	}

	/*
	 * Handle nowait, not much to do other than tell it to retry
	 * and wait.
	 */
	ret = VM_FAULT_RETRY;
	if (vmf->flags & FAULT_FLAG_RETRY_NOWAIT)
		goto out;

	/* take the reference before dropping the mmap_sem */
	userfaultfd_ctx_get(ctx);

	init_waitqueue_func_entry(&uwq.wq, userfaultfd_wake_function);
	uwq.wq.private = current;
	uwq.msg = userfault_msg(vmf->address, vmf->flags, reason,
			ctx->features);
	uwq.ctx = ctx;
	uwq.waken = false;

	return_to_userland =
		(vmf->flags & (FAULT_FLAG_USER|FAULT_FLAG_KILLABLE)) ==
		(FAULT_FLAG_USER|FAULT_FLAG_KILLABLE);
	blocking_state = return_to_userland ? TASK_INTERRUPTIBLE :
			 TASK_KILLABLE;

	spin_lock(&ctx->fault_pending_wqh.lock);
	/*
	 * After the __add_wait_queue the uwq is visible to userland
	 * through poll/read().
	 */
	__add_wait_queue(&ctx->fault_pending_wqh, &uwq.wq);
	/*
	 * The smp_mb() after __set_current_state prevents the reads
	 * following the spin_unlock to happen before the list_add in
	 * __add_wait_queue.
	 */
	set_current_state(blocking_state);
	spin_unlock(&ctx->fault_pending_wqh.lock);

	if (!is_vm_hugetlb_page(vmf->vma))
		must_wait = userfaultfd_must_wait(ctx, vmf->address, vmf->flags,
						  reason);
	else
		must_wait = userfaultfd_huge_must_wait(ctx, vmf->vma,
						       vmf->address,
						       vmf->flags, reason);
	up_read(&mm->mmap_sem);

	if (likely(must_wait && !READ_ONCE(ctx->released) &&
		   (return_to_userland ? !signal_pending(current) :
		    !fatal_signal_pending(current)))) {
		wake_up_poll(&ctx->fd_wqh, EPOLLIN);
		schedule();
		ret |= VM_FAULT_MAJOR;

		/*
		 * False wakeups can orginate even from rwsem before
		 * up_read() however userfaults will wait either for a
		 * targeted wakeup on the specific uwq waitqueue from
		 * wake_userfault() or for signals or for uffd
		 * release.
		 */
		while (!READ_ONCE(uwq.waken)) {
			/*
			 * This needs the full smp_store_mb()
			 * guarantee as the state write must be
			 * visible to other CPUs before reading
			 * uwq.waken from other CPUs.
			 */
			set_current_state(blocking_state);
			if (READ_ONCE(uwq.waken) ||
			    READ_ONCE(ctx->released) ||
			    (return_to_userland ? signal_pending(current) :
			     fatal_signal_pending(current)))
				break;
			schedule();
		}
	}

	__set_current_state(TASK_RUNNING);

	if (return_to_userland) {
		if (signal_pending(current) &&
		    !fatal_signal_pending(current)) {
			/*
			 * If we got a SIGSTOP or SIGCONT and this is
			 * a normal userland page fault, just let
			 * userland return so the signal will be
			 * handled and gdb debugging works.  The page
			 * fault code immediately after we return from
			 * this function is going to release the
			 * mmap_sem and it's not depending on it
			 * (unlike gup would if we were not to return
			 * VM_FAULT_RETRY).
			 *
			 * If a fatal signal is pending we still take
			 * the streamlined VM_FAULT_RETRY failure path
			 * and there's no need to retake the mmap_sem
			 * in such case.
			 */
			down_read(&mm->mmap_sem);
			ret = VM_FAULT_NOPAGE;
		}
	}

	/*
	 * Here we race with the list_del; list_add in
	 * userfaultfd_ctx_read(), however because we don't ever run
	 * list_del_init() to refile across the two lists, the prev
	 * and next pointers will never point to self. list_add also
	 * would never let any of the two pointers to point to
	 * self. So list_empty_careful won't risk to see both pointers
	 * pointing to self at any time during the list refile. The
	 * only case where list_del_init() is called is the full
	 * removal in the wake function and there we don't re-list_add
	 * and it's fine not to block on the spinlock. The uwq on this
	 * kernel stack can be released after the list_del_init.
	 */
	if (!list_empty_careful(&uwq.wq.entry)) {
		spin_lock(&ctx->fault_pending_wqh.lock);
		/*
		 * No need of list_del_init(), the uwq on the stack
		 * will be freed shortly anyway.
		 */
		list_del(&uwq.wq.entry);
		spin_unlock(&ctx->fault_pending_wqh.lock);
	}

	/*
	 * ctx may go away after this if the userfault pseudo fd is
	 * already released.
	 */
	userfaultfd_ctx_put(ctx);

out:
	return ret;
}