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
struct userfaultfd_ctx {int state; int /*<<< orphan*/  event_wqh; int /*<<< orphan*/  fault_pending_wqh; int /*<<< orphan*/  fd_wqh; } ;
struct file {int f_flags; struct userfaultfd_ctx* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLERR ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int O_NONBLOCK ; 
#define  UFFD_STATE_RUNNING 129 
#define  UFFD_STATE_WAIT_API 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t userfaultfd_poll(struct file *file, poll_table *wait)
{
	struct userfaultfd_ctx *ctx = file->private_data;
	__poll_t ret;

	poll_wait(file, &ctx->fd_wqh, wait);

	switch (ctx->state) {
	case UFFD_STATE_WAIT_API:
		return EPOLLERR;
	case UFFD_STATE_RUNNING:
		/*
		 * poll() never guarantees that read won't block.
		 * userfaults can be waken before they're read().
		 */
		if (unlikely(!(file->f_flags & O_NONBLOCK)))
			return EPOLLERR;
		/*
		 * lockless access to see if there are pending faults
		 * __pollwait last action is the add_wait_queue but
		 * the spin_unlock would allow the waitqueue_active to
		 * pass above the actual list_add inside
		 * add_wait_queue critical section. So use a full
		 * memory barrier to serialize the list_add write of
		 * add_wait_queue() with the waitqueue_active read
		 * below.
		 */
		ret = 0;
		smp_mb();
		if (waitqueue_active(&ctx->fault_pending_wqh))
			ret = EPOLLIN;
		else if (waitqueue_active(&ctx->event_wqh))
			ret = EPOLLIN;

		return ret;
	default:
		WARN_ON_ONCE(1);
		return EPOLLERR;
	}
}