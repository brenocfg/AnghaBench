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
struct virtio_fs {int /*<<< orphan*/  refcount; } ;
struct virtio_device {struct virtio_fs* priv; TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct virtio_fs*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct virtio_fs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtio_device_ready (struct virtio_device*) ; 
 int virtio_fs_add_instance (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_cleanup_vqs (struct virtio_device*,struct virtio_fs*) ; 
 int virtio_fs_read_tag (struct virtio_device*,struct virtio_fs*) ; 
 int virtio_fs_setup_vqs (struct virtio_device*,struct virtio_fs*) ; 

__attribute__((used)) static int virtio_fs_probe(struct virtio_device *vdev)
{
	struct virtio_fs *fs;
	int ret;

	fs = kzalloc(sizeof(*fs), GFP_KERNEL);
	if (!fs)
		return -ENOMEM;
	kref_init(&fs->refcount);
	vdev->priv = fs;

	ret = virtio_fs_read_tag(vdev, fs);
	if (ret < 0)
		goto out;

	ret = virtio_fs_setup_vqs(vdev, fs);
	if (ret < 0)
		goto out;

	/* TODO vq affinity */

	/* Bring the device online in case the filesystem is mounted and
	 * requests need to be sent before we return.
	 */
	virtio_device_ready(vdev);

	ret = virtio_fs_add_instance(fs);
	if (ret < 0)
		goto out_vqs;

	return 0;

out_vqs:
	vdev->config->reset(vdev);
	virtio_fs_cleanup_vqs(vdev, fs);

out:
	vdev->priv = NULL;
	kfree(fs);
	return ret;
}