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
struct vhost_virtqueue {void* heads; void* log; void* indirect; } ;
struct vhost_dev {int nvqs; struct vhost_virtqueue** vqs; int /*<<< orphan*/  iov_limit; } ;

/* Variables and functions */
 long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UIO_MAXIOV ; 
 void* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_vq_free_iovecs (struct vhost_virtqueue*) ; 

__attribute__((used)) static long vhost_dev_alloc_iovecs(struct vhost_dev *dev)
{
	struct vhost_virtqueue *vq;
	int i;

	for (i = 0; i < dev->nvqs; ++i) {
		vq = dev->vqs[i];
		vq->indirect = kmalloc_array(UIO_MAXIOV,
					     sizeof(*vq->indirect),
					     GFP_KERNEL);
		vq->log = kmalloc_array(dev->iov_limit, sizeof(*vq->log),
					GFP_KERNEL);
		vq->heads = kmalloc_array(dev->iov_limit, sizeof(*vq->heads),
					  GFP_KERNEL);
		if (!vq->indirect || !vq->log || !vq->heads)
			goto err_nomem;
	}
	return 0;

err_nomem:
	for (; i >= 0; --i)
		vhost_vq_free_iovecs(dev->vqs[i]);
	return -ENOMEM;
}