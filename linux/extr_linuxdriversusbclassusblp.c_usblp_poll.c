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
struct usblp {int /*<<< orphan*/  lock; scalar_t__ wcomplete; scalar_t__ no_paper; scalar_t__ rcomplete; scalar_t__ bidir; int /*<<< orphan*/  wwait; int /*<<< orphan*/  rwait; } ;
struct poll_table_struct {int dummy; } ;
struct file {struct usblp* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __poll_t usblp_poll(struct file *file, struct poll_table_struct *wait)
{
	__poll_t ret;
	unsigned long flags;

	struct usblp *usblp = file->private_data;
	/* Should we check file->f_mode & FMODE_WRITE before poll_wait()? */
	poll_wait(file, &usblp->rwait, wait);
	poll_wait(file, &usblp->wwait, wait);
	spin_lock_irqsave(&usblp->lock, flags);
	ret = ((usblp->bidir && usblp->rcomplete) ? EPOLLIN  | EPOLLRDNORM : 0) |
	   ((usblp->no_paper || usblp->wcomplete) ? EPOLLOUT | EPOLLWRNORM : 0);
	spin_unlock_irqrestore(&usblp->lock, flags);
	return ret;
}