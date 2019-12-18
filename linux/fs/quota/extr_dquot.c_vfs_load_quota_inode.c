#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_bdev; int /*<<< orphan*/ * s_user_ns; TYPE_2__* dq_op; TYPE_1__* s_op; } ;
struct quota_info {int flags; int /*<<< orphan*/ ** files; TYPE_4__* info; TYPE_3__** ops; } ;
struct quota_format_type {TYPE_3__* qf_ops; } ;
struct inode {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct TYPE_8__ {int dqi_fmt_id; int /*<<< orphan*/  dqi_flags; int /*<<< orphan*/  dqi_dirty_list; struct quota_format_type* dqi_format; } ;
struct TYPE_7__ {int (* read_file_info ) (struct super_block*,int) ;int /*<<< orphan*/  (* check_quota_file ) (struct super_block*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * get_projid; } ;
struct TYPE_5__ {int /*<<< orphan*/  quota_read; int /*<<< orphan*/  quota_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQF_SYS_FILE ; 
 int DQUOT_QUOTA_SYS_FILE ; 
 unsigned int DQUOT_USAGE_ENABLED ; 
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EROFS ; 
 int ESRCH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_RDONLY (struct inode*) ; 
 int PRJQUOTA ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  __dquot_drop (struct inode*) ; 
 int add_dquot_ref (struct super_block*,int) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  dq_state_lock ; 
 int /*<<< orphan*/  dquot_disable (struct super_block*,int,unsigned int) ; 
 int dquot_state_flag (unsigned int,int) ; 
 struct quota_format_type* find_quota_format (int) ; 
 int /*<<< orphan*/ * igrab (struct inode*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  invalidate_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  put_quota_format (struct quota_format_type*) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 scalar_t__ sb_has_quota_loaded (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int) ; 
 int stub2 (struct super_block*,int) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int vfs_load_quota_inode(struct inode *inode, int type, int format_id,
	unsigned int flags)
{
	struct quota_format_type *fmt = find_quota_format(format_id);
	struct super_block *sb = inode->i_sb;
	struct quota_info *dqopt = sb_dqopt(sb);
	int error;

	if (!fmt)
		return -ESRCH;
	if (!S_ISREG(inode->i_mode)) {
		error = -EACCES;
		goto out_fmt;
	}
	if (IS_RDONLY(inode)) {
		error = -EROFS;
		goto out_fmt;
	}
	if (!sb->s_op->quota_write || !sb->s_op->quota_read ||
	    (type == PRJQUOTA && sb->dq_op->get_projid == NULL)) {
		error = -EINVAL;
		goto out_fmt;
	}
	/* Filesystems outside of init_user_ns not yet supported */
	if (sb->s_user_ns != &init_user_ns) {
		error = -EINVAL;
		goto out_fmt;
	}
	/* Usage always has to be set... */
	if (!(flags & DQUOT_USAGE_ENABLED)) {
		error = -EINVAL;
		goto out_fmt;
	}
	if (sb_has_quota_loaded(sb, type)) {
		error = -EBUSY;
		goto out_fmt;
	}

	if (!(dqopt->flags & DQUOT_QUOTA_SYS_FILE)) {
		/* As we bypass the pagecache we must now flush all the
		 * dirty data and invalidate caches so that kernel sees
		 * changes from userspace. It is not enough to just flush
		 * the quota file since if blocksize < pagesize, invalidation
		 * of the cache could fail because of other unrelated dirty
		 * data */
		sync_filesystem(sb);
		invalidate_bdev(sb->s_bdev);
	}

	if (!(dqopt->flags & DQUOT_QUOTA_SYS_FILE)) {
		/* We don't want quota and atime on quota files (deadlocks
		 * possible) Also nobody should write to the file - we use
		 * special IO operations which ignore the immutable bit. */
		inode_lock(inode);
		inode->i_flags |= S_NOQUOTA;
		inode_unlock(inode);
		/*
		 * When S_NOQUOTA is set, remove dquot references as no more
		 * references can be added
		 */
		__dquot_drop(inode);
	}

	error = -EIO;
	dqopt->files[type] = igrab(inode);
	if (!dqopt->files[type])
		goto out_file_flags;
	error = -EINVAL;
	if (!fmt->qf_ops->check_quota_file(sb, type))
		goto out_file_init;

	dqopt->ops[type] = fmt->qf_ops;
	dqopt->info[type].dqi_format = fmt;
	dqopt->info[type].dqi_fmt_id = format_id;
	INIT_LIST_HEAD(&dqopt->info[type].dqi_dirty_list);
	error = dqopt->ops[type]->read_file_info(sb, type);
	if (error < 0)
		goto out_file_init;
	if (dqopt->flags & DQUOT_QUOTA_SYS_FILE) {
		spin_lock(&dq_data_lock);
		dqopt->info[type].dqi_flags |= DQF_SYS_FILE;
		spin_unlock(&dq_data_lock);
	}
	spin_lock(&dq_state_lock);
	dqopt->flags |= dquot_state_flag(flags, type);
	spin_unlock(&dq_state_lock);

	error = add_dquot_ref(sb, type);
	if (error)
		dquot_disable(sb, type, flags);

	return error;
out_file_init:
	dqopt->files[type] = NULL;
	iput(inode);
out_file_flags:
	inode_lock(inode);
	inode->i_flags &= ~S_NOQUOTA;
	inode_unlock(inode);
out_fmt:
	put_quota_format(fmt);

	return error;
}