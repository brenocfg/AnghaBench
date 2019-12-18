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
struct virtio_fs {int /*<<< orphan*/  list; } ;
struct virtio_device {struct virtio_fs* priv; TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtio_fs_cleanup_vqs (struct virtio_device*,struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_drain_all_queues (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_mutex ; 
 int /*<<< orphan*/  virtio_fs_put (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_stop_all_queues (struct virtio_fs*) ; 

__attribute__((used)) static void virtio_fs_remove(struct virtio_device *vdev)
{
	struct virtio_fs *fs = vdev->priv;

	mutex_lock(&virtio_fs_mutex);
	/* This device is going away. No one should get new reference */
	list_del_init(&fs->list);
	virtio_fs_stop_all_queues(fs);
	virtio_fs_drain_all_queues(fs);
	vdev->config->reset(vdev);
	virtio_fs_cleanup_vqs(vdev, fs);

	vdev->priv = NULL;
	/* Put device reference on virtio_fs object */
	virtio_fs_put(fs);
	mutex_unlock(&virtio_fs_mutex);
}