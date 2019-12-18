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
struct virtqueue {int dummy; } ;
struct virtio_vsock {int /*<<< orphan*/  queued_replies; struct virtqueue** vqs; } ;

/* Variables and functions */
 size_t VSOCK_VQ_RX ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int virtqueue_get_vring_size (struct virtqueue*) ; 

__attribute__((used)) static bool virtio_transport_more_replies(struct virtio_vsock *vsock)
{
	struct virtqueue *vq = vsock->vqs[VSOCK_VQ_RX];
	int val;

	smp_rmb(); /* paired with atomic_inc() and atomic_dec_return() */
	val = atomic_read(&vsock->queued_replies);

	return val < virtqueue_get_vring_size(vq);
}