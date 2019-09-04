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
struct TYPE_2__ {int /*<<< orphan*/  dst_cid; } ;
struct virtio_vsock_pkt {int len; int /*<<< orphan*/  list; scalar_t__ reply; TYPE_1__ hdr; } ;
struct virtio_vsock {scalar_t__ guest_cid; int /*<<< orphan*/  send_pkt_work; int /*<<< orphan*/  send_pkt_list_lock; int /*<<< orphan*/  send_pkt_list; int /*<<< orphan*/  queued_replies; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_transport_free_pkt (struct virtio_vsock_pkt*) ; 
 int virtio_transport_send_pkt_loopback (struct virtio_vsock*,struct virtio_vsock_pkt*) ; 
 struct virtio_vsock* virtio_vsock_get () ; 
 int /*<<< orphan*/  virtio_vsock_workqueue ; 

__attribute__((used)) static int
virtio_transport_send_pkt(struct virtio_vsock_pkt *pkt)
{
	struct virtio_vsock *vsock;
	int len = pkt->len;

	vsock = virtio_vsock_get();
	if (!vsock) {
		virtio_transport_free_pkt(pkt);
		return -ENODEV;
	}

	if (le64_to_cpu(pkt->hdr.dst_cid) == vsock->guest_cid)
		return virtio_transport_send_pkt_loopback(vsock, pkt);

	if (pkt->reply)
		atomic_inc(&vsock->queued_replies);

	spin_lock_bh(&vsock->send_pkt_list_lock);
	list_add_tail(&pkt->list, &vsock->send_pkt_list);
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	queue_work(virtio_vsock_workqueue, &vsock->send_pkt_work);
	return len;
}