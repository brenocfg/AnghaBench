#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct TYPE_6__ {int major_ver; int cluster_size; int /*<<< orphan*/  nls_map; int /*<<< orphan*/ * upcase; scalar_t__ upcase_len; int /*<<< orphan*/ * attrdef; scalar_t__ attrdef_size; int /*<<< orphan*/ * mft_ino; int /*<<< orphan*/ * mftmirr_ino; int /*<<< orphan*/ * logfile_ino; int /*<<< orphan*/  mftbmp_lock; int /*<<< orphan*/ * mftbmp_ino; int /*<<< orphan*/  lcnbmp_lock; int /*<<< orphan*/ * lcnbmp_ino; int /*<<< orphan*/ * root_ino; int /*<<< orphan*/ * secure_ino; int /*<<< orphan*/ * extend_ino; int /*<<< orphan*/ * quota_ino; int /*<<< orphan*/ * quota_q_ino; int /*<<< orphan*/ * usnjrnl_ino; int /*<<< orphan*/ * usnjrnl_max_ino; int /*<<< orphan*/ * usnjrnl_j_ino; int /*<<< orphan*/ * vol_ino; } ;
typedef  TYPE_1__ ntfs_volume ;

/* Variables and functions */
 TYPE_1__* NTFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  NVolErrors (TYPE_1__*) ; 
 int /*<<< orphan*/  VOLUME_IS_DIRTY ; 
 int /*<<< orphan*/ * default_upcase ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_compression_buffers () ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ntfs_clear_volume_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_commit_inode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/  ntfs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfs_lock ; 
 int /*<<< orphan*/  ntfs_nr_compression_users ; 
 int /*<<< orphan*/  ntfs_nr_upcase_users ; 
 int /*<<< orphan*/  ntfs_warning (struct super_block*,char*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_inode_now (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ntfs_put_super(struct super_block *sb)
{
	ntfs_volume *vol = NTFS_SB(sb);

	ntfs_debug("Entering.");

#ifdef NTFS_RW
	/*
	 * Commit all inodes while they are still open in case some of them
	 * cause others to be dirtied.
	 */
	ntfs_commit_inode(vol->vol_ino);

	/* NTFS 3.0+ specific. */
	if (vol->major_ver >= 3) {
		if (vol->usnjrnl_j_ino)
			ntfs_commit_inode(vol->usnjrnl_j_ino);
		if (vol->usnjrnl_max_ino)
			ntfs_commit_inode(vol->usnjrnl_max_ino);
		if (vol->usnjrnl_ino)
			ntfs_commit_inode(vol->usnjrnl_ino);
		if (vol->quota_q_ino)
			ntfs_commit_inode(vol->quota_q_ino);
		if (vol->quota_ino)
			ntfs_commit_inode(vol->quota_ino);
		if (vol->extend_ino)
			ntfs_commit_inode(vol->extend_ino);
		if (vol->secure_ino)
			ntfs_commit_inode(vol->secure_ino);
	}

	ntfs_commit_inode(vol->root_ino);

	down_write(&vol->lcnbmp_lock);
	ntfs_commit_inode(vol->lcnbmp_ino);
	up_write(&vol->lcnbmp_lock);

	down_write(&vol->mftbmp_lock);
	ntfs_commit_inode(vol->mftbmp_ino);
	up_write(&vol->mftbmp_lock);

	if (vol->logfile_ino)
		ntfs_commit_inode(vol->logfile_ino);

	if (vol->mftmirr_ino)
		ntfs_commit_inode(vol->mftmirr_ino);
	ntfs_commit_inode(vol->mft_ino);

	/*
	 * If a read-write mount and no volume errors have occurred, mark the
	 * volume clean.  Also, re-commit all affected inodes.
	 */
	if (!sb_rdonly(sb)) {
		if (!NVolErrors(vol)) {
			if (ntfs_clear_volume_flags(vol, VOLUME_IS_DIRTY))
				ntfs_warning(sb, "Failed to clear dirty bit "
						"in volume information "
						"flags.  Run chkdsk.");
			ntfs_commit_inode(vol->vol_ino);
			ntfs_commit_inode(vol->root_ino);
			if (vol->mftmirr_ino)
				ntfs_commit_inode(vol->mftmirr_ino);
			ntfs_commit_inode(vol->mft_ino);
		} else {
			ntfs_warning(sb, "Volume has errors.  Leaving volume "
					"marked dirty.  Run chkdsk.");
		}
	}
#endif /* NTFS_RW */

	iput(vol->vol_ino);
	vol->vol_ino = NULL;

	/* NTFS 3.0+ specific clean up. */
	if (vol->major_ver >= 3) {
#ifdef NTFS_RW
		if (vol->usnjrnl_j_ino) {
			iput(vol->usnjrnl_j_ino);
			vol->usnjrnl_j_ino = NULL;
		}
		if (vol->usnjrnl_max_ino) {
			iput(vol->usnjrnl_max_ino);
			vol->usnjrnl_max_ino = NULL;
		}
		if (vol->usnjrnl_ino) {
			iput(vol->usnjrnl_ino);
			vol->usnjrnl_ino = NULL;
		}
		if (vol->quota_q_ino) {
			iput(vol->quota_q_ino);
			vol->quota_q_ino = NULL;
		}
		if (vol->quota_ino) {
			iput(vol->quota_ino);
			vol->quota_ino = NULL;
		}
#endif /* NTFS_RW */
		if (vol->extend_ino) {
			iput(vol->extend_ino);
			vol->extend_ino = NULL;
		}
		if (vol->secure_ino) {
			iput(vol->secure_ino);
			vol->secure_ino = NULL;
		}
	}

	iput(vol->root_ino);
	vol->root_ino = NULL;

	down_write(&vol->lcnbmp_lock);
	iput(vol->lcnbmp_ino);
	vol->lcnbmp_ino = NULL;
	up_write(&vol->lcnbmp_lock);

	down_write(&vol->mftbmp_lock);
	iput(vol->mftbmp_ino);
	vol->mftbmp_ino = NULL;
	up_write(&vol->mftbmp_lock);

#ifdef NTFS_RW
	if (vol->logfile_ino) {
		iput(vol->logfile_ino);
		vol->logfile_ino = NULL;
	}
	if (vol->mftmirr_ino) {
		/* Re-commit the mft mirror and mft just in case. */
		ntfs_commit_inode(vol->mftmirr_ino);
		ntfs_commit_inode(vol->mft_ino);
		iput(vol->mftmirr_ino);
		vol->mftmirr_ino = NULL;
	}
	/*
	 * We should have no dirty inodes left, due to
	 * mft.c::ntfs_mft_writepage() cleaning all the dirty pages as
	 * the underlying mft records are written out and cleaned.
	 */
	ntfs_commit_inode(vol->mft_ino);
	write_inode_now(vol->mft_ino, 1);
#endif /* NTFS_RW */

	iput(vol->mft_ino);
	vol->mft_ino = NULL;

	/* Throw away the table of attribute definitions. */
	vol->attrdef_size = 0;
	if (vol->attrdef) {
		ntfs_free(vol->attrdef);
		vol->attrdef = NULL;
	}
	vol->upcase_len = 0;
	/*
	 * Destroy the global default upcase table if necessary.  Also decrease
	 * the number of upcase users if we are a user.
	 */
	mutex_lock(&ntfs_lock);
	if (vol->upcase == default_upcase) {
		ntfs_nr_upcase_users--;
		vol->upcase = NULL;
	}
	if (!ntfs_nr_upcase_users && default_upcase) {
		ntfs_free(default_upcase);
		default_upcase = NULL;
	}
	if (vol->cluster_size <= 4096 && !--ntfs_nr_compression_users)
		free_compression_buffers();
	mutex_unlock(&ntfs_lock);
	if (vol->upcase) {
		ntfs_free(vol->upcase);
		vol->upcase = NULL;
	}

	unload_nls(vol->nls_map);

	sb->s_fs_info = NULL;
	kfree(vol);
}