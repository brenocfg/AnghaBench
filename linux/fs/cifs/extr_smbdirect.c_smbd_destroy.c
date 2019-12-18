#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smbd_response {int /*<<< orphan*/  list; } ;
struct smbd_connection {scalar_t__ transport_status; scalar_t__ count_receive_queue; scalar_t__ count_empty_packet_queue; scalar_t__ receive_credit_max; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  response_cache; int /*<<< orphan*/  response_mempool; int /*<<< orphan*/  request_cache; int /*<<< orphan*/  request_mempool; TYPE_1__* id; int /*<<< orphan*/  pd; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  mr_used_count; int /*<<< orphan*/  wait_mr; int /*<<< orphan*/  wait_receive_queues; scalar_t__ reassembly_data_length; int /*<<< orphan*/  reassembly_queue_lock; int /*<<< orphan*/  send_payload_pending; int /*<<< orphan*/  wait_send_payload_pending; int /*<<< orphan*/  send_pending; int /*<<< orphan*/  wait_send_pending; int /*<<< orphan*/  send_immediate_work; int /*<<< orphan*/  idle_timer_work; int /*<<< orphan*/  disconn_wait; } ;
struct TCP_Server_Info {int /*<<< orphan*/  srv_mutex; struct smbd_connection* smbd_conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 scalar_t__ SMBD_DESTROYED ; 
 scalar_t__ SMBD_DISCONNECTED ; 
 struct smbd_response* _get_first_reassembly (struct smbd_connection*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_mr_list (struct smbd_connection*) ; 
 int /*<<< orphan*/  destroy_receive_buffers (struct smbd_connection*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_drain_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_free_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smbd_connection*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_rdma_event (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_receive_buffer (struct smbd_connection*,struct smbd_response*) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_destroy_qp (TYPE_1__*) ; 
 int /*<<< orphan*/  rdma_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

void smbd_destroy(struct TCP_Server_Info *server)
{
	struct smbd_connection *info = server->smbd_conn;
	struct smbd_response *response;
	unsigned long flags;

	if (!info) {
		log_rdma_event(INFO, "rdma session already destroyed\n");
		return;
	}

	log_rdma_event(INFO, "destroying rdma session\n");
	if (info->transport_status != SMBD_DISCONNECTED) {
		rdma_disconnect(server->smbd_conn->id);
		log_rdma_event(INFO, "wait for transport being disconnected\n");
		wait_event_interruptible(
			info->disconn_wait,
			info->transport_status == SMBD_DISCONNECTED);
	}

	log_rdma_event(INFO, "destroying qp\n");
	ib_drain_qp(info->id->qp);
	rdma_destroy_qp(info->id);

	log_rdma_event(INFO, "cancelling idle timer\n");
	cancel_delayed_work_sync(&info->idle_timer_work);
	log_rdma_event(INFO, "cancelling send immediate work\n");
	cancel_delayed_work_sync(&info->send_immediate_work);

	log_rdma_event(INFO, "wait for all send posted to IB to finish\n");
	wait_event(info->wait_send_pending,
		atomic_read(&info->send_pending) == 0);
	wait_event(info->wait_send_payload_pending,
		atomic_read(&info->send_payload_pending) == 0);

	/* It's not posssible for upper layer to get to reassembly */
	log_rdma_event(INFO, "drain the reassembly queue\n");
	do {
		spin_lock_irqsave(&info->reassembly_queue_lock, flags);
		response = _get_first_reassembly(info);
		if (response) {
			list_del(&response->list);
			spin_unlock_irqrestore(
				&info->reassembly_queue_lock, flags);
			put_receive_buffer(info, response);
		} else
			spin_unlock_irqrestore(
				&info->reassembly_queue_lock, flags);
	} while (response);
	info->reassembly_data_length = 0;

	log_rdma_event(INFO, "free receive buffers\n");
	wait_event(info->wait_receive_queues,
		info->count_receive_queue + info->count_empty_packet_queue
			== info->receive_credit_max);
	destroy_receive_buffers(info);

	/*
	 * For performance reasons, memory registration and deregistration
	 * are not locked by srv_mutex. It is possible some processes are
	 * blocked on transport srv_mutex while holding memory registration.
	 * Release the transport srv_mutex to allow them to hit the failure
	 * path when sending data, and then release memory registartions.
	 */
	log_rdma_event(INFO, "freeing mr list\n");
	wake_up_interruptible_all(&info->wait_mr);
	while (atomic_read(&info->mr_used_count)) {
		mutex_unlock(&server->srv_mutex);
		msleep(1000);
		mutex_lock(&server->srv_mutex);
	}
	destroy_mr_list(info);

	ib_free_cq(info->send_cq);
	ib_free_cq(info->recv_cq);
	ib_dealloc_pd(info->pd);
	rdma_destroy_id(info->id);

	/* free mempools */
	mempool_destroy(info->request_mempool);
	kmem_cache_destroy(info->request_cache);

	mempool_destroy(info->response_mempool);
	kmem_cache_destroy(info->response_cache);

	info->transport_status = SMBD_DESTROYED;

	destroy_workqueue(info->workqueue);
	kfree(info);
}