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
struct request_queue {struct nvme_ns_head* queuedata; } ;
struct nvme_ns_head {int /*<<< orphan*/  srcu; int /*<<< orphan*/  current_path; } ;
struct nvme_ns {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_2__ {int (* poll_fn ) (struct request_queue*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 scalar_t__ nvme_path_is_optimized (struct nvme_ns*) ; 
 struct nvme_ns* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int stub1 (struct request_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nvme_ns_head_poll(struct request_queue *q, blk_qc_t qc)
{
	struct nvme_ns_head *head = q->queuedata;
	struct nvme_ns *ns;
	bool found = false;
	int srcu_idx;

	srcu_idx = srcu_read_lock(&head->srcu);
	ns = srcu_dereference(head->current_path, &head->srcu);
	if (likely(ns && nvme_path_is_optimized(ns)))
		found = ns->queue->poll_fn(q, qc);
	srcu_read_unlock(&head->srcu, srcu_idx);
	return found;
}