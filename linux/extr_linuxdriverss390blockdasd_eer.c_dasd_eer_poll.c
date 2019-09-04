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
struct file {scalar_t__ private_data; } ;
struct eerbuffer {scalar_t__ head; scalar_t__ tail; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  bufferlock ; 
 int /*<<< orphan*/  dasd_eer_read_wait_queue ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __poll_t dasd_eer_poll(struct file *filp, poll_table *ptable)
{
	__poll_t mask;
	unsigned long flags;
	struct eerbuffer *eerb;

	eerb = (struct eerbuffer *) filp->private_data;
	poll_wait(filp, &dasd_eer_read_wait_queue, ptable);
	spin_lock_irqsave(&bufferlock, flags);
	if (eerb->head != eerb->tail)
		mask = EPOLLIN | EPOLLRDNORM ;
	else
		mask = 0;
	spin_unlock_irqrestore(&bufferlock, flags);
	return mask;
}