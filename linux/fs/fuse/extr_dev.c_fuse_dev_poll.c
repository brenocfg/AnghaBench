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
struct fuse_iqueue {int /*<<< orphan*/  lock; int /*<<< orphan*/  connected; int /*<<< orphan*/  waitq; } ;
struct fuse_dev {TYPE_1__* fc; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {struct fuse_iqueue iq; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 struct fuse_dev* fuse_get_dev (struct file*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ request_pending (struct fuse_iqueue*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t fuse_dev_poll(struct file *file, poll_table *wait)
{
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;
	struct fuse_iqueue *fiq;
	struct fuse_dev *fud = fuse_get_dev(file);

	if (!fud)
		return EPOLLERR;

	fiq = &fud->fc->iq;
	poll_wait(file, &fiq->waitq, wait);

	spin_lock(&fiq->lock);
	if (!fiq->connected)
		mask = EPOLLERR;
	else if (request_pending(fiq))
		mask |= EPOLLIN | EPOLLRDNORM;
	spin_unlock(&fiq->lock);

	return mask;
}