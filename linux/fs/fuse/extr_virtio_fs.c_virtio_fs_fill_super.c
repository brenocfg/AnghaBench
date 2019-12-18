#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtio_fs_vq {TYPE_2__* fud; } ;
struct virtio_fs {unsigned int nvqs; struct virtio_fs_vq* vqs; int /*<<< orphan*/  tag; int /*<<< orphan*/  list; } ;
struct super_block {int dummy; } ;
struct fuse_fs_context {int default_permissions; int allow_other; int blksize; int destroy; int no_control; int no_force_umount; int no_mount_options; void** fudptr; int /*<<< orphan*/  max_read; int /*<<< orphan*/  rootmode; } ;
struct TYPE_4__ {struct virtio_fs* priv; } ;
struct fuse_conn {TYPE_1__ iq; } ;
struct TYPE_5__ {struct fuse_conn* fc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  UINT_MAX ; 
 unsigned int VQ_REQUEST ; 
 TYPE_2__* fuse_dev_alloc () ; 
 int /*<<< orphan*/  fuse_dev_install (TYPE_2__*,struct fuse_conn*) ; 
 int fuse_fill_super_common (struct super_block*,struct fuse_fs_context*) ; 
 int /*<<< orphan*/  fuse_send_init (struct fuse_conn*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_fs_free_devs (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_mutex ; 
 int /*<<< orphan*/  virtio_fs_start_all_queues (struct virtio_fs*) ; 

__attribute__((used)) static int virtio_fs_fill_super(struct super_block *sb)
{
	struct fuse_conn *fc = get_fuse_conn_super(sb);
	struct virtio_fs *fs = fc->iq.priv;
	unsigned int i;
	int err;
	struct fuse_fs_context ctx = {
		.rootmode = S_IFDIR,
		.default_permissions = 1,
		.allow_other = 1,
		.max_read = UINT_MAX,
		.blksize = 512,
		.destroy = true,
		.no_control = true,
		.no_force_umount = true,
		.no_mount_options = true,
	};

	mutex_lock(&virtio_fs_mutex);

	/* After holding mutex, make sure virtiofs device is still there.
	 * Though we are holding a reference to it, drive ->remove might
	 * still have cleaned up virtual queues. In that case bail out.
	 */
	err = -EINVAL;
	if (list_empty(&fs->list)) {
		pr_info("virtio-fs: tag <%s> not found\n", fs->tag);
		goto err;
	}

	err = -ENOMEM;
	/* Allocate fuse_dev for hiprio and notification queues */
	for (i = 0; i < VQ_REQUEST; i++) {
		struct virtio_fs_vq *fsvq = &fs->vqs[i];

		fsvq->fud = fuse_dev_alloc();
		if (!fsvq->fud)
			goto err_free_fuse_devs;
	}

	ctx.fudptr = (void **)&fs->vqs[VQ_REQUEST].fud;
	err = fuse_fill_super_common(sb, &ctx);
	if (err < 0)
		goto err_free_fuse_devs;

	fc = fs->vqs[VQ_REQUEST].fud->fc;

	for (i = 0; i < fs->nvqs; i++) {
		struct virtio_fs_vq *fsvq = &fs->vqs[i];

		if (i == VQ_REQUEST)
			continue; /* already initialized */
		fuse_dev_install(fsvq->fud, fc);
	}

	/* Previous unmount will stop all queues. Start these again */
	virtio_fs_start_all_queues(fs);
	fuse_send_init(fc);
	mutex_unlock(&virtio_fs_mutex);
	return 0;

err_free_fuse_devs:
	virtio_fs_free_devs(fs);
err:
	mutex_unlock(&virtio_fs_mutex);
	return err;
}