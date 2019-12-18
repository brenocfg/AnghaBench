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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; } ;
struct fuse_conn {int delete_stale; int /*<<< orphan*/  release; } ;
struct fs_context {int /*<<< orphan*/  root; struct fuse_conn* s_fs_info; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  SB_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_conn_init (struct fuse_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct virtio_fs*) ; 
 int /*<<< orphan*/  fuse_conn_put (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_free_conn ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 struct fuse_conn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 struct super_block* sget_fc (struct fs_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio_fs_fill_super (struct super_block*) ; 
 struct virtio_fs* virtio_fs_find_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_fs_fiq_ops ; 
 int /*<<< orphan*/  virtio_fs_mutex ; 
 int /*<<< orphan*/  virtio_fs_put (struct virtio_fs*) ; 
 int /*<<< orphan*/  virtio_fs_set_super ; 
 int /*<<< orphan*/  virtio_fs_test_super ; 

__attribute__((used)) static int virtio_fs_get_tree(struct fs_context *fsc)
{
	struct virtio_fs *fs;
	struct super_block *sb;
	struct fuse_conn *fc;
	int err;

	/* This gets a reference on virtio_fs object. This ptr gets installed
	 * in fc->iq->priv. Once fuse_conn is going away, it calls ->put()
	 * to drop the reference to this object.
	 */
	fs = virtio_fs_find_instance(fsc->source);
	if (!fs) {
		pr_info("virtio-fs: tag <%s> not found\n", fsc->source);
		return -EINVAL;
	}

	fc = kzalloc(sizeof(struct fuse_conn), GFP_KERNEL);
	if (!fc) {
		mutex_lock(&virtio_fs_mutex);
		virtio_fs_put(fs);
		mutex_unlock(&virtio_fs_mutex);
		return -ENOMEM;
	}

	fuse_conn_init(fc, get_user_ns(current_user_ns()), &virtio_fs_fiq_ops,
		       fs);
	fc->release = fuse_free_conn;
	fc->delete_stale = true;

	fsc->s_fs_info = fc;
	sb = sget_fc(fsc, virtio_fs_test_super, virtio_fs_set_super);
	fuse_conn_put(fc);
	if (IS_ERR(sb))
		return PTR_ERR(sb);

	if (!sb->s_root) {
		err = virtio_fs_fill_super(sb);
		if (err) {
			deactivate_locked_super(sb);
			return err;
		}

		sb->s_flags |= SB_ACTIVE;
	}

	WARN_ON(fsc->root);
	fsc->root = dget(sb->s_root);
	return 0;
}