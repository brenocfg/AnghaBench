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
struct virtqueue {TYPE_1__* vdev; } ;
struct virtio_vsock {int /*<<< orphan*/  tx_work; } ;
struct TYPE_2__ {struct virtio_vsock* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_vsock_workqueue ; 

__attribute__((used)) static void virtio_vsock_tx_done(struct virtqueue *vq)
{
	struct virtio_vsock *vsock = vq->vdev->priv;

	if (!vsock)
		return;
	queue_work(virtio_vsock_workqueue, &vsock->tx_work);
}