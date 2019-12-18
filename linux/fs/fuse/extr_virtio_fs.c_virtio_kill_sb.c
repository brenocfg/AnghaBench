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
struct virtio_fs_vq {int connected; int /*<<< orphan*/  lock; } ;
struct virtio_fs {struct virtio_fs_vq* vqs; } ;
struct super_block {int dummy; } ;
struct TYPE_2__ {struct virtio_fs* priv; } ;
struct fuse_conn {TYPE_1__ iq; } ;

/* Variables and functions */
 size_t VQ_HIPRIO ; 
 void fuse_kill_sb_anon (struct super_block*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_fs_drain_all_queues (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_free_devs (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_stop_all_queues (struct virtio_fs*) ; 

__attribute__((used)) static void virtio_kill_sb(struct super_block *sb)
{
	struct fuse_conn *fc = get_fuse_conn_super(sb);
	struct virtio_fs *vfs;
	struct virtio_fs_vq *fsvq;

	/* If mount failed, we can still be called without any fc */
	if (!fc)
		return fuse_kill_sb_anon(sb);

	vfs = fc->iq.priv;
	fsvq = &vfs->vqs[VQ_HIPRIO];

	/* Stop forget queue. Soon destroy will be sent */
	spin_lock(&fsvq->lock);
	fsvq->connected = false;
	spin_unlock(&fsvq->lock);
	virtio_fs_drain_all_queues(vfs);

	fuse_kill_sb_anon(sb);

	/* fuse_kill_sb_anon() must have sent destroy. Stop all queues
	 * and drain one more time and free fuse devices. Freeing fuse
	 * devices will drop their reference on fuse_conn and that in
	 * turn will drop its reference on virtio_fs object.
	 */
	virtio_fs_stop_all_queues(vfs);
	virtio_fs_drain_all_queues(vfs);
	virtio_fs_free_devs(vfs);
}