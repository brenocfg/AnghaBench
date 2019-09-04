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
struct vhost_virtqueue {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * private_data; } ;
struct vhost_test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *vhost_test_stop_vq(struct vhost_test *n,
				struct vhost_virtqueue *vq)
{
	void *private;

	mutex_lock(&vq->mutex);
	private = vq->private_data;
	vq->private_data = NULL;
	mutex_unlock(&vq->mutex);
	return private;
}