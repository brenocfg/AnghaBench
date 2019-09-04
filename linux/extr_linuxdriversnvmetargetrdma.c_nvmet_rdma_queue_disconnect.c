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
struct nvmet_rdma_queue {int /*<<< orphan*/  queue_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nvmet_rdma_queue_disconnect (struct nvmet_rdma_queue*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_rdma_queue_mutex ; 

__attribute__((used)) static void nvmet_rdma_queue_disconnect(struct nvmet_rdma_queue *queue)
{
	bool disconnect = false;

	mutex_lock(&nvmet_rdma_queue_mutex);
	if (!list_empty(&queue->queue_list)) {
		list_del_init(&queue->queue_list);
		disconnect = true;
	}
	mutex_unlock(&nvmet_rdma_queue_mutex);

	if (disconnect)
		__nvmet_rdma_queue_disconnect(queue);
}