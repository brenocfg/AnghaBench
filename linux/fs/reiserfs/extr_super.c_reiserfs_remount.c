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
struct super_block {int s_flags; } ;
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_super_block {int dummy; } ;
struct reiserfs_journal {unsigned int j_max_commit_age; unsigned int j_max_trans_age; unsigned int j_default_max_commit_age; int j_errno; int j_must_wait; } ;
typedef  int /*<<< orphan*/  qf_names ;
struct TYPE_2__ {unsigned long s_mount_opt; char** s_qf_names; scalar_t__ s_mount_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int JOURNAL_MAX_TRANS_AGE ; 
 int REISERFS_ATTRS ; 
 int REISERFS_BARRIER_FLUSH ; 
 int REISERFS_BARRIER_NONE ; 
 int REISERFS_ERROR_CONTINUE ; 
 scalar_t__ REISERFS_ERROR_FS ; 
 int REISERFS_ERROR_PANIC ; 
 int REISERFS_ERROR_RO ; 
 int REISERFS_GRPQUOTA ; 
 int REISERFS_HASHED_RELOCATION ; 
 int REISERFS_LARGETAIL ; 
 int REISERFS_MAXQUOTAS ; 
 int REISERFS_NO_BORDER ; 
 int REISERFS_NO_UNHASHED_RELOCATION ; 
 int REISERFS_POSIXACL ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int REISERFS_SMALLTAIL ; 
 int REISERFS_TEST4 ; 
 int REISERFS_USRQUOTA ; 
 scalar_t__ REISERFS_VALID_FS ; 
 int REISERFS_XATTRS_USER ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_super_block* SB_DISK_SUPER_BLOCK (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  dquot_resume (struct super_block*,int) ; 
 int dquot_suspend (struct super_block*,int) ; 
 int /*<<< orphan*/  finish_unfinished (struct super_block*) ; 
 int /*<<< orphan*/  handle_attrs (struct super_block*) ; 
 int /*<<< orphan*/  handle_barrier_mode (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  handle_data_mode (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  handle_quota_files (struct super_block*,char**,unsigned int*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 int /*<<< orphan*/  old_format_only (struct super_block*) ; 
 scalar_t__ reiserfs_is_journal_aborted (struct reiserfs_journal*) ; 
 int /*<<< orphan*/  reiserfs_parse_options (struct super_block*,char*,unsigned long*,unsigned long*,int /*<<< orphan*/ *,unsigned int*,char**,unsigned int*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int reiserfs_resize (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_xattr_init (struct super_block*,int) ; 
 scalar_t__ sb_mnt_count (struct reiserfs_super_block*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 scalar_t__ sb_umount_state (struct reiserfs_super_block*) ; 
 int /*<<< orphan*/  set_sb_mnt_count (struct reiserfs_super_block*,scalar_t__) ; 
 int /*<<< orphan*/  set_sb_umount_state (struct reiserfs_super_block*,scalar_t__) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int reiserfs_remount(struct super_block *s, int *mount_flags, char *arg)
{
	struct reiserfs_super_block *rs;
	struct reiserfs_transaction_handle th;
	unsigned long blocks;
	unsigned long mount_options = REISERFS_SB(s)->s_mount_opt;
	unsigned long safe_mask = 0;
	unsigned int commit_max_age = (unsigned int)-1;
	struct reiserfs_journal *journal = SB_JOURNAL(s);
	char *new_opts;
	int err;
	char *qf_names[REISERFS_MAXQUOTAS];
	unsigned int qfmt = 0;
#ifdef CONFIG_QUOTA
	int i;
#endif

	new_opts = kstrdup(arg, GFP_KERNEL);
	if (arg && !new_opts)
		return -ENOMEM;

	sync_filesystem(s);
	reiserfs_write_lock(s);

#ifdef CONFIG_QUOTA
	memcpy(qf_names, REISERFS_SB(s)->s_qf_names, sizeof(qf_names));
#endif

	rs = SB_DISK_SUPER_BLOCK(s);

	if (!reiserfs_parse_options
	    (s, arg, &mount_options, &blocks, NULL, &commit_max_age,
	    qf_names, &qfmt)) {
#ifdef CONFIG_QUOTA
		for (i = 0; i < REISERFS_MAXQUOTAS; i++)
			if (qf_names[i] != REISERFS_SB(s)->s_qf_names[i])
				kfree(qf_names[i]);
#endif
		err = -EINVAL;
		goto out_err_unlock;
	}
#ifdef CONFIG_QUOTA
	handle_quota_files(s, qf_names, &qfmt);
#endif

	handle_attrs(s);

	/* Add options that are safe here */
	safe_mask |= 1 << REISERFS_SMALLTAIL;
	safe_mask |= 1 << REISERFS_LARGETAIL;
	safe_mask |= 1 << REISERFS_NO_BORDER;
	safe_mask |= 1 << REISERFS_NO_UNHASHED_RELOCATION;
	safe_mask |= 1 << REISERFS_HASHED_RELOCATION;
	safe_mask |= 1 << REISERFS_TEST4;
	safe_mask |= 1 << REISERFS_ATTRS;
	safe_mask |= 1 << REISERFS_XATTRS_USER;
	safe_mask |= 1 << REISERFS_POSIXACL;
	safe_mask |= 1 << REISERFS_BARRIER_FLUSH;
	safe_mask |= 1 << REISERFS_BARRIER_NONE;
	safe_mask |= 1 << REISERFS_ERROR_RO;
	safe_mask |= 1 << REISERFS_ERROR_CONTINUE;
	safe_mask |= 1 << REISERFS_ERROR_PANIC;
	safe_mask |= 1 << REISERFS_USRQUOTA;
	safe_mask |= 1 << REISERFS_GRPQUOTA;

	/*
	 * Update the bitmask, taking care to keep
	 * the bits we're not allowed to change here
	 */
	REISERFS_SB(s)->s_mount_opt =
	    (REISERFS_SB(s)->
	     s_mount_opt & ~safe_mask) | (mount_options & safe_mask);

	if (commit_max_age != 0 && commit_max_age != (unsigned int)-1) {
		journal->j_max_commit_age = commit_max_age;
		journal->j_max_trans_age = commit_max_age;
	} else if (commit_max_age == 0) {
		/* 0 means restore defaults. */
		journal->j_max_commit_age = journal->j_default_max_commit_age;
		journal->j_max_trans_age = JOURNAL_MAX_TRANS_AGE;
	}

	if (blocks) {
		err = reiserfs_resize(s, blocks);
		if (err != 0)
			goto out_err_unlock;
	}

	if (*mount_flags & SB_RDONLY) {
		reiserfs_write_unlock(s);
		reiserfs_xattr_init(s, *mount_flags);
		/* remount read-only */
		if (sb_rdonly(s))
			/* it is read-only already */
			goto out_ok_unlocked;

		err = dquot_suspend(s, -1);
		if (err < 0)
			goto out_err;

		/* try to remount file system with read-only permissions */
		if (sb_umount_state(rs) == REISERFS_VALID_FS
		    || REISERFS_SB(s)->s_mount_state != REISERFS_VALID_FS) {
			goto out_ok_unlocked;
		}

		reiserfs_write_lock(s);

		err = journal_begin(&th, s, 10);
		if (err)
			goto out_err_unlock;

		/* Mounting a rw partition read-only. */
		reiserfs_prepare_for_journal(s, SB_BUFFER_WITH_SB(s), 1);
		set_sb_umount_state(rs, REISERFS_SB(s)->s_mount_state);
		journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
	} else {
		/* remount read-write */
		if (!sb_rdonly(s)) {
			reiserfs_write_unlock(s);
			reiserfs_xattr_init(s, *mount_flags);
			goto out_ok_unlocked;	/* We are read-write already */
		}

		if (reiserfs_is_journal_aborted(journal)) {
			err = journal->j_errno;
			goto out_err_unlock;
		}

		handle_data_mode(s, mount_options);
		handle_barrier_mode(s, mount_options);
		REISERFS_SB(s)->s_mount_state = sb_umount_state(rs);

		/* now it is safe to call journal_begin */
		s->s_flags &= ~SB_RDONLY;
		err = journal_begin(&th, s, 10);
		if (err)
			goto out_err_unlock;

		/* Mount a partition which is read-only, read-write */
		reiserfs_prepare_for_journal(s, SB_BUFFER_WITH_SB(s), 1);
		REISERFS_SB(s)->s_mount_state = sb_umount_state(rs);
		s->s_flags &= ~SB_RDONLY;
		set_sb_umount_state(rs, REISERFS_ERROR_FS);
		if (!old_format_only(s))
			set_sb_mnt_count(rs, sb_mnt_count(rs) + 1);
		/* mark_buffer_dirty (SB_BUFFER_WITH_SB (s), 1); */
		journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
		REISERFS_SB(s)->s_mount_state = REISERFS_VALID_FS;
	}
	/* this will force a full flush of all journal lists */
	SB_JOURNAL(s)->j_must_wait = 1;
	err = journal_end(&th);
	if (err)
		goto out_err_unlock;

	reiserfs_write_unlock(s);
	if (!(*mount_flags & SB_RDONLY)) {
		dquot_resume(s, -1);
		reiserfs_write_lock(s);
		finish_unfinished(s);
		reiserfs_write_unlock(s);
		reiserfs_xattr_init(s, *mount_flags);
	}

out_ok_unlocked:
	return 0;

out_err_unlock:
	reiserfs_write_unlock(s);
out_err:
	kfree(new_opts);
	return err;
}