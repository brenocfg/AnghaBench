#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct fuse_iqueue {TYPE_2__ waitq; int /*<<< orphan*/  fasync; struct fuse_forget_link* forget_list_tail; scalar_t__ connected; } ;
struct TYPE_3__ {void* nlookup; void* nodeid; } ;
struct fuse_forget_link {struct fuse_forget_link* next; TYPE_1__ forget_one; } ;
struct fuse_conn {struct fuse_iqueue iq; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kfree (struct fuse_forget_link*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_locked (TYPE_2__*) ; 

void fuse_queue_forget(struct fuse_conn *fc, struct fuse_forget_link *forget,
		       u64 nodeid, u64 nlookup)
{
	struct fuse_iqueue *fiq = &fc->iq;

	forget->forget_one.nodeid = nodeid;
	forget->forget_one.nlookup = nlookup;

	spin_lock(&fiq->waitq.lock);
	if (fiq->connected) {
		fiq->forget_list_tail->next = forget;
		fiq->forget_list_tail = forget;
		wake_up_locked(&fiq->waitq);
		kill_fasync(&fiq->fasync, SIGIO, POLL_IN);
	} else {
		kfree(forget);
	}
	spin_unlock(&fiq->waitq.lock);
}