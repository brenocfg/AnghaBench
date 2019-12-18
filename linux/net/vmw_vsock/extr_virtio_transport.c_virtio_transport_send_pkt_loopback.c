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
struct virtio_vsock_pkt {int len; int /*<<< orphan*/  list; } ;
struct virtio_vsock {int /*<<< orphan*/  loopback_work; int /*<<< orphan*/  loopback_list_lock; int /*<<< orphan*/  loopback_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_vsock_workqueue ; 

__attribute__((used)) static int virtio_transport_send_pkt_loopback(struct virtio_vsock *vsock,
					      struct virtio_vsock_pkt *pkt)
{
	int len = pkt->len;

	spin_lock_bh(&vsock->loopback_list_lock);
	list_add_tail(&pkt->list, &vsock->loopback_list);
	spin_unlock_bh(&vsock->loopback_list_lock);

	queue_work(virtio_vsock_workqueue, &vsock->loopback_work);

	return len;
}