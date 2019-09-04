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
struct nvme_queue {int cq_head; int q_depth; int cq_phase; } ;

/* Variables and functions */

__attribute__((used)) static inline void nvme_update_cq_head(struct nvme_queue *nvmeq)
{
	if (nvmeq->cq_head == nvmeq->q_depth - 1) {
		nvmeq->cq_head = 0;
		nvmeq->cq_phase = !nvmeq->cq_phase;
	} else {
		nvmeq->cq_head++;
	}
}