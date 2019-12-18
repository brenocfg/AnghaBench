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
struct super_block {int s_quota_types; int s_time_gran; int /*<<< orphan*/ * s_fs_info; int /*<<< orphan*/ * s_root; scalar_t__ s_blocksize_bits; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/ * s_qcop; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_flags; } ;
struct TYPE_7__ {int ls_jid; } ;
struct gfs2_args {int ar_statfs_quantum; scalar_t__ ar_spectator; int /*<<< orphan*/  ar_quota_quantum; int /*<<< orphan*/  ar_commit; scalar_t__ ar_nobarrier; scalar_t__ ar_posix_acl; } ;
struct TYPE_6__ {int gt_statfs_slow; int gt_statfs_quantum; int /*<<< orphan*/  gt_quota_quantum; int /*<<< orphan*/  gt_logd_secs; } ;
struct TYPE_5__ {scalar_t__ sb_bsize_shift; int /*<<< orphan*/  sb_bsize; } ;
struct gfs2_sbd {char* sd_table_name; int /*<<< orphan*/  sd_journal_ready; int /*<<< orphan*/ * sd_master_dir; int /*<<< orphan*/ * sd_root_dir; TYPE_3__ sd_lockstruct; int /*<<< orphan*/  sd_fsname; struct gfs2_args sd_args; TYPE_2__ sd_tune; scalar_t__ sd_fsb2bb_shift; int /*<<< orphan*/  sd_fsb2bb; TYPE_1__ sd_sb; int /*<<< orphan*/  sd_flags; } ;
struct gfs2_holder {int dummy; } ;
struct fs_context {int sb_flags; struct gfs2_args* fs_private; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 int /*<<< orphan*/  DO ; 
 int /*<<< orphan*/  DQUOT_QUOTA_SYS_FILE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFS2_BASIC_BLOCK ; 
 scalar_t__ GFS2_BASIC_BLOCK_SHIFT ; 
 int /*<<< orphan*/  GFS2_MAGIC ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int QTYPE_MASK_GRP ; 
 int QTYPE_MASK_USR ; 
 int /*<<< orphan*/  SB_NOSEC ; 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int SB_SILENT ; 
 int /*<<< orphan*/  SDF_NOBARRIERS ; 
 int /*<<< orphan*/  SDF_RORECOVERY ; 
 int /*<<< orphan*/  UNDO ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sbd (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_create_debugfs_file (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_delete_debugfs_file (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_dops ; 
 int /*<<< orphan*/  gfs2_export_ops ; 
 int /*<<< orphan*/  gfs2_gl_hash_clear (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_lm_mount (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_lm_unmount (struct gfs2_sbd*) ; 
 int gfs2_make_fs_rw (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_online_uevent (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_quotactl_ops ; 
 int gfs2_statfs_init (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_super_ops ; 
 int gfs2_sys_fs_add (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_sys_fs_del (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_xattr_handlers ; 
 int init_inodes (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int init_locking (struct gfs2_sbd*,struct gfs2_holder*,int /*<<< orphan*/ ) ; 
 int init_names (struct gfs2_sbd*,int) ; 
 int init_per_node (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int init_sb (struct gfs2_sbd*,int) ; 
 struct gfs2_sbd* init_sbd (struct super_block*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_4__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  sb_min_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 
 int wait_on_journal (struct gfs2_sbd*) ; 

__attribute__((used)) static int gfs2_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct gfs2_args *args = fc->fs_private;
	int silent = fc->sb_flags & SB_SILENT;
	struct gfs2_sbd *sdp;
	struct gfs2_holder mount_gh;
	int error;

	sdp = init_sbd(sb);
	if (!sdp) {
		pr_warn("can't alloc struct gfs2_sbd\n");
		return -ENOMEM;
	}
	sdp->sd_args = *args;

	if (sdp->sd_args.ar_spectator) {
                sb->s_flags |= SB_RDONLY;
		set_bit(SDF_RORECOVERY, &sdp->sd_flags);
	}
	if (sdp->sd_args.ar_posix_acl)
		sb->s_flags |= SB_POSIXACL;
	if (sdp->sd_args.ar_nobarrier)
		set_bit(SDF_NOBARRIERS, &sdp->sd_flags);

	sb->s_flags |= SB_NOSEC;
	sb->s_magic = GFS2_MAGIC;
	sb->s_op = &gfs2_super_ops;
	sb->s_d_op = &gfs2_dops;
	sb->s_export_op = &gfs2_export_ops;
	sb->s_xattr = gfs2_xattr_handlers;
	sb->s_qcop = &gfs2_quotactl_ops;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
	sb_dqopt(sb)->flags |= DQUOT_QUOTA_SYS_FILE;
	sb->s_time_gran = 1;
	sb->s_maxbytes = MAX_LFS_FILESIZE;

	/* Set up the buffer cache and fill in some fake block size values
	   to allow us to read-in the on-disk superblock. */
	sdp->sd_sb.sb_bsize = sb_min_blocksize(sb, GFS2_BASIC_BLOCK);
	sdp->sd_sb.sb_bsize_shift = sb->s_blocksize_bits;
	sdp->sd_fsb2bb_shift = sdp->sd_sb.sb_bsize_shift -
                               GFS2_BASIC_BLOCK_SHIFT;
	sdp->sd_fsb2bb = BIT(sdp->sd_fsb2bb_shift);

	sdp->sd_tune.gt_logd_secs = sdp->sd_args.ar_commit;
	sdp->sd_tune.gt_quota_quantum = sdp->sd_args.ar_quota_quantum;
	if (sdp->sd_args.ar_statfs_quantum) {
		sdp->sd_tune.gt_statfs_slow = 0;
		sdp->sd_tune.gt_statfs_quantum = sdp->sd_args.ar_statfs_quantum;
	} else {
		sdp->sd_tune.gt_statfs_slow = 1;
		sdp->sd_tune.gt_statfs_quantum = 30;
	}

	error = init_names(sdp, silent);
	if (error) {
		/* In this case, we haven't initialized sysfs, so we have to
		   manually free the sdp. */
		free_sbd(sdp);
		sb->s_fs_info = NULL;
		return error;
	}

	snprintf(sdp->sd_fsname, sizeof(sdp->sd_fsname), "%s", sdp->sd_table_name);

	error = gfs2_sys_fs_add(sdp);
	/*
	 * If we hit an error here, gfs2_sys_fs_add will have called function
	 * kobject_put which causes the sysfs usage count to go to zero, which
	 * causes sysfs to call function gfs2_sbd_release, which frees sdp.
	 * Subsequent error paths here will call gfs2_sys_fs_del, which also
	 * kobject_put to free sdp.
	 */
	if (error)
		return error;

	gfs2_create_debugfs_file(sdp);

	error = gfs2_lm_mount(sdp, silent);
	if (error)
		goto fail_debug;

	error = init_locking(sdp, &mount_gh, DO);
	if (error)
		goto fail_lm;

	error = init_sb(sdp, silent);
	if (error)
		goto fail_locking;

	error = wait_on_journal(sdp);
	if (error)
		goto fail_sb;

	/*
	 * If user space has failed to join the cluster or some similar
	 * failure has occurred, then the journal id will contain a
	 * negative (error) number. This will then be returned to the
	 * caller (of the mount syscall). We do this even for spectator
	 * mounts (which just write a jid of 0 to indicate "ok" even though
	 * the jid is unused in the spectator case)
	 */
	if (sdp->sd_lockstruct.ls_jid < 0) {
		error = sdp->sd_lockstruct.ls_jid;
		sdp->sd_lockstruct.ls_jid = 0;
		goto fail_sb;
	}

	if (sdp->sd_args.ar_spectator)
		snprintf(sdp->sd_fsname, sizeof(sdp->sd_fsname), "%s.s",
			 sdp->sd_table_name);
	else
		snprintf(sdp->sd_fsname, sizeof(sdp->sd_fsname), "%s.%u",
			 sdp->sd_table_name, sdp->sd_lockstruct.ls_jid);

	error = init_inodes(sdp, DO);
	if (error)
		goto fail_sb;

	error = init_per_node(sdp, DO);
	if (error)
		goto fail_inodes;

	error = gfs2_statfs_init(sdp);
	if (error) {
		fs_err(sdp, "can't initialize statfs subsystem: %d\n", error);
		goto fail_per_node;
	}

	if (!sb_rdonly(sb)) {
		error = gfs2_make_fs_rw(sdp);
		if (error) {
			fs_err(sdp, "can't make FS RW: %d\n", error);
			goto fail_per_node;
		}
	}

	gfs2_glock_dq_uninit(&mount_gh);
	gfs2_online_uevent(sdp);
	return 0;

fail_per_node:
	init_per_node(sdp, UNDO);
fail_inodes:
	init_inodes(sdp, UNDO);
fail_sb:
	if (sdp->sd_root_dir)
		dput(sdp->sd_root_dir);
	if (sdp->sd_master_dir)
		dput(sdp->sd_master_dir);
	if (sb->s_root)
		dput(sb->s_root);
	sb->s_root = NULL;
fail_locking:
	init_locking(sdp, &mount_gh, UNDO);
fail_lm:
	complete_all(&sdp->sd_journal_ready);
	gfs2_gl_hash_clear(sdp);
	gfs2_lm_unmount(sdp);
fail_debug:
	gfs2_delete_debugfs_file(sdp);
	/* gfs2_sys_fs_del must be the last thing we do, since it causes
	 * sysfs to call function gfs2_sbd_release, which frees sdp. */
	gfs2_sys_fs_del(sdp);
	sb->s_fs_info = NULL;
	return error;
}