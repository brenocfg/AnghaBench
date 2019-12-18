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
struct virtio_fs {int dummy; } ;
struct fuse_iqueue {struct virtio_fs* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_fs_mutex ; 
 int /*<<< orphan*/  virtio_fs_put (struct virtio_fs*) ; 

__attribute__((used)) static void virtio_fs_fiq_release(struct fuse_iqueue *fiq)
{
	struct virtio_fs *vfs = fiq->priv;

	mutex_lock(&virtio_fs_mutex);
	virtio_fs_put(vfs);
	mutex_unlock(&virtio_fs_mutex);
}