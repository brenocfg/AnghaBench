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
struct super_block {int s_flags; } ;
struct seq_file {int dummy; } ;
struct mount_opts {scalar_t__ token; int flags; int mount_opt; } ;
struct ext4_super_block {int /*<<< orphan*/  s_errors; int /*<<< orphan*/  s_def_resgid; int /*<<< orphan*/  s_def_resuid; } ;
struct ext4_sb_info {int s_def_mount_opt; int s_sb_block; int s_mount_opt; int s_commit_interval; int s_min_batch_time; int s_max_batch_time; int s_stripe; int s_inode_readahead_blks; int s_li_wait_mult; int s_max_dir_size_kb; int /*<<< orphan*/  s_resgid; int /*<<< orphan*/  s_resuid; struct ext4_super_block* s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_ERR_ABORT ; 
 int /*<<< orphan*/  DATA_FLAGS ; 
 scalar_t__ DUMMY_ENCRYPTION_ENABLED (struct ext4_sb_info*) ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 int EXT4_DEF_INODE_READAHEAD_BLKS ; 
 int EXT4_DEF_LI_WAIT_MULT ; 
 int EXT4_DEF_MAX_BATCH_TIME ; 
 int EXT4_DEF_MIN_BATCH_TIME ; 
 int EXT4_DEF_RESGID ; 
 int EXT4_DEF_RESUID ; 
 int EXT4_ERRORS_CONTINUE ; 
 int EXT4_ERRORS_PANIC ; 
 int EXT4_ERRORS_RO ; 
 int EXT4_MOUNT_DATA_FLAGS ; 
 scalar_t__ EXT4_MOUNT_JOURNAL_DATA ; 
 scalar_t__ EXT4_MOUNT_ORDERED_DATA ; 
 scalar_t__ EXT4_MOUNT_WRITEBACK_DATA ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_INODE_TABLE ; 
 int JBD2_DEFAULT_MAX_COMMIT_AGE ; 
 int MOPT_CLEAR ; 
 int MOPT_CLEAR_ERR ; 
 int MOPT_SET ; 
 scalar_t__ Opt_err ; 
 int SB_I_VERSION ; 
 int /*<<< orphan*/  SEQ_OPTS_PRINT (char*,int) ; 
 int /*<<< orphan*/  SEQ_OPTS_PUTS (char*) ; 
 struct mount_opts* ext4_mount_opts ; 
 int /*<<< orphan*/  ext4_show_quota_options (struct seq_file*,struct super_block*) ; 
 int from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int token2str (scalar_t__) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ext4_show_options(struct seq_file *seq, struct super_block *sb,
			      int nodefs)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	int def_errors, def_mount_opt = sbi->s_def_mount_opt;
	const struct mount_opts *m;
	char sep = nodefs ? '\n' : ',';

#define SEQ_OPTS_PUTS(str) seq_printf(seq, "%c" str, sep)
#define SEQ_OPTS_PRINT(str, arg) seq_printf(seq, "%c" str, sep, arg)

	if (sbi->s_sb_block != 1)
		SEQ_OPTS_PRINT("sb=%llu", sbi->s_sb_block);

	for (m = ext4_mount_opts; m->token != Opt_err; m++) {
		int want_set = m->flags & MOPT_SET;
		if (((m->flags & (MOPT_SET|MOPT_CLEAR)) == 0) ||
		    (m->flags & MOPT_CLEAR_ERR))
			continue;
		if (!nodefs && !(m->mount_opt & (sbi->s_mount_opt ^ def_mount_opt)))
			continue; /* skip if same as the default */
		if ((want_set &&
		     (sbi->s_mount_opt & m->mount_opt) != m->mount_opt) ||
		    (!want_set && (sbi->s_mount_opt & m->mount_opt)))
			continue; /* select Opt_noFoo vs Opt_Foo */
		SEQ_OPTS_PRINT("%s", token2str(m->token));
	}

	if (nodefs || !uid_eq(sbi->s_resuid, make_kuid(&init_user_ns, EXT4_DEF_RESUID)) ||
	    le16_to_cpu(es->s_def_resuid) != EXT4_DEF_RESUID)
		SEQ_OPTS_PRINT("resuid=%u",
				from_kuid_munged(&init_user_ns, sbi->s_resuid));
	if (nodefs || !gid_eq(sbi->s_resgid, make_kgid(&init_user_ns, EXT4_DEF_RESGID)) ||
	    le16_to_cpu(es->s_def_resgid) != EXT4_DEF_RESGID)
		SEQ_OPTS_PRINT("resgid=%u",
				from_kgid_munged(&init_user_ns, sbi->s_resgid));
	def_errors = nodefs ? -1 : le16_to_cpu(es->s_errors);
	if (test_opt(sb, ERRORS_RO) && def_errors != EXT4_ERRORS_RO)
		SEQ_OPTS_PUTS("errors=remount-ro");
	if (test_opt(sb, ERRORS_CONT) && def_errors != EXT4_ERRORS_CONTINUE)
		SEQ_OPTS_PUTS("errors=continue");
	if (test_opt(sb, ERRORS_PANIC) && def_errors != EXT4_ERRORS_PANIC)
		SEQ_OPTS_PUTS("errors=panic");
	if (nodefs || sbi->s_commit_interval != JBD2_DEFAULT_MAX_COMMIT_AGE*HZ)
		SEQ_OPTS_PRINT("commit=%lu", sbi->s_commit_interval / HZ);
	if (nodefs || sbi->s_min_batch_time != EXT4_DEF_MIN_BATCH_TIME)
		SEQ_OPTS_PRINT("min_batch_time=%u", sbi->s_min_batch_time);
	if (nodefs || sbi->s_max_batch_time != EXT4_DEF_MAX_BATCH_TIME)
		SEQ_OPTS_PRINT("max_batch_time=%u", sbi->s_max_batch_time);
	if (sb->s_flags & SB_I_VERSION)
		SEQ_OPTS_PUTS("i_version");
	if (nodefs || sbi->s_stripe)
		SEQ_OPTS_PRINT("stripe=%lu", sbi->s_stripe);
	if (nodefs || EXT4_MOUNT_DATA_FLAGS &
			(sbi->s_mount_opt ^ def_mount_opt)) {
		if (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA)
			SEQ_OPTS_PUTS("data=journal");
		else if (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA)
			SEQ_OPTS_PUTS("data=ordered");
		else if (test_opt(sb, DATA_FLAGS) == EXT4_MOUNT_WRITEBACK_DATA)
			SEQ_OPTS_PUTS("data=writeback");
	}
	if (nodefs ||
	    sbi->s_inode_readahead_blks != EXT4_DEF_INODE_READAHEAD_BLKS)
		SEQ_OPTS_PRINT("inode_readahead_blks=%u",
			       sbi->s_inode_readahead_blks);

	if (test_opt(sb, INIT_INODE_TABLE) && (nodefs ||
		       (sbi->s_li_wait_mult != EXT4_DEF_LI_WAIT_MULT)))
		SEQ_OPTS_PRINT("init_itable=%u", sbi->s_li_wait_mult);
	if (nodefs || sbi->s_max_dir_size_kb)
		SEQ_OPTS_PRINT("max_dir_size_kb=%u", sbi->s_max_dir_size_kb);
	if (test_opt(sb, DATA_ERR_ABORT))
		SEQ_OPTS_PUTS("data_err=abort");
	if (DUMMY_ENCRYPTION_ENABLED(sbi))
		SEQ_OPTS_PUTS("test_dummy_encryption");

	ext4_show_quota_options(seq, sb);
	return 0;
}