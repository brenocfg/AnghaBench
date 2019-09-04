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
struct request {struct nvme_queue* end_io_data; } ;
struct nvme_queue {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  ioq_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_del_queue_end(struct request *req, blk_status_t error)
{
	struct nvme_queue *nvmeq = req->end_io_data;

	blk_mq_free_request(req);
	complete(&nvmeq->dev->ioq_wait);
}