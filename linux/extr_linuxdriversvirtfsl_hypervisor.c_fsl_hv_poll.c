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
struct poll_table_struct {int dummy; } ;
struct file {struct doorbell_queue* private_data; } ;
struct doorbell_queue {scalar_t__ head; scalar_t__ tail; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __poll_t fsl_hv_poll(struct file *filp, struct poll_table_struct *p)
{
	struct doorbell_queue *dbq = filp->private_data;
	unsigned long flags;
	__poll_t mask;

	spin_lock_irqsave(&dbq->lock, flags);

	poll_wait(filp, &dbq->wait, p);
	mask = (dbq->head == dbq->tail) ? 0 : (EPOLLIN | EPOLLRDNORM);

	spin_unlock_irqrestore(&dbq->lock, flags);

	return mask;
}