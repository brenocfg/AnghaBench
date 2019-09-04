#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct super_block {int dummy; } ;
struct TYPE_24__ {int nr_clusters; int major_ver; int /*<<< orphan*/ * mftbmp_ino; int /*<<< orphan*/ * upcase; scalar_t__ upcase_len; int /*<<< orphan*/ * attrdef; scalar_t__ attrdef_size; int /*<<< orphan*/ * lcnbmp_ino; int /*<<< orphan*/ * vol_ino; int /*<<< orphan*/ * root_ino; int /*<<< orphan*/ * secure_ino; int /*<<< orphan*/ * extend_ino; int /*<<< orphan*/  minor_ver; struct super_block* sb; int /*<<< orphan*/  vol_flags; int /*<<< orphan*/  mft_ino; } ;
typedef  TYPE_5__ ntfs_volume ;
struct TYPE_25__ {TYPE_4__* attr; } ;
typedef  TYPE_6__ ntfs_attr_search_ctx ;
struct TYPE_26__ {int major_ver; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  flags; } ;
typedef  TYPE_7__ VOLUME_INFORMATION ;
struct TYPE_20__ {int /*<<< orphan*/  lock; } ;
struct TYPE_27__ {int /*<<< orphan*/  mrec_lock; TYPE_1__ runlist; } ;
struct TYPE_21__ {int /*<<< orphan*/  value_length; int /*<<< orphan*/  value_offset; } ;
struct TYPE_22__ {TYPE_2__ resident; } ;
struct TYPE_23__ {int /*<<< orphan*/  length; TYPE_3__ data; scalar_t__ flags; scalar_t__ non_resident; } ;
typedef  int /*<<< orphan*/  MFT_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  AT_BITMAP ; 
 int /*<<< orphan*/  AT_VOLUME_INFORMATION ; 
 int /*<<< orphan*/  FILE_Bitmap ; 
 int /*<<< orphan*/  FILE_Extend ; 
 int /*<<< orphan*/  FILE_Secure ; 
 int /*<<< orphan*/  FILE_Volume ; 
 int /*<<< orphan*/  FILE_root ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NInoSetSparseDisabled (TYPE_8__*) ; 
 TYPE_8__* NTFS_I (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVolClearSparseEnabled (TYPE_5__*) ; 
 scalar_t__ NVolSparseEnabled (TYPE_5__*) ; 
 int /*<<< orphan*/ * default_upcase ; 
 int i_size_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 scalar_t__ is_bad_inode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lcnbmp_mrec_lock_key ; 
 int /*<<< orphan*/  lcnbmp_runlist_lock_key ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_and_init_upcase (TYPE_5__*) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_mft_record (TYPE_8__*) ; 
 int /*<<< orphan*/  mftbmp_mrec_lock_key ; 
 int /*<<< orphan*/  mftbmp_runlist_lock_key ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_6__* ntfs_attr_get_search_ctx (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ntfs_attr_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ntfs_attr_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ntfs_attr_put_search_ctx (TYPE_6__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*) ; 
 int /*<<< orphan*/  ntfs_error (struct super_block*,char*) ; 
 int /*<<< orphan*/  ntfs_free (int /*<<< orphan*/ *) ; 
 void* ntfs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_lock ; 
 int /*<<< orphan*/  ntfs_nr_upcase_users ; 
 int /*<<< orphan*/  ntfs_warning (struct super_block*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unmap_mft_record (TYPE_8__*) ; 

__attribute__((used)) static bool load_system_files(ntfs_volume *vol)
{
	struct super_block *sb = vol->sb;
	MFT_RECORD *m;
	VOLUME_INFORMATION *vi;
	ntfs_attr_search_ctx *ctx;
#ifdef NTFS_RW
	RESTART_PAGE_HEADER *rp;
	int err;
#endif /* NTFS_RW */

	ntfs_debug("Entering.");
#ifdef NTFS_RW
	/* Get mft mirror inode compare the contents of $MFT and $MFTMirr. */
	if (!load_and_init_mft_mirror(vol) || !check_mft_mirror(vol)) {
		static const char *es1 = "Failed to load $MFTMirr";
		static const char *es2 = "$MFTMirr does not match $MFT";
		static const char *es3 = ".  Run ntfsfix and/or chkdsk.";

		/* If a read-write mount, convert it to a read-only mount. */
		if (!sb_rdonly(sb)) {
			if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) {
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						!vol->mftmirr_ino ? es1 : es2,
						es3);
				goto iput_mirr_err_out;
			}
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s",
					!vol->mftmirr_ino ? es1 : es2, es3);
		} else
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s",
					!vol->mftmirr_ino ? es1 : es2, es3);
		/* This will prevent a read-write remount. */
		NVolSetErrors(vol);
	}
#endif /* NTFS_RW */
	/* Get mft bitmap attribute inode. */
	vol->mftbmp_ino = ntfs_attr_iget(vol->mft_ino, AT_BITMAP, NULL, 0);
	if (IS_ERR(vol->mftbmp_ino)) {
		ntfs_error(sb, "Failed to load $MFT/$BITMAP attribute.");
		goto iput_mirr_err_out;
	}
	lockdep_set_class(&NTFS_I(vol->mftbmp_ino)->runlist.lock,
			   &mftbmp_runlist_lock_key);
	lockdep_set_class(&NTFS_I(vol->mftbmp_ino)->mrec_lock,
			   &mftbmp_mrec_lock_key);
	/* Read upcase table and setup @vol->upcase and @vol->upcase_len. */
	if (!load_and_init_upcase(vol))
		goto iput_mftbmp_err_out;
#ifdef NTFS_RW
	/*
	 * Read attribute definitions table and setup @vol->attrdef and
	 * @vol->attrdef_size.
	 */
	if (!load_and_init_attrdef(vol))
		goto iput_upcase_err_out;
#endif /* NTFS_RW */
	/*
	 * Get the cluster allocation bitmap inode and verify the size, no
	 * need for any locking at this stage as we are already running
	 * exclusively as we are mount in progress task.
	 */
	vol->lcnbmp_ino = ntfs_iget(sb, FILE_Bitmap);
	if (IS_ERR(vol->lcnbmp_ino) || is_bad_inode(vol->lcnbmp_ino)) {
		if (!IS_ERR(vol->lcnbmp_ino))
			iput(vol->lcnbmp_ino);
		goto bitmap_failed;
	}
	lockdep_set_class(&NTFS_I(vol->lcnbmp_ino)->runlist.lock,
			   &lcnbmp_runlist_lock_key);
	lockdep_set_class(&NTFS_I(vol->lcnbmp_ino)->mrec_lock,
			   &lcnbmp_mrec_lock_key);

	NInoSetSparseDisabled(NTFS_I(vol->lcnbmp_ino));
	if ((vol->nr_clusters + 7) >> 3 > i_size_read(vol->lcnbmp_ino)) {
		iput(vol->lcnbmp_ino);
bitmap_failed:
		ntfs_error(sb, "Failed to load $Bitmap.");
		goto iput_attrdef_err_out;
	}
	/*
	 * Get the volume inode and setup our cache of the volume flags and
	 * version.
	 */
	vol->vol_ino = ntfs_iget(sb, FILE_Volume);
	if (IS_ERR(vol->vol_ino) || is_bad_inode(vol->vol_ino)) {
		if (!IS_ERR(vol->vol_ino))
			iput(vol->vol_ino);
volume_failed:
		ntfs_error(sb, "Failed to load $Volume.");
		goto iput_lcnbmp_err_out;
	}
	m = map_mft_record(NTFS_I(vol->vol_ino));
	if (IS_ERR(m)) {
iput_volume_failed:
		iput(vol->vol_ino);
		goto volume_failed;
	}
	if (!(ctx = ntfs_attr_get_search_ctx(NTFS_I(vol->vol_ino), m))) {
		ntfs_error(sb, "Failed to get attribute search context.");
		goto get_ctx_vol_failed;
	}
	if (ntfs_attr_lookup(AT_VOLUME_INFORMATION, NULL, 0, 0, 0, NULL, 0,
			ctx) || ctx->attr->non_resident || ctx->attr->flags) {
err_put_vol:
		ntfs_attr_put_search_ctx(ctx);
get_ctx_vol_failed:
		unmap_mft_record(NTFS_I(vol->vol_ino));
		goto iput_volume_failed;
	}
	vi = (VOLUME_INFORMATION*)((char*)ctx->attr +
			le16_to_cpu(ctx->attr->data.resident.value_offset));
	/* Some bounds checks. */
	if ((u8*)vi < (u8*)ctx->attr || (u8*)vi +
			le32_to_cpu(ctx->attr->data.resident.value_length) >
			(u8*)ctx->attr + le32_to_cpu(ctx->attr->length))
		goto err_put_vol;
	/* Copy the volume flags and version to the ntfs_volume structure. */
	vol->vol_flags = vi->flags;
	vol->major_ver = vi->major_ver;
	vol->minor_ver = vi->minor_ver;
	ntfs_attr_put_search_ctx(ctx);
	unmap_mft_record(NTFS_I(vol->vol_ino));
	pr_info("volume version %i.%i.\n", vol->major_ver,
			vol->minor_ver);
	if (vol->major_ver < 3 && NVolSparseEnabled(vol)) {
		ntfs_warning(vol->sb, "Disabling sparse support due to NTFS "
				"volume version %i.%i (need at least version "
				"3.0).", vol->major_ver, vol->minor_ver);
		NVolClearSparseEnabled(vol);
	}
#ifdef NTFS_RW
	/* Make sure that no unsupported volume flags are set. */
	if (vol->vol_flags & VOLUME_MUST_MOUNT_RO_MASK) {
		static const char *es1a = "Volume is dirty";
		static const char *es1b = "Volume has been modified by chkdsk";
		static const char *es1c = "Volume has unsupported flags set";
		static const char *es2a = ".  Run chkdsk and mount in Windows.";
		static const char *es2b = ".  Mount in Windows.";
		const char *es1, *es2;

		es2 = es2a;
		if (vol->vol_flags & VOLUME_IS_DIRTY)
			es1 = es1a;
		else if (vol->vol_flags & VOLUME_MODIFIED_BY_CHKDSK) {
			es1 = es1b;
			es2 = es2b;
		} else {
			es1 = es1c;
			ntfs_warning(sb, "Unsupported volume flags 0x%x "
					"encountered.",
					(unsigned)le16_to_cpu(vol->vol_flags));
		}
		/* If a read-write mount, convert it to a read-only mount. */
		if (!sb_rdonly(sb)) {
			if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) {
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				goto iput_vol_err_out;
			}
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		} else
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/*
		 * Do not set NVolErrors() because ntfs_remount() re-checks the
		 * flags which we need to do in case any flags have changed.
		 */
	}
	/*
	 * Get the inode for the logfile, check it and determine if the volume
	 * was shutdown cleanly.
	 */
	rp = NULL;
	if (!load_and_check_logfile(vol, &rp) ||
			!ntfs_is_logfile_clean(vol->logfile_ino, rp)) {
		static const char *es1a = "Failed to load $LogFile";
		static const char *es1b = "$LogFile is not clean";
		static const char *es2 = ".  Mount in Windows.";
		const char *es1;

		es1 = !vol->logfile_ino ? es1a : es1b;
		/* If a read-write mount, convert it to a read-only mount. */
		if (!sb_rdonly(sb)) {
			if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) {
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				if (vol->logfile_ino) {
					BUG_ON(!rp);
					ntfs_free(rp);
				}
				goto iput_logfile_err_out;
			}
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		} else
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a read-write remount. */
		NVolSetErrors(vol);
	}
	ntfs_free(rp);
#endif /* NTFS_RW */
	/* Get the root directory inode so we can do path lookups. */
	vol->root_ino = ntfs_iget(sb, FILE_root);
	if (IS_ERR(vol->root_ino) || is_bad_inode(vol->root_ino)) {
		if (!IS_ERR(vol->root_ino))
			iput(vol->root_ino);
		ntfs_error(sb, "Failed to load root directory.");
		goto iput_logfile_err_out;
	}
#ifdef NTFS_RW
	/*
	 * Check if Windows is suspended to disk on the target volume.  If it
	 * is hibernated, we must not write *anything* to the disk so set
	 * NVolErrors() without setting the dirty volume flag and mount
	 * read-only.  This will prevent read-write remounting and it will also
	 * prevent all writes.
	 */
	err = check_windows_hibernation_status(vol);
	if (unlikely(err)) {
		static const char *es1a = "Failed to determine if Windows is "
				"hibernated";
		static const char *es1b = "Windows is hibernated";
		static const char *es2 = ".  Run chkdsk.";
		const char *es1;

		es1 = err < 0 ? es1a : es1b;
		/* If a read-write mount, convert it to a read-only mount. */
		if (!sb_rdonly(sb)) {
			if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) {
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				goto iput_root_err_out;
			}
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		} else
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a read-write remount. */
		NVolSetErrors(vol);
	}
	/* If (still) a read-write mount, mark the volume dirty. */
	if (!sb_rdonly(sb) && ntfs_set_volume_flags(vol, VOLUME_IS_DIRTY)) {
		static const char *es1 = "Failed to set dirty bit in volume "
				"information flags";
		static const char *es2 = ".  Run chkdsk.";

		/* Convert to a read-only mount. */
		if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) {
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			goto iput_root_err_out;
		}
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		/*
		 * Do not set NVolErrors() because ntfs_remount() might manage
		 * to set the dirty flag in which case all would be well.
		 */
	}
#if 0
	// TODO: Enable this code once we start modifying anything that is
	//	 different between NTFS 1.2 and 3.x...
	/*
	 * If (still) a read-write mount, set the NT4 compatibility flag on
	 * newer NTFS version volumes.
	 */
	if (!(sb->s_flags & SB_RDONLY) && (vol->major_ver > 1) &&
			ntfs_set_volume_flags(vol, VOLUME_MOUNTED_ON_NT4)) {
		static const char *es1 = "Failed to set NT4 compatibility flag";
		static const char *es2 = ".  Run chkdsk.";

		/* Convert to a read-only mount. */
		if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) {
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			goto iput_root_err_out;
		}
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	}
#endif
	/* If (still) a read-write mount, empty the logfile. */
	if (!sb_rdonly(sb) && !ntfs_empty_logfile(vol->logfile_ino)) {
		static const char *es1 = "Failed to empty $LogFile";
		static const char *es2 = ".  Mount in Windows.";

		/* Convert to a read-only mount. */
		if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) {
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			goto iput_root_err_out;
		}
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	}
#endif /* NTFS_RW */
	/* If on NTFS versions before 3.0, we are done. */
	if (unlikely(vol->major_ver < 3))
		return true;
	/* NTFS 3.0+ specific initialization. */
	/* Get the security descriptors inode. */
	vol->secure_ino = ntfs_iget(sb, FILE_Secure);
	if (IS_ERR(vol->secure_ino) || is_bad_inode(vol->secure_ino)) {
		if (!IS_ERR(vol->secure_ino))
			iput(vol->secure_ino);
		ntfs_error(sb, "Failed to load $Secure.");
		goto iput_root_err_out;
	}
	// TODO: Initialize security.
	/* Get the extended system files' directory inode. */
	vol->extend_ino = ntfs_iget(sb, FILE_Extend);
	if (IS_ERR(vol->extend_ino) || is_bad_inode(vol->extend_ino)) {
		if (!IS_ERR(vol->extend_ino))
			iput(vol->extend_ino);
		ntfs_error(sb, "Failed to load $Extend.");
		goto iput_sec_err_out;
	}
#ifdef NTFS_RW
	/* Find the quota file, load it if present, and set it up. */
	if (!load_and_init_quota(vol)) {
		static const char *es1 = "Failed to load $Quota";
		static const char *es2 = ".  Run chkdsk.";

		/* If a read-write mount, convert it to a read-only mount. */
		if (!sb_rdonly(sb)) {
			if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) {
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				goto iput_quota_err_out;
			}
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		} else
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a read-write remount. */
		NVolSetErrors(vol);
	}
	/* If (still) a read-write mount, mark the quotas out of date. */
	if (!sb_rdonly(sb) && !ntfs_mark_quotas_out_of_date(vol)) {
		static const char *es1 = "Failed to mark quotas out of date";
		static const char *es2 = ".  Run chkdsk.";

		/* Convert to a read-only mount. */
		if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) {
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			goto iput_quota_err_out;
		}
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	}
	/*
	 * Find the transaction log file ($UsnJrnl), load it if present, check
	 * it, and set it up.
	 */
	if (!load_and_init_usnjrnl(vol)) {
		static const char *es1 = "Failed to load $UsnJrnl";
		static const char *es2 = ".  Run chkdsk.";

		/* If a read-write mount, convert it to a read-only mount. */
		if (!sb_rdonly(sb)) {
			if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
					ON_ERRORS_CONTINUE))) {
				ntfs_error(sb, "%s and neither on_errors="
						"continue nor on_errors="
						"remount-ro was specified%s",
						es1, es2);
				goto iput_usnjrnl_err_out;
			}
			sb->s_flags |= SB_RDONLY;
			ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		} else
			ntfs_warning(sb, "%s.  Will not be able to remount "
					"read-write%s", es1, es2);
		/* This will prevent a read-write remount. */
		NVolSetErrors(vol);
	}
	/* If (still) a read-write mount, stamp the transaction log. */
	if (!sb_rdonly(sb) && !ntfs_stamp_usnjrnl(vol)) {
		static const char *es1 = "Failed to stamp transaction log "
				"($UsnJrnl)";
		static const char *es2 = ".  Run chkdsk.";

		/* Convert to a read-only mount. */
		if (!(vol->on_errors & (ON_ERRORS_REMOUNT_RO |
				ON_ERRORS_CONTINUE))) {
			ntfs_error(sb, "%s and neither on_errors=continue nor "
					"on_errors=remount-ro was specified%s",
					es1, es2);
			goto iput_usnjrnl_err_out;
		}
		ntfs_error(sb, "%s.  Mounting read-only%s", es1, es2);
		sb->s_flags |= SB_RDONLY;
		NVolSetErrors(vol);
	}
#endif /* NTFS_RW */
	return true;
#ifdef NTFS_RW
iput_usnjrnl_err_out:
	iput(vol->usnjrnl_j_ino);
	iput(vol->usnjrnl_max_ino);
	iput(vol->usnjrnl_ino);
iput_quota_err_out:
	iput(vol->quota_q_ino);
	iput(vol->quota_ino);
	iput(vol->extend_ino);
#endif /* NTFS_RW */
iput_sec_err_out:
	iput(vol->secure_ino);
iput_root_err_out:
	iput(vol->root_ino);
iput_logfile_err_out:
#ifdef NTFS_RW
	iput(vol->logfile_ino);
iput_vol_err_out:
#endif /* NTFS_RW */
	iput(vol->vol_ino);
iput_lcnbmp_err_out:
	iput(vol->lcnbmp_ino);
iput_attrdef_err_out:
	vol->attrdef_size = 0;
	if (vol->attrdef) {
		ntfs_free(vol->attrdef);
		vol->attrdef = NULL;
	}
#ifdef NTFS_RW
iput_upcase_err_out:
#endif /* NTFS_RW */
	vol->upcase_len = 0;
	mutex_lock(&ntfs_lock);
	if (vol->upcase == default_upcase) {
		ntfs_nr_upcase_users--;
		vol->upcase = NULL;
	}
	mutex_unlock(&ntfs_lock);
	if (vol->upcase) {
		ntfs_free(vol->upcase);
		vol->upcase = NULL;
	}
iput_mftbmp_err_out:
	iput(vol->mftbmp_ino);
iput_mirr_err_out:
#ifdef NTFS_RW
	iput(vol->mftmirr_ino);
#endif /* NTFS_RW */
	return false;
}