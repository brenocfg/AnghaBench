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
typedef  int u64 ;
struct vhost_virtqueue {int acked_features; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct vhost_scsi {TYPE_2__ dev; TYPE_1__* vqs; } ;
struct TYPE_3__ {struct vhost_virtqueue vq; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int VHOST_F_LOG_ALL ; 
 int VHOST_SCSI_FEATURES ; 
 int VHOST_SCSI_MAX_VQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_log_access_ok (TYPE_2__*) ; 

__attribute__((used)) static int vhost_scsi_set_features(struct vhost_scsi *vs, u64 features)
{
	struct vhost_virtqueue *vq;
	int i;

	if (features & ~VHOST_SCSI_FEATURES)
		return -EOPNOTSUPP;

	mutex_lock(&vs->dev.mutex);
	if ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&vs->dev)) {
		mutex_unlock(&vs->dev.mutex);
		return -EFAULT;
	}

	for (i = 0; i < VHOST_SCSI_MAX_VQ; i++) {
		vq = &vs->vqs[i].vq;
		mutex_lock(&vq->mutex);
		vq->acked_features = features;
		mutex_unlock(&vq->mutex);
	}
	mutex_unlock(&vs->dev.mutex);
	return 0;
}