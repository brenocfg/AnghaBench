#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ wait_queue_entry_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; } ;
struct eventpoll {scalar_t__ ovflist; TYPE_3__ poll_wait; TYPE_3__ wq; int /*<<< orphan*/  rdllist; int /*<<< orphan*/  ws; } ;
struct TYPE_10__ {int events; } ;
struct epitem {scalar_t__ next; TYPE_1__ event; int /*<<< orphan*/  rdllink; scalar_t__ ws; struct eventpoll* ep; } ;
typedef  int __poll_t ;
struct TYPE_13__ {int /*<<< orphan*/  whead; } ;

/* Variables and functions */
 int EPOLLEXCLUSIVE ; 
#define  EPOLLIN 129 
 int EPOLLINOUT_BITS ; 
#define  EPOLLOUT 128 
 int EP_PRIVATE_BITS ; 
 scalar_t__ EP_UNACTIVE_PTR ; 
 int POLLFREE ; 
 int /*<<< orphan*/  __pm_stay_awake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep_is_linked (struct epitem*) ; 
 struct epitem* ep_item_from_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  ep_pm_stay_awake_rcu (struct epitem*) ; 
 int /*<<< orphan*/  ep_poll_safewake (TYPE_3__*) ; 
 TYPE_5__* ep_pwq_from_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  ep_set_busy_poll_napi_id (struct epitem*) ; 
 int key_to_poll (void*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ waitqueue_active (TYPE_3__*) ; 
 int /*<<< orphan*/  wake_up_locked (TYPE_3__*) ; 

__attribute__((used)) static int ep_poll_callback(wait_queue_entry_t *wait, unsigned mode, int sync, void *key)
{
	int pwake = 0;
	unsigned long flags;
	struct epitem *epi = ep_item_from_wait(wait);
	struct eventpoll *ep = epi->ep;
	__poll_t pollflags = key_to_poll(key);
	int ewake = 0;

	spin_lock_irqsave(&ep->wq.lock, flags);

	ep_set_busy_poll_napi_id(epi);

	/*
	 * If the event mask does not contain any poll(2) event, we consider the
	 * descriptor to be disabled. This condition is likely the effect of the
	 * EPOLLONESHOT bit that disables the descriptor when an event is received,
	 * until the next EPOLL_CTL_MOD will be issued.
	 */
	if (!(epi->event.events & ~EP_PRIVATE_BITS))
		goto out_unlock;

	/*
	 * Check the events coming with the callback. At this stage, not
	 * every device reports the events in the "key" parameter of the
	 * callback. We need to be able to handle both cases here, hence the
	 * test for "key" != NULL before the event match test.
	 */
	if (pollflags && !(pollflags & epi->event.events))
		goto out_unlock;

	/*
	 * If we are transferring events to userspace, we can hold no locks
	 * (because we're accessing user memory, and because of linux f_op->poll()
	 * semantics). All the events that happen during that period of time are
	 * chained in ep->ovflist and requeued later on.
	 */
	if (ep->ovflist != EP_UNACTIVE_PTR) {
		if (epi->next == EP_UNACTIVE_PTR) {
			epi->next = ep->ovflist;
			ep->ovflist = epi;
			if (epi->ws) {
				/*
				 * Activate ep->ws since epi->ws may get
				 * deactivated at any time.
				 */
				__pm_stay_awake(ep->ws);
			}

		}
		goto out_unlock;
	}

	/* If this file is already in the ready list we exit soon */
	if (!ep_is_linked(epi)) {
		list_add_tail(&epi->rdllink, &ep->rdllist);
		ep_pm_stay_awake_rcu(epi);
	}

	/*
	 * Wake up ( if active ) both the eventpoll wait list and the ->poll()
	 * wait list.
	 */
	if (waitqueue_active(&ep->wq)) {
		if ((epi->event.events & EPOLLEXCLUSIVE) &&
					!(pollflags & POLLFREE)) {
			switch (pollflags & EPOLLINOUT_BITS) {
			case EPOLLIN:
				if (epi->event.events & EPOLLIN)
					ewake = 1;
				break;
			case EPOLLOUT:
				if (epi->event.events & EPOLLOUT)
					ewake = 1;
				break;
			case 0:
				ewake = 1;
				break;
			}
		}
		wake_up_locked(&ep->wq);
	}
	if (waitqueue_active(&ep->poll_wait))
		pwake++;

out_unlock:
	spin_unlock_irqrestore(&ep->wq.lock, flags);

	/* We have to call this outside the lock */
	if (pwake)
		ep_poll_safewake(&ep->poll_wait);

	if (!(epi->event.events & EPOLLEXCLUSIVE))
		ewake = 1;

	if (pollflags & POLLFREE) {
		/*
		 * If we race with ep_remove_wait_queue() it can miss
		 * ->whead = NULL and do another remove_wait_queue() after
		 * us, so we can't use __remove_wait_queue().
		 */
		list_del_init(&wait->entry);
		/*
		 * ->whead != NULL protects us from the race with ep_free()
		 * or ep_remove(), ep_remove_wait_queue() takes whead->lock
		 * held by the caller. Once we nullify it, nothing protects
		 * ep/epi or even wait.
		 */
		smp_store_release(&ep_pwq_from_wait(wait)->whead, NULL);
	}

	return ewake;
}