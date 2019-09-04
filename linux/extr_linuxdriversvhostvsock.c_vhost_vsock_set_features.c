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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct vhost_vsock {TYPE_1__ dev; struct vhost_virtqueue* vqs; } ;
struct vhost_virtqueue {int acked_features; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vhost_virtqueue*) ; 
 int EFAULT ; 
 int EOPNOTSUPP ; 
 int VHOST_F_LOG_ALL ; 
 int VHOST_VSOCK_FEATURES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_log_access_ok (TYPE_1__*) ; 

__attribute__((used)) static int vhost_vsock_set_features(struct vhost_vsock *vsock, u64 features)
{
	struct vhost_virtqueue *vq;
	int i;

	if (features & ~VHOST_VSOCK_FEATURES)
		return -EOPNOTSUPP;

	mutex_lock(&vsock->dev.mutex);
	if ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&vsock->dev)) {
		mutex_unlock(&vsock->dev.mutex);
		return -EFAULT;
	}

	for (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) {
		vq = &vsock->vqs[i];
		mutex_lock(&vq->mutex);
		vq->acked_features = features;
		mutex_unlock(&vq->mutex);
	}
	mutex_unlock(&vsock->dev.mutex);
	return 0;
}