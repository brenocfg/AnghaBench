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
struct inode {int dummy; } ;
struct file {struct doorbell_queue* private_data; } ;
struct doorbell_queue {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_list_lock ; 
 int /*<<< orphan*/  kfree (struct doorbell_queue*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fsl_hv_close(struct inode *inode, struct file *filp)
{
	struct doorbell_queue *dbq = filp->private_data;
	unsigned long flags;

	int ret = 0;

	spin_lock_irqsave(&db_list_lock, flags);
	list_del(&dbq->list);
	spin_unlock_irqrestore(&db_list_lock, flags);

	kfree(dbq);

	return ret;
}