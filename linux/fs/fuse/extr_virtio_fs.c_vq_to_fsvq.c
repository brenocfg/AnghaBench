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
struct virtqueue {size_t index; TYPE_1__* vdev; } ;
struct virtio_fs_vq {int dummy; } ;
struct virtio_fs {struct virtio_fs_vq* vqs; } ;
struct TYPE_2__ {struct virtio_fs* priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct virtio_fs_vq *vq_to_fsvq(struct virtqueue *vq)
{
	struct virtio_fs *fs = vq->vdev->priv;

	return &fs->vqs[vq->index];
}