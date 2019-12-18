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
struct virtio_vsock_event {int dummy; } ;
struct virtio_vsock {struct virtqueue** vqs; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t VSOCK_VQ_EVENT ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,struct virtio_vsock_event*,int) ; 
 int virtqueue_add_inbuf (struct virtqueue*,struct scatterlist*,int,struct virtio_vsock_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_vsock_event_fill_one(struct virtio_vsock *vsock,
				       struct virtio_vsock_event *event)
{
	struct scatterlist sg;
	struct virtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_EVENT];

	sg_init_one(&sg, event, sizeof(*event));

	return virtqueue_add_inbuf(vq, &sg, 1, event, GFP_KERNEL);
}