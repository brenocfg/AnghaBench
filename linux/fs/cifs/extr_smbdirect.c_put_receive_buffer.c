#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct smbd_response {int /*<<< orphan*/  list; TYPE_2__ sge; } ;
struct smbd_connection {int /*<<< orphan*/  post_send_credits_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  receive_queue_lock; int /*<<< orphan*/  count_put_receive_buffer; int /*<<< orphan*/  count_receive_queue; int /*<<< orphan*/  receive_queue; TYPE_1__* id; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void put_receive_buffer(
	struct smbd_connection *info, struct smbd_response *response)
{
	unsigned long flags;

	ib_dma_unmap_single(info->id->device, response->sge.addr,
		response->sge.length, DMA_FROM_DEVICE);

	spin_lock_irqsave(&info->receive_queue_lock, flags);
	list_add_tail(&response->list, &info->receive_queue);
	info->count_receive_queue++;
	info->count_put_receive_buffer++;
	spin_unlock_irqrestore(&info->receive_queue_lock, flags);

	queue_work(info->workqueue, &info->post_send_credits_work);
}