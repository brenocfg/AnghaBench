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
struct TYPE_6__ {scalar_t__ from; } ;
typedef  TYPE_1__ substring_t ;
struct super_block {int /*<<< orphan*/  s_flags; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct mount_opts {int token; int flags; int mount_opt; } ;
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; } ;
struct ext4_sb_info {int s_commit_interval; int s_want_extra_isize; int s_max_batch_time; int s_min_batch_time; int s_inode_readahead_blks; int s_li_wait_mult; int s_max_dir_size_kb; int s_stripe; int s_mount_opt; int s_jquota_fmt; int /*<<< orphan*/  s_journal; int /*<<< orphan*/  s_mount_flags; int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_FLAGS ; 
 int /*<<< orphan*/  ERRORS_MASK ; 
 int /*<<< orphan*/  EXPLICIT_DELALLOC ; 
 int /*<<< orphan*/  EXPLICIT_JOURNAL_CHECKSUM ; 
 int EXT4_DEF_LI_WAIT_MULT ; 
 int /*<<< orphan*/  EXT4_MF_FS_ABORTED ; 
 int /*<<< orphan*/  EXT4_MF_TEST_DUMMY_ENCRYPTION ; 
 int EXT4_MOUNT_DELALLOC ; 
 int EXT4_MOUNT_JOURNAL_CHECKSUM ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GRPQUOTA ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_INODE_TABLE ; 
 int INT_MAX ; 
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 unsigned int IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_EXT2_SB (struct super_block*) ; 
 scalar_t__ IS_EXT3_SB (struct super_block*) ; 
 int JBD2_DEFAULT_MAX_COMMIT_AGE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int MOPT_CLEAR ; 
 int MOPT_CLEAR_ERR ; 
 int MOPT_DATAJ ; 
 int MOPT_EXPLICIT ; 
 int MOPT_GTE0 ; 
 int MOPT_NOSUPPORT ; 
 int MOPT_NO_EXT2 ; 
 int MOPT_NO_EXT3 ; 
 int MOPT_QFMT ; 
 int MOPT_SET ; 
 int MOPT_STRING ; 
#define  Opt_abort 135 
 int Opt_commit ; 
 int Opt_data_err_abort ; 
 int Opt_data_err_ignore ; 
 int Opt_dax ; 
 int Opt_debug_want_extra_isize ; 
 int Opt_err ; 
 int Opt_grpjquota ; 
#define  Opt_i_version 134 
 int Opt_init_itable ; 
 int Opt_inode_readahead_blks ; 
 int Opt_journal_dev ; 
 int Opt_journal_ioprio ; 
 int Opt_journal_path ; 
#define  Opt_lazytime 133 
 int Opt_max_batch_time ; 
 int Opt_max_dir_size_kb ; 
 int Opt_min_batch_time ; 
#define  Opt_noacl 132 
#define  Opt_nolazytime 131 
 int Opt_noquota ; 
#define  Opt_nouser_xattr 130 
 int Opt_offgrpjquota ; 
 int Opt_offusrjquota ; 
#define  Opt_removed 129 
 int Opt_resgid ; 
 int Opt_resuid ; 
#define  Opt_sb 128 
 int Opt_stripe ; 
 int Opt_test_dummy_encryption ; 
 int Opt_usrjquota ; 
 int /*<<< orphan*/  SB_I_VERSION ; 
 int /*<<< orphan*/  SB_LAZYTIME ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USRQUOTA ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int clear_qf_name (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_user_ns () ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deprecated_msg ; 
 scalar_t__ ext4_has_feature_quota (struct super_block*) ; 
 struct mount_opts* ext4_mount_opts ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ match_int (TYPE_1__*,int*) ; 
 char* match_strdup (TYPE_1__*) ; 
 unsigned long new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 scalar_t__ sb_any_quota_loaded (struct super_block*) ; 
 int /*<<< orphan*/  set_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_opt2 (struct super_block*,int /*<<< orphan*/ ) ; 
 int set_qf_name (struct super_block*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int handle_mount_opt(struct super_block *sb, char *opt, int token,
			    substring_t *args, unsigned long *journal_devnum,
			    unsigned int *journal_ioprio, int is_remount)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	const struct mount_opts *m;
	kuid_t uid;
	kgid_t gid;
	int arg = 0;

#ifdef CONFIG_QUOTA
	if (token == Opt_usrjquota)
		return set_qf_name(sb, USRQUOTA, &args[0]);
	else if (token == Opt_grpjquota)
		return set_qf_name(sb, GRPQUOTA, &args[0]);
	else if (token == Opt_offusrjquota)
		return clear_qf_name(sb, USRQUOTA);
	else if (token == Opt_offgrpjquota)
		return clear_qf_name(sb, GRPQUOTA);
#endif
	switch (token) {
	case Opt_noacl:
	case Opt_nouser_xattr:
		ext4_msg(sb, KERN_WARNING, deprecated_msg, opt, "3.5");
		break;
	case Opt_sb:
		return 1;	/* handled by get_sb_block() */
	case Opt_removed:
		ext4_msg(sb, KERN_WARNING, "Ignoring removed %s option", opt);
		return 1;
	case Opt_abort:
		sbi->s_mount_flags |= EXT4_MF_FS_ABORTED;
		return 1;
	case Opt_i_version:
		sb->s_flags |= SB_I_VERSION;
		return 1;
	case Opt_lazytime:
		sb->s_flags |= SB_LAZYTIME;
		return 1;
	case Opt_nolazytime:
		sb->s_flags &= ~SB_LAZYTIME;
		return 1;
	}

	for (m = ext4_mount_opts; m->token != Opt_err; m++)
		if (token == m->token)
			break;

	if (m->token == Opt_err) {
		ext4_msg(sb, KERN_ERR, "Unrecognized mount option \"%s\" "
			 "or missing value", opt);
		return -1;
	}

	if ((m->flags & MOPT_NO_EXT2) && IS_EXT2_SB(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "Mount option \"%s\" incompatible with ext2", opt);
		return -1;
	}
	if ((m->flags & MOPT_NO_EXT3) && IS_EXT3_SB(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "Mount option \"%s\" incompatible with ext3", opt);
		return -1;
	}

	if (args->from && !(m->flags & MOPT_STRING) && match_int(args, &arg))
		return -1;
	if (args->from && (m->flags & MOPT_GTE0) && (arg < 0))
		return -1;
	if (m->flags & MOPT_EXPLICIT) {
		if (m->mount_opt & EXT4_MOUNT_DELALLOC) {
			set_opt2(sb, EXPLICIT_DELALLOC);
		} else if (m->mount_opt & EXT4_MOUNT_JOURNAL_CHECKSUM) {
			set_opt2(sb, EXPLICIT_JOURNAL_CHECKSUM);
		} else
			return -1;
	}
	if (m->flags & MOPT_CLEAR_ERR)
		clear_opt(sb, ERRORS_MASK);
	if (token == Opt_noquota && sb_any_quota_loaded(sb)) {
		ext4_msg(sb, KERN_ERR, "Cannot change quota "
			 "options when quota turned on");
		return -1;
	}

	if (m->flags & MOPT_NOSUPPORT) {
		ext4_msg(sb, KERN_ERR, "%s option not supported", opt);
	} else if (token == Opt_commit) {
		if (arg == 0)
			arg = JBD2_DEFAULT_MAX_COMMIT_AGE;
		else if (arg > INT_MAX / HZ) {
			ext4_msg(sb, KERN_ERR,
				 "Invalid commit interval %d, "
				 "must be smaller than %d",
				 arg, INT_MAX / HZ);
			return -1;
		}
		sbi->s_commit_interval = HZ * arg;
	} else if (token == Opt_debug_want_extra_isize) {
		sbi->s_want_extra_isize = arg;
	} else if (token == Opt_max_batch_time) {
		sbi->s_max_batch_time = arg;
	} else if (token == Opt_min_batch_time) {
		sbi->s_min_batch_time = arg;
	} else if (token == Opt_inode_readahead_blks) {
		if (arg && (arg > (1 << 30) || !is_power_of_2(arg))) {
			ext4_msg(sb, KERN_ERR,
				 "EXT4-fs: inode_readahead_blks must be "
				 "0 or a power of 2 smaller than 2^31");
			return -1;
		}
		sbi->s_inode_readahead_blks = arg;
	} else if (token == Opt_init_itable) {
		set_opt(sb, INIT_INODE_TABLE);
		if (!args->from)
			arg = EXT4_DEF_LI_WAIT_MULT;
		sbi->s_li_wait_mult = arg;
	} else if (token == Opt_max_dir_size_kb) {
		sbi->s_max_dir_size_kb = arg;
	} else if (token == Opt_stripe) {
		sbi->s_stripe = arg;
	} else if (token == Opt_resuid) {
		uid = make_kuid(current_user_ns(), arg);
		if (!uid_valid(uid)) {
			ext4_msg(sb, KERN_ERR, "Invalid uid value %d", arg);
			return -1;
		}
		sbi->s_resuid = uid;
	} else if (token == Opt_resgid) {
		gid = make_kgid(current_user_ns(), arg);
		if (!gid_valid(gid)) {
			ext4_msg(sb, KERN_ERR, "Invalid gid value %d", arg);
			return -1;
		}
		sbi->s_resgid = gid;
	} else if (token == Opt_journal_dev) {
		if (is_remount) {
			ext4_msg(sb, KERN_ERR,
				 "Cannot specify journal on remount");
			return -1;
		}
		*journal_devnum = arg;
	} else if (token == Opt_journal_path) {
		char *journal_path;
		struct inode *journal_inode;
		struct path path;
		int error;

		if (is_remount) {
			ext4_msg(sb, KERN_ERR,
				 "Cannot specify journal on remount");
			return -1;
		}
		journal_path = match_strdup(&args[0]);
		if (!journal_path) {
			ext4_msg(sb, KERN_ERR, "error: could not dup "
				"journal device string");
			return -1;
		}

		error = kern_path(journal_path, LOOKUP_FOLLOW, &path);
		if (error) {
			ext4_msg(sb, KERN_ERR, "error: could not find "
				"journal device path: error %d", error);
			kfree(journal_path);
			return -1;
		}

		journal_inode = d_inode(path.dentry);
		if (!S_ISBLK(journal_inode->i_mode)) {
			ext4_msg(sb, KERN_ERR, "error: journal path %s "
				"is not a block device", journal_path);
			path_put(&path);
			kfree(journal_path);
			return -1;
		}

		*journal_devnum = new_encode_dev(journal_inode->i_rdev);
		path_put(&path);
		kfree(journal_path);
	} else if (token == Opt_journal_ioprio) {
		if (arg > 7) {
			ext4_msg(sb, KERN_ERR, "Invalid journal IO priority"
				 " (must be 0-7)");
			return -1;
		}
		*journal_ioprio =
			IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, arg);
	} else if (token == Opt_test_dummy_encryption) {
#ifdef CONFIG_FS_ENCRYPTION
		sbi->s_mount_flags |= EXT4_MF_TEST_DUMMY_ENCRYPTION;
		ext4_msg(sb, KERN_WARNING,
			 "Test dummy encryption mode enabled");
#else
		ext4_msg(sb, KERN_WARNING,
			 "Test dummy encryption mount option ignored");
#endif
	} else if (m->flags & MOPT_DATAJ) {
		if (is_remount) {
			if (!sbi->s_journal)
				ext4_msg(sb, KERN_WARNING, "Remounting file system with no journal so ignoring journalled data option");
			else if (test_opt(sb, DATA_FLAGS) != m->mount_opt) {
				ext4_msg(sb, KERN_ERR,
					 "Cannot change data mode on remount");
				return -1;
			}
		} else {
			clear_opt(sb, DATA_FLAGS);
			sbi->s_mount_opt |= m->mount_opt;
		}
#ifdef CONFIG_QUOTA
	} else if (m->flags & MOPT_QFMT) {
		if (sb_any_quota_loaded(sb) &&
		    sbi->s_jquota_fmt != m->mount_opt) {
			ext4_msg(sb, KERN_ERR, "Cannot change journaled "
				 "quota options when quota turned on");
			return -1;
		}
		if (ext4_has_feature_quota(sb)) {
			ext4_msg(sb, KERN_INFO,
				 "Quota format mount options ignored "
				 "when QUOTA feature is enabled");
			return 1;
		}
		sbi->s_jquota_fmt = m->mount_opt;
#endif
	} else if (token == Opt_dax) {
#ifdef CONFIG_FS_DAX
		ext4_msg(sb, KERN_WARNING,
		"DAX enabled. Warning: EXPERIMENTAL, use at your own risk");
		sbi->s_mount_opt |= m->mount_opt;
#else
		ext4_msg(sb, KERN_INFO, "dax option not supported");
		return -1;
#endif
	} else if (token == Opt_data_err_abort) {
		sbi->s_mount_opt |= m->mount_opt;
	} else if (token == Opt_data_err_ignore) {
		sbi->s_mount_opt &= ~m->mount_opt;
	} else {
		if (!args->from)
			arg = 1;
		if (m->flags & MOPT_CLEAR)
			arg = !arg;
		else if (unlikely(!(m->flags & MOPT_SET))) {
			ext4_msg(sb, KERN_WARNING,
				 "buggy handling of option %s", opt);
			WARN_ON(1);
			return -1;
		}
		if (arg != 0)
			sbi->s_mount_opt |= m->mount_opt;
		else
			sbi->s_mount_opt &= ~m->mount_opt;
	}
	return 1;
}