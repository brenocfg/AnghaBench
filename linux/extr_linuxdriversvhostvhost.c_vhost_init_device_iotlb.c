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
struct vhost_virtqueue {int /*<<< orphan*/  mutex; struct vhost_umem* iotlb; } ;
struct vhost_umem {int dummy; } ;
struct vhost_dev {int nvqs; struct vhost_virtqueue** vqs; struct vhost_umem* iotlb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __vhost_vq_meta_reset (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vhost_umem* vhost_umem_alloc () ; 
 int /*<<< orphan*/  vhost_umem_clean (struct vhost_umem*) ; 

int vhost_init_device_iotlb(struct vhost_dev *d, bool enabled)
{
	struct vhost_umem *niotlb, *oiotlb;
	int i;

	niotlb = vhost_umem_alloc();
	if (!niotlb)
		return -ENOMEM;

	oiotlb = d->iotlb;
	d->iotlb = niotlb;

	for (i = 0; i < d->nvqs; ++i) {
		struct vhost_virtqueue *vq = d->vqs[i];

		mutex_lock(&vq->mutex);
		vq->iotlb = niotlb;
		__vhost_vq_meta_reset(vq);
		mutex_unlock(&vq->mutex);
	}

	vhost_umem_clean(oiotlb);

	return 0;
}