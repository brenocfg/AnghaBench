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
typedef  int /*<<< orphan*/  u16 ;
struct nvme_queue {TYPE_1__* dev; scalar_t__ q_db; int /*<<< orphan*/  dbbuf_cq_ei; int /*<<< orphan*/  dbbuf_cq_db; int /*<<< orphan*/  cq_head; } ;
struct TYPE_2__ {scalar_t__ db_stride; } ;

/* Variables and functions */
 scalar_t__ nvme_dbbuf_update_and_check_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void nvme_ring_cq_doorbell(struct nvme_queue *nvmeq)
{
	u16 head = nvmeq->cq_head;

	if (nvme_dbbuf_update_and_check_event(head, nvmeq->dbbuf_cq_db,
					      nvmeq->dbbuf_cq_ei))
		writel(head, nvmeq->q_db + nvmeq->dev->db_stride);
}