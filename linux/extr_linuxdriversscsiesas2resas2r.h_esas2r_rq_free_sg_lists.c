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
struct esas2r_request {int /*<<< orphan*/  sg_table_head; } ;
struct esas2r_adapter {int /*<<< orphan*/  sg_list_lock; int /*<<< orphan*/  free_sg_list_head; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void esas2r_rq_free_sg_lists(struct esas2r_request *rq,
					   struct esas2r_adapter *a)
{
	unsigned long flags;

	if (list_empty(&rq->sg_table_head))
		return;

	spin_lock_irqsave(&a->sg_list_lock, flags);
	list_splice_tail_init(&rq->sg_table_head, &a->free_sg_list_head);
	spin_unlock_irqrestore(&a->sg_list_lock, flags);
}