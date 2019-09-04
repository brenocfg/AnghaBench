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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; } ;
struct ext4_inode_info {unsigned int i_flags; } ;
struct ext4_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  DAX ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 unsigned int EXT4_APPEND_FL ; 
 unsigned int EXT4_EOFBLOCKS_FL ; 
 unsigned int EXT4_EXTENTS_FL ; 
 unsigned int EXT4_FL_USER_MODIFIABLE ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 unsigned int EXT4_IMMUTABLE_FL ; 
 unsigned int EXT4_JOURNAL_DATA_FL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int ext4_change_inode_journal_flag (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,unsigned int) ; 
 int ext4_ext_migrate (struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int ext4_ind_migrate (struct inode*) ; 
 scalar_t__ ext4_is_quota_file (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_iloc_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int ext4_reserve_inode_write (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  ext4_set_inode_flags (struct inode*) ; 
 int ext4_truncate (struct inode*) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_ioctl_setflags(struct inode *inode,
			       unsigned int flags)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	handle_t *handle = NULL;
	int err = -EPERM, migrate = 0;
	struct ext4_iloc iloc;
	unsigned int oldflags, mask, i;
	unsigned int jflag;

	/* Is it quota file? Do not allow user to mess with it */
	if (ext4_is_quota_file(inode))
		goto flags_out;

	oldflags = ei->i_flags;

	/* The JOURNAL_DATA flag is modifiable only by root */
	jflag = flags & EXT4_JOURNAL_DATA_FL;

	/*
	 * The IMMUTABLE and APPEND_ONLY flags can only be changed by
	 * the relevant capability.
	 *
	 * This test looks nicer. Thanks to Pauline Middelink
	 */
	if ((flags ^ oldflags) & (EXT4_APPEND_FL | EXT4_IMMUTABLE_FL)) {
		if (!capable(CAP_LINUX_IMMUTABLE))
			goto flags_out;
	}

	/*
	 * The JOURNAL_DATA flag can only be changed by
	 * the relevant capability.
	 */
	if ((jflag ^ oldflags) & (EXT4_JOURNAL_DATA_FL)) {
		if (!capable(CAP_SYS_RESOURCE))
			goto flags_out;
	}
	if ((flags ^ oldflags) & EXT4_EXTENTS_FL)
		migrate = 1;

	if (flags & EXT4_EOFBLOCKS_FL) {
		/* we don't support adding EOFBLOCKS flag */
		if (!(oldflags & EXT4_EOFBLOCKS_FL)) {
			err = -EOPNOTSUPP;
			goto flags_out;
		}
	} else if (oldflags & EXT4_EOFBLOCKS_FL) {
		err = ext4_truncate(inode);
		if (err)
			goto flags_out;
	}

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		goto flags_out;
	}
	if (IS_SYNC(inode))
		ext4_handle_sync(handle);
	err = ext4_reserve_inode_write(handle, inode, &iloc);
	if (err)
		goto flags_err;

	for (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
		if (!(mask & EXT4_FL_USER_MODIFIABLE))
			continue;
		/* These flags get special treatment later */
		if (mask == EXT4_JOURNAL_DATA_FL || mask == EXT4_EXTENTS_FL)
			continue;
		if (mask & flags)
			ext4_set_inode_flag(inode, i);
		else
			ext4_clear_inode_flag(inode, i);
	}

	ext4_set_inode_flags(inode);
	inode->i_ctime = current_time(inode);

	err = ext4_mark_iloc_dirty(handle, inode, &iloc);
flags_err:
	ext4_journal_stop(handle);
	if (err)
		goto flags_out;

	if ((jflag ^ oldflags) & (EXT4_JOURNAL_DATA_FL)) {
		/*
		 * Changes to the journaling mode can cause unsafe changes to
		 * S_DAX if we are using the DAX mount option.
		 */
		if (test_opt(inode->i_sb, DAX)) {
			err = -EBUSY;
			goto flags_out;
		}

		err = ext4_change_inode_journal_flag(inode, jflag);
		if (err)
			goto flags_out;
	}
	if (migrate) {
		if (flags & EXT4_EXTENTS_FL)
			err = ext4_ext_migrate(inode);
		else
			err = ext4_ind_migrate(inode);
	}

flags_out:
	return err;
}