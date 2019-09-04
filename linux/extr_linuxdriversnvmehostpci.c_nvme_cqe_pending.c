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
struct nvme_queue {size_t cq_head; int cq_phase; TYPE_1__* cqes; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool nvme_cqe_pending(struct nvme_queue *nvmeq)
{
	return (le16_to_cpu(nvmeq->cqes[nvmeq->cq_head].status) & 1) ==
			nvmeq->cq_phase;
}