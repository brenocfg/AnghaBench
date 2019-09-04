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
struct ocfs2_super {int dummy; } ;
struct ocfs2_inode_info {int ip_flags; int /*<<< orphan*/  ip_lock; struct inode* ip_next_orphan; scalar_t__ ip_blkno; } ;
struct ocfs2_dinode {int i_flags; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  enum ocfs2_orphan_reco_type { ____Placeholder_ocfs2_orphan_reco_type } ocfs2_orphan_reco_type ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  OCFS2_DIO_ORPHANED_FL ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_DIO_ORPHAN_ENTRY ; 
 int OCFS2_INODE_MAYBE_ORPHANED ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_recovering_orphan_dir (struct ocfs2_super*,int) ; 
 int ocfs2_del_inode_from_orphan (struct ocfs2_super*,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_mark_recovering_orphan_dir (struct ocfs2_super*,int) ; 
 int ocfs2_queue_orphans (struct ocfs2_super*,int,struct inode**,int) ; 
 int ocfs2_rw_lock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int ocfs2_truncate_file (struct inode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_recover_orphans (int) ; 
 int /*<<< orphan*/  trace_ocfs2_recover_orphans_iput (unsigned long long) ; 

__attribute__((used)) static int ocfs2_recover_orphans(struct ocfs2_super *osb,
				 int slot,
				 enum ocfs2_orphan_reco_type orphan_reco_type)
{
	int ret = 0;
	struct inode *inode = NULL;
	struct inode *iter;
	struct ocfs2_inode_info *oi;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di = NULL;

	trace_ocfs2_recover_orphans(slot);

	ocfs2_mark_recovering_orphan_dir(osb, slot);
	ret = ocfs2_queue_orphans(osb, slot, &inode, orphan_reco_type);
	ocfs2_clear_recovering_orphan_dir(osb, slot);

	/* Error here should be noted, but we want to continue with as
	 * many queued inodes as we've got. */
	if (ret)
		mlog_errno(ret);

	while (inode) {
		oi = OCFS2_I(inode);
		trace_ocfs2_recover_orphans_iput(
					(unsigned long long)oi->ip_blkno);

		iter = oi->ip_next_orphan;
		oi->ip_next_orphan = NULL;

		if (oi->ip_flags & OCFS2_INODE_DIO_ORPHAN_ENTRY) {
			inode_lock(inode);
			ret = ocfs2_rw_lock(inode, 1);
			if (ret < 0) {
				mlog_errno(ret);
				goto unlock_mutex;
			}
			/*
			 * We need to take and drop the inode lock to
			 * force read inode from disk.
			 */
			ret = ocfs2_inode_lock(inode, &di_bh, 1);
			if (ret) {
				mlog_errno(ret);
				goto unlock_rw;
			}

			di = (struct ocfs2_dinode *)di_bh->b_data;

			if (di->i_flags & cpu_to_le32(OCFS2_DIO_ORPHANED_FL)) {
				ret = ocfs2_truncate_file(inode, di_bh,
						i_size_read(inode));
				if (ret < 0) {
					if (ret != -ENOSPC)
						mlog_errno(ret);
					goto unlock_inode;
				}

				ret = ocfs2_del_inode_from_orphan(osb, inode,
						di_bh, 0, 0);
				if (ret)
					mlog_errno(ret);
			}
unlock_inode:
			ocfs2_inode_unlock(inode, 1);
			brelse(di_bh);
			di_bh = NULL;
unlock_rw:
			ocfs2_rw_unlock(inode, 1);
unlock_mutex:
			inode_unlock(inode);

			/* clear dio flag in ocfs2_inode_info */
			oi->ip_flags &= ~OCFS2_INODE_DIO_ORPHAN_ENTRY;
		} else {
			spin_lock(&oi->ip_lock);
			/* Set the proper information to get us going into
			 * ocfs2_delete_inode. */
			oi->ip_flags |= OCFS2_INODE_MAYBE_ORPHANED;
			spin_unlock(&oi->ip_lock);
		}

		iput(inode);
		inode = iter;
	}

	return ret;
}