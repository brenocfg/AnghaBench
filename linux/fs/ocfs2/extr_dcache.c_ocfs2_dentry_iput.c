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
struct ocfs2_dentry_lock {scalar_t__ dl_count; } ;
struct inode {int dummy; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_sb; struct ocfs2_dentry_lock* d_fsdata; } ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int,struct dentry*) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,struct dentry*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_dentry_lock_put (int /*<<< orphan*/ ,struct ocfs2_dentry_lock*) ; 

__attribute__((used)) static void ocfs2_dentry_iput(struct dentry *dentry, struct inode *inode)
{
	struct ocfs2_dentry_lock *dl = dentry->d_fsdata;

	if (!dl) {
		/*
		 * No dentry lock is ok if we're disconnected or
		 * unhashed.
		 */
		if (!(dentry->d_flags & DCACHE_DISCONNECTED) &&
		    !d_unhashed(dentry)) {
			unsigned long long ino = 0ULL;
			if (inode)
				ino = (unsigned long long)OCFS2_I(inode)->ip_blkno;
			mlog(ML_ERROR, "Dentry is missing cluster lock. "
			     "inode: %llu, d_flags: 0x%x, d_name: %pd\n",
			     ino, dentry->d_flags, dentry);
		}

		goto out;
	}

	mlog_bug_on_msg(dl->dl_count == 0, "dentry: %pd, count: %u\n",
			dentry, dl->dl_count);

	ocfs2_dentry_lock_put(OCFS2_SB(dentry->d_sb), dl);

out:
	iput(inode);
}