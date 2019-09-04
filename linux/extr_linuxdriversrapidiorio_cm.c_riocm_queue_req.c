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
struct tx_req {size_t len; int /*<<< orphan*/  node; void* buffer; struct rio_dev* rdev; } ;
struct rio_dev {int dummy; } ;
struct cm_dev {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_reqs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tx_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int riocm_queue_req(struct cm_dev *cm, struct rio_dev *rdev,
			   void *buffer, size_t len)
{
	unsigned long flags;
	struct tx_req *treq;

	treq = kzalloc(sizeof(*treq), GFP_KERNEL);
	if (treq == NULL)
		return -ENOMEM;

	treq->rdev = rdev;
	treq->buffer = buffer;
	treq->len = len;

	spin_lock_irqsave(&cm->tx_lock, flags);
	list_add_tail(&treq->node, &cm->tx_reqs);
	spin_unlock_irqrestore(&cm->tx_lock, flags);
	return 0;
}