#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct gfs2_sbd {TYPE_1__* sd_statfs_inode; TYPE_1__* sd_rindex; TYPE_1__* sd_quota_inode; scalar_t__ sd_rindex_uptodate; int /*<<< orphan*/  sd_journal_ready; int /*<<< orphan*/  sd_master_dir; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_rwsem; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int UNDO ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_clear_rgrpd (struct gfs2_sbd*) ; 
 void* gfs2_lookup_simple (struct inode*,char*) ; 
 int /*<<< orphan*/  gfs2_quota_imutex_key ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int init_journal (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  iput (TYPE_1__*) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_inodes(struct gfs2_sbd *sdp, int undo)
{
	int error = 0;
	struct inode *master = d_inode(sdp->sd_master_dir);

	if (undo)
		goto fail_qinode;

	error = init_journal(sdp, undo);
	complete_all(&sdp->sd_journal_ready);
	if (error)
		goto fail;

	/* Read in the master statfs inode */
	sdp->sd_statfs_inode = gfs2_lookup_simple(master, "statfs");
	if (IS_ERR(sdp->sd_statfs_inode)) {
		error = PTR_ERR(sdp->sd_statfs_inode);
		fs_err(sdp, "can't read in statfs inode: %d\n", error);
		goto fail_journal;
	}

	/* Read in the resource index inode */
	sdp->sd_rindex = gfs2_lookup_simple(master, "rindex");
	if (IS_ERR(sdp->sd_rindex)) {
		error = PTR_ERR(sdp->sd_rindex);
		fs_err(sdp, "can't get resource index inode: %d\n", error);
		goto fail_statfs;
	}
	sdp->sd_rindex_uptodate = 0;

	/* Read in the quota inode */
	sdp->sd_quota_inode = gfs2_lookup_simple(master, "quota");
	if (IS_ERR(sdp->sd_quota_inode)) {
		error = PTR_ERR(sdp->sd_quota_inode);
		fs_err(sdp, "can't get quota file inode: %d\n", error);
		goto fail_rindex;
	}
	/*
	 * i_rwsem on quota files is special. Since this inode is hidden system
	 * file, we are safe to define locking ourselves.
	 */
	lockdep_set_class(&sdp->sd_quota_inode->i_rwsem,
			  &gfs2_quota_imutex_key);

	error = gfs2_rindex_update(sdp);
	if (error)
		goto fail_qinode;

	return 0;

fail_qinode:
	iput(sdp->sd_quota_inode);
fail_rindex:
	gfs2_clear_rgrpd(sdp);
	iput(sdp->sd_rindex);
fail_statfs:
	iput(sdp->sd_statfs_inode);
fail_journal:
	init_journal(sdp, UNDO);
fail:
	return error;
}