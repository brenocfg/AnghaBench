#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint ;
struct TYPE_5__ {int /*<<< orphan*/ * b; } ;
struct xfs_sb {int sb_versionnum; scalar_t__ sb_spino_align; int sb_qflags; int /*<<< orphan*/  sb_rootino; int /*<<< orphan*/  sb_logblocks; int /*<<< orphan*/  sb_logstart; int /*<<< orphan*/  sb_agcount; TYPE_2__ sb_uuid; int /*<<< orphan*/  sb_features2; int /*<<< orphan*/  sb_bad_features2; } ;
struct TYPE_4__ {int /*<<< orphan*/  xs_kobj; } ;
struct xfs_mount {int m_update_sb; int m_flags; int m_fail_unmount; char* m_fsname; int* m_fixedfsid; scalar_t__ m_logdev_targp; scalar_t__ m_qflags; scalar_t__ m_ddev_targp; int /*<<< orphan*/  m_kobj; TYPE_1__ m_stats; int /*<<< orphan*/  m_reclaim_work; struct xfs_sb m_sb; struct xfs_inode* m_rootip; int /*<<< orphan*/  m_maxagi; } ;
struct xfs_inode {scalar_t__ i_ino; } ;
struct xfs_ino_geometry {int /*<<< orphan*/  inode_cluster_size_raw; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int EINVAL ; 
 int ENOSPC ; 
 struct xfs_ino_geometry* M_IGEO (struct xfs_mount*) ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int /*<<< orphan*/  SYNC_WAIT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_3__* VFS_I (struct xfs_inode*) ; 
 int XFS_ALL_QUOTA_ACCT ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 scalar_t__ XFS_B_TO_FSBT (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int /*<<< orphan*/  XFS_ERROR_REPORT (char*,int /*<<< orphan*/ ,struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_FSB_TO_BB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_IGET_UNTRUSTED ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_IS_QUOTA_ON (struct xfs_mount*) ; 
 scalar_t__ XFS_IS_QUOTA_RUNNING (struct xfs_mount*) ; 
 int XFS_MOUNT_ATTR2 ; 
 int XFS_MOUNT_NOATTR2 ; 
 int XFS_MOUNT_NORECOVERY ; 
 int XFS_MOUNT_RDONLY ; 
 int XFS_MOUNT_UNMOUNTING ; 
 int XFS_SB_VERSION_NLINKBIT ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_alloc_compute_maxlevels (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_bmap_compute_maxlevels (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int xfs_check_sizes (struct xfs_mount*) ; 
 int xfs_check_summary_counts (struct xfs_mount*) ; 
 int xfs_da_mount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_da_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_default_resblks (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_err (struct xfs_mount*,char*,int) ; 
 int /*<<< orphan*/  xfs_error_sysfs_del (struct xfs_mount*) ; 
 int xfs_error_sysfs_init (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_errortag_del (struct xfs_mount*) ; 
 int xfs_errortag_init (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_force_shutdown (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_free_perag (struct xfs_mount*) ; 
 int xfs_fs_reserve_ag_blocks (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_fs_unreserve_ag_blocks (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_health_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_ialloc_setup_geometry (struct xfs_mount*) ; 
 int xfs_iget (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_inode**) ; 
 int xfs_initialize_perag (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_irele (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_log_mount (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_mount_cancel (struct xfs_mount*) ; 
 int xfs_log_mount_finish (struct xfs_mount*) ; 
 int xfs_mount_reset_sbqflags (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_mp_ktype ; 
 int /*<<< orphan*/  xfs_notice (struct xfs_mount*,char*) ; 
 int /*<<< orphan*/  xfs_qm_mount_quotas (struct xfs_mount*) ; 
 int xfs_qm_newmount (struct xfs_mount*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  xfs_qm_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_qm_unmount_quotas (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_quiesce_attr (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_reclaim_inodes (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_refcountbt_compute_maxlevels (struct xfs_mount*) ; 
 int xfs_reflink_recover_cow (struct xfs_mount*) ; 
 int xfs_reserve_blocks (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_rmapbt_compute_maxlevels (struct xfs_mount*) ; 
 int xfs_rtmount_init (struct xfs_mount*) ; 
 int xfs_rtmount_inodes (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_rtunmount_inodes (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_has_mismatched_features2 (struct xfs_sb*) ; 
 int /*<<< orphan*/  xfs_sb_mount_common (struct xfs_mount*,struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasattr2 (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hassparseinodes (struct xfs_sb*) ; 
 int /*<<< orphan*/  xfs_sb_version_removeattr2 (struct xfs_sb*) ; 
 int /*<<< orphan*/  xfs_set_low_space_thresholds (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_set_rw_sizes (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_stats_ktype ; 
 int xfs_sync_sb (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  xfs_sysfs_del (int /*<<< orphan*/ *) ; 
 int xfs_sysfs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xfs_trans_init (struct xfs_mount*) ; 
 int xfs_update_alignment (struct xfs_mount*) ; 
 int xfs_uuid_mount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_uuid_unmount (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_wait_buftarg (scalar_t__) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,...) ; 

int
xfs_mountfs(
	struct xfs_mount	*mp)
{
	struct xfs_sb		*sbp = &(mp->m_sb);
	struct xfs_inode	*rip;
	struct xfs_ino_geometry	*igeo = M_IGEO(mp);
	uint64_t		resblks;
	uint			quotamount = 0;
	uint			quotaflags = 0;
	int			error = 0;

	xfs_sb_mount_common(mp, sbp);

	/*
	 * Check for a mismatched features2 values.  Older kernels read & wrote
	 * into the wrong sb offset for sb_features2 on some platforms due to
	 * xfs_sb_t not being 64bit size aligned when sb_features2 was added,
	 * which made older superblock reading/writing routines swap it as a
	 * 64-bit value.
	 *
	 * For backwards compatibility, we make both slots equal.
	 *
	 * If we detect a mismatched field, we OR the set bits into the existing
	 * features2 field in case it has already been modified; we don't want
	 * to lose any features.  We then update the bad location with the ORed
	 * value so that older kernels will see any features2 flags. The
	 * superblock writeback code ensures the new sb_features2 is copied to
	 * sb_bad_features2 before it is logged or written to disk.
	 */
	if (xfs_sb_has_mismatched_features2(sbp)) {
		xfs_warn(mp, "correcting sb_features alignment problem");
		sbp->sb_features2 |= sbp->sb_bad_features2;
		mp->m_update_sb = true;

		/*
		 * Re-check for ATTR2 in case it was found in bad_features2
		 * slot.
		 */
		if (xfs_sb_version_hasattr2(&mp->m_sb) &&
		   !(mp->m_flags & XFS_MOUNT_NOATTR2))
			mp->m_flags |= XFS_MOUNT_ATTR2;
	}

	if (xfs_sb_version_hasattr2(&mp->m_sb) &&
	   (mp->m_flags & XFS_MOUNT_NOATTR2)) {
		xfs_sb_version_removeattr2(&mp->m_sb);
		mp->m_update_sb = true;

		/* update sb_versionnum for the clearing of the morebits */
		if (!sbp->sb_features2)
			mp->m_update_sb = true;
	}

	/* always use v2 inodes by default now */
	if (!(mp->m_sb.sb_versionnum & XFS_SB_VERSION_NLINKBIT)) {
		mp->m_sb.sb_versionnum |= XFS_SB_VERSION_NLINKBIT;
		mp->m_update_sb = true;
	}

	/*
	 * Check if sb_agblocks is aligned at stripe boundary
	 * If sb_agblocks is NOT aligned turn off m_dalign since
	 * allocator alignment is within an ag, therefore ag has
	 * to be aligned at stripe boundary.
	 */
	error = xfs_update_alignment(mp);
	if (error)
		goto out;

	xfs_alloc_compute_maxlevels(mp);
	xfs_bmap_compute_maxlevels(mp, XFS_DATA_FORK);
	xfs_bmap_compute_maxlevels(mp, XFS_ATTR_FORK);
	xfs_ialloc_setup_geometry(mp);
	xfs_rmapbt_compute_maxlevels(mp);
	xfs_refcountbt_compute_maxlevels(mp);

	/* enable fail_at_unmount as default */
	mp->m_fail_unmount = true;

	error = xfs_sysfs_init(&mp->m_kobj, &xfs_mp_ktype, NULL, mp->m_fsname);
	if (error)
		goto out;

	error = xfs_sysfs_init(&mp->m_stats.xs_kobj, &xfs_stats_ktype,
			       &mp->m_kobj, "stats");
	if (error)
		goto out_remove_sysfs;

	error = xfs_error_sysfs_init(mp);
	if (error)
		goto out_del_stats;

	error = xfs_errortag_init(mp);
	if (error)
		goto out_remove_error_sysfs;

	error = xfs_uuid_mount(mp);
	if (error)
		goto out_remove_errortag;

	/*
	 * Set the minimum read and write sizes
	 */
	xfs_set_rw_sizes(mp);

	/* set the low space thresholds for dynamic preallocation */
	xfs_set_low_space_thresholds(mp);

	/*
	 * If enabled, sparse inode chunk alignment is expected to match the
	 * cluster size. Full inode chunk alignment must match the chunk size,
	 * but that is checked on sb read verification...
	 */
	if (xfs_sb_version_hassparseinodes(&mp->m_sb) &&
	    mp->m_sb.sb_spino_align !=
			XFS_B_TO_FSBT(mp, igeo->inode_cluster_size_raw)) {
		xfs_warn(mp,
	"Sparse inode block alignment (%u) must match cluster size (%llu).",
			 mp->m_sb.sb_spino_align,
			 XFS_B_TO_FSBT(mp, igeo->inode_cluster_size_raw));
		error = -EINVAL;
		goto out_remove_uuid;
	}

	/*
	 * Check that the data (and log if separate) is an ok size.
	 */
	error = xfs_check_sizes(mp);
	if (error)
		goto out_remove_uuid;

	/*
	 * Initialize realtime fields in the mount structure
	 */
	error = xfs_rtmount_init(mp);
	if (error) {
		xfs_warn(mp, "RT mount failed");
		goto out_remove_uuid;
	}

	/*
	 *  Copies the low order bits of the timestamp and the randomly
	 *  set "sequence" number out of a UUID.
	 */
	mp->m_fixedfsid[0] =
		(get_unaligned_be16(&sbp->sb_uuid.b[8]) << 16) |
		 get_unaligned_be16(&sbp->sb_uuid.b[4]);
	mp->m_fixedfsid[1] = get_unaligned_be32(&sbp->sb_uuid.b[0]);

	error = xfs_da_mount(mp);
	if (error) {
		xfs_warn(mp, "Failed dir/attr init: %d", error);
		goto out_remove_uuid;
	}

	/*
	 * Initialize the precomputed transaction reservations values.
	 */
	xfs_trans_init(mp);

	/*
	 * Allocate and initialize the per-ag data.
	 */
	error = xfs_initialize_perag(mp, sbp->sb_agcount, &mp->m_maxagi);
	if (error) {
		xfs_warn(mp, "Failed per-ag init: %d", error);
		goto out_free_dir;
	}

	if (!sbp->sb_logblocks) {
		xfs_warn(mp, "no log defined");
		XFS_ERROR_REPORT("xfs_mountfs", XFS_ERRLEVEL_LOW, mp);
		error = -EFSCORRUPTED;
		goto out_free_perag;
	}

	/*
	 * Log's mount-time initialization. The first part of recovery can place
	 * some items on the AIL, to be handled when recovery is finished or
	 * cancelled.
	 */
	error = xfs_log_mount(mp, mp->m_logdev_targp,
			      XFS_FSB_TO_DADDR(mp, sbp->sb_logstart),
			      XFS_FSB_TO_BB(mp, sbp->sb_logblocks));
	if (error) {
		xfs_warn(mp, "log mount failed");
		goto out_fail_wait;
	}

	/* Make sure the summary counts are ok. */
	error = xfs_check_summary_counts(mp);
	if (error)
		goto out_log_dealloc;

	/*
	 * Get and sanity-check the root inode.
	 * Save the pointer to it in the mount structure.
	 */
	error = xfs_iget(mp, NULL, sbp->sb_rootino, XFS_IGET_UNTRUSTED,
			 XFS_ILOCK_EXCL, &rip);
	if (error) {
		xfs_warn(mp,
			"Failed to read root inode 0x%llx, error %d",
			sbp->sb_rootino, -error);
		goto out_log_dealloc;
	}

	ASSERT(rip != NULL);

	if (unlikely(!S_ISDIR(VFS_I(rip)->i_mode))) {
		xfs_warn(mp, "corrupted root inode %llu: not a directory",
			(unsigned long long)rip->i_ino);
		xfs_iunlock(rip, XFS_ILOCK_EXCL);
		XFS_ERROR_REPORT("xfs_mountfs_int(2)", XFS_ERRLEVEL_LOW,
				 mp);
		error = -EFSCORRUPTED;
		goto out_rele_rip;
	}
	mp->m_rootip = rip;	/* save it */

	xfs_iunlock(rip, XFS_ILOCK_EXCL);

	/*
	 * Initialize realtime inode pointers in the mount structure
	 */
	error = xfs_rtmount_inodes(mp);
	if (error) {
		/*
		 * Free up the root inode.
		 */
		xfs_warn(mp, "failed to read RT inodes");
		goto out_rele_rip;
	}

	/*
	 * If this is a read-only mount defer the superblock updates until
	 * the next remount into writeable mode.  Otherwise we would never
	 * perform the update e.g. for the root filesystem.
	 */
	if (mp->m_update_sb && !(mp->m_flags & XFS_MOUNT_RDONLY)) {
		error = xfs_sync_sb(mp, false);
		if (error) {
			xfs_warn(mp, "failed to write sb changes");
			goto out_rtunmount;
		}
	}

	/*
	 * Initialise the XFS quota management subsystem for this mount
	 */
	if (XFS_IS_QUOTA_RUNNING(mp)) {
		error = xfs_qm_newmount(mp, &quotamount, &quotaflags);
		if (error)
			goto out_rtunmount;
	} else {
		ASSERT(!XFS_IS_QUOTA_ON(mp));

		/*
		 * If a file system had quotas running earlier, but decided to
		 * mount without -o uquota/pquota/gquota options, revoke the
		 * quotachecked license.
		 */
		if (mp->m_sb.sb_qflags & XFS_ALL_QUOTA_ACCT) {
			xfs_notice(mp, "resetting quota flags");
			error = xfs_mount_reset_sbqflags(mp);
			if (error)
				goto out_rtunmount;
		}
	}

	/*
	 * Finish recovering the file system.  This part needed to be delayed
	 * until after the root and real-time bitmap inodes were consistently
	 * read in.
	 */
	error = xfs_log_mount_finish(mp);
	if (error) {
		xfs_warn(mp, "log mount finish failed");
		goto out_rtunmount;
	}

	/*
	 * Now the log is fully replayed, we can transition to full read-only
	 * mode for read-only mounts. This will sync all the metadata and clean
	 * the log so that the recovery we just performed does not have to be
	 * replayed again on the next mount.
	 *
	 * We use the same quiesce mechanism as the rw->ro remount, as they are
	 * semantically identical operations.
	 */
	if ((mp->m_flags & (XFS_MOUNT_RDONLY|XFS_MOUNT_NORECOVERY)) ==
							XFS_MOUNT_RDONLY) {
		xfs_quiesce_attr(mp);
	}

	/*
	 * Complete the quota initialisation, post-log-replay component.
	 */
	if (quotamount) {
		ASSERT(mp->m_qflags == 0);
		mp->m_qflags = quotaflags;

		xfs_qm_mount_quotas(mp);
	}

	/*
	 * Now we are mounted, reserve a small amount of unused space for
	 * privileged transactions. This is needed so that transaction
	 * space required for critical operations can dip into this pool
	 * when at ENOSPC. This is needed for operations like create with
	 * attr, unwritten extent conversion at ENOSPC, etc. Data allocations
	 * are not allowed to use this reserved space.
	 *
	 * This may drive us straight to ENOSPC on mount, but that implies
	 * we were already there on the last unmount. Warn if this occurs.
	 */
	if (!(mp->m_flags & XFS_MOUNT_RDONLY)) {
		resblks = xfs_default_resblks(mp);
		error = xfs_reserve_blocks(mp, &resblks, NULL);
		if (error)
			xfs_warn(mp,
	"Unable to allocate reserve blocks. Continuing without reserve pool.");

		/* Recover any CoW blocks that never got remapped. */
		error = xfs_reflink_recover_cow(mp);
		if (error) {
			xfs_err(mp,
	"Error %d recovering leftover CoW allocations.", error);
			xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
			goto out_quota;
		}

		/* Reserve AG blocks for future btree expansion. */
		error = xfs_fs_reserve_ag_blocks(mp);
		if (error && error != -ENOSPC)
			goto out_agresv;
	}

	return 0;

 out_agresv:
	xfs_fs_unreserve_ag_blocks(mp);
 out_quota:
	xfs_qm_unmount_quotas(mp);
 out_rtunmount:
	xfs_rtunmount_inodes(mp);
 out_rele_rip:
	xfs_irele(rip);
	/* Clean out dquots that might be in memory after quotacheck. */
	xfs_qm_unmount(mp);
	/*
	 * Cancel all delayed reclaim work and reclaim the inodes directly.
	 * We have to do this /after/ rtunmount and qm_unmount because those
	 * two will have scheduled delayed reclaim for the rt/quota inodes.
	 *
	 * This is slightly different from the unmountfs call sequence
	 * because we could be tearing down a partially set up mount.  In
	 * particular, if log_mount_finish fails we bail out without calling
	 * qm_unmount_quotas and therefore rely on qm_unmount to release the
	 * quota inodes.
	 */
	cancel_delayed_work_sync(&mp->m_reclaim_work);
	xfs_reclaim_inodes(mp, SYNC_WAIT);
	xfs_health_unmount(mp);
 out_log_dealloc:
	mp->m_flags |= XFS_MOUNT_UNMOUNTING;
	xfs_log_mount_cancel(mp);
 out_fail_wait:
	if (mp->m_logdev_targp && mp->m_logdev_targp != mp->m_ddev_targp)
		xfs_wait_buftarg(mp->m_logdev_targp);
	xfs_wait_buftarg(mp->m_ddev_targp);
 out_free_perag:
	xfs_free_perag(mp);
 out_free_dir:
	xfs_da_unmount(mp);
 out_remove_uuid:
	xfs_uuid_unmount(mp);
 out_remove_errortag:
	xfs_errortag_del(mp);
 out_remove_error_sysfs:
	xfs_error_sysfs_del(mp);
 out_del_stats:
	xfs_sysfs_del(&mp->m_stats.xs_kobj);
 out_remove_sysfs:
	xfs_sysfs_del(&mp->m_kobj);
 out:
	return error;
}