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
struct inode {int dummy; } ;
struct TYPE_3__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_blkno; int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_check_range_for_refcount (struct inode*,scalar_t__,size_t) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_overwrite_io (struct inode*,struct buffer_head*,scalar_t__,size_t) ; 
 int ocfs2_prepare_inode_for_refcount (struct inode*,struct file*,scalar_t__,size_t,int*) ; 
 int ocfs2_try_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int ocfs2_write_remove_suid (struct inode*) ; 
 scalar_t__ should_remove_suid (struct dentry*) ; 
 int /*<<< orphan*/  trace_ocfs2_prepare_inode_for_write (int /*<<< orphan*/ ,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_prepare_inode_for_write(struct file *file,
					 loff_t pos, size_t count, int wait)
{
	int ret = 0, meta_level = 0, overwrite_io = 0;
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = d_inode(dentry);
	struct buffer_head *di_bh = NULL;
	loff_t end;

	/*
	 * We start with a read level meta lock and only jump to an ex
	 * if we need to make modifications here.
	 */
	for(;;) {
		if (wait)
			ret = ocfs2_inode_lock(inode, NULL, meta_level);
		else
			ret = ocfs2_try_inode_lock(inode,
				overwrite_io ? NULL : &di_bh, meta_level);
		if (ret < 0) {
			meta_level = -1;
			if (ret != -EAGAIN)
				mlog_errno(ret);
			goto out;
		}

		/*
		 * Check if IO will overwrite allocated blocks in case
		 * IOCB_NOWAIT flag is set.
		 */
		if (!wait && !overwrite_io) {
			overwrite_io = 1;
			if (!down_read_trylock(&OCFS2_I(inode)->ip_alloc_sem)) {
				ret = -EAGAIN;
				goto out_unlock;
			}

			ret = ocfs2_overwrite_io(inode, di_bh, pos, count);
			brelse(di_bh);
			di_bh = NULL;
			up_read(&OCFS2_I(inode)->ip_alloc_sem);
			if (ret < 0) {
				if (ret != -EAGAIN)
					mlog_errno(ret);
				goto out_unlock;
			}
		}

		/* Clear suid / sgid if necessary. We do this here
		 * instead of later in the write path because
		 * remove_suid() calls ->setattr without any hint that
		 * we may have already done our cluster locking. Since
		 * ocfs2_setattr() *must* take cluster locks to
		 * proceed, this will lead us to recursively lock the
		 * inode. There's also the dinode i_size state which
		 * can be lost via setattr during extending writes (we
		 * set inode->i_size at the end of a write. */
		if (should_remove_suid(dentry)) {
			if (meta_level == 0) {
				ocfs2_inode_unlock(inode, meta_level);
				meta_level = 1;
				continue;
			}

			ret = ocfs2_write_remove_suid(inode);
			if (ret < 0) {
				mlog_errno(ret);
				goto out_unlock;
			}
		}

		end = pos + count;

		ret = ocfs2_check_range_for_refcount(inode, pos, count);
		if (ret == 1) {
			ocfs2_inode_unlock(inode, meta_level);
			meta_level = -1;

			ret = ocfs2_prepare_inode_for_refcount(inode,
							       file,
							       pos,
							       count,
							       &meta_level);
		}

		if (ret < 0) {
			mlog_errno(ret);
			goto out_unlock;
		}

		break;
	}

out_unlock:
	trace_ocfs2_prepare_inode_for_write(OCFS2_I(inode)->ip_blkno,
					    pos, count, wait);

	brelse(di_bh);

	if (meta_level >= 0)
		ocfs2_inode_unlock(inode, meta_level);

out:
	return ret;
}