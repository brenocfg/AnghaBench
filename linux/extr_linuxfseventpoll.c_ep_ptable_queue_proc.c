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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct file {int dummy; } ;
struct eppoll_entry {int /*<<< orphan*/  llink; int /*<<< orphan*/  wait; struct epitem* base; int /*<<< orphan*/ * whead; } ;
struct TYPE_2__ {int events; } ;
struct epitem {int nwait; int /*<<< orphan*/  pwqlist; TYPE_1__ event; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int EPOLLEXCLUSIVE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_wait_queue_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct epitem* ep_item_from_epqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ep_poll_callback ; 
 int /*<<< orphan*/  init_waitqueue_func_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct eppoll_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwq_cache ; 

__attribute__((used)) static void ep_ptable_queue_proc(struct file *file, wait_queue_head_t *whead,
				 poll_table *pt)
{
	struct epitem *epi = ep_item_from_epqueue(pt);
	struct eppoll_entry *pwq;

	if (epi->nwait >= 0 && (pwq = kmem_cache_alloc(pwq_cache, GFP_KERNEL))) {
		init_waitqueue_func_entry(&pwq->wait, ep_poll_callback);
		pwq->whead = whead;
		pwq->base = epi;
		if (epi->event.events & EPOLLEXCLUSIVE)
			add_wait_queue_exclusive(whead, &pwq->wait);
		else
			add_wait_queue(whead, &pwq->wait);
		list_add_tail(&pwq->llink, &epi->pwqlist);
		epi->nwait++;
	} else {
		/* We have to signal that an error occurred */
		epi->nwait = -1;
	}
}