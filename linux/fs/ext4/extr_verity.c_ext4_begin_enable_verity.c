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
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_VERITY_IN_PROGRESS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int dquot_initialize (struct inode*) ; 
 int ext4_convert_inline_data (struct inode*) ; 
 int ext4_inode_attach_jinode (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_truncate (struct inode*) ; 
 scalar_t__ ext4_verity_in_progress (struct inode*) ; 
 int /*<<< orphan*/  ext4_warning_inode (struct inode*,char*) ; 
 struct inode* file_inode (struct file*) ; 

__attribute__((used)) static int ext4_begin_enable_verity(struct file *filp)
{
	struct inode *inode = file_inode(filp);
	const int credits = 2; /* superblock and inode for ext4_orphan_add() */
	handle_t *handle;
	int err;

	if (ext4_verity_in_progress(inode))
		return -EBUSY;

	/*
	 * Since the file was opened readonly, we have to initialize the jbd
	 * inode and quotas here and not rely on ->open() doing it.  This must
	 * be done before evicting the inline data.
	 */

	err = ext4_inode_attach_jinode(inode);
	if (err)
		return err;

	err = dquot_initialize(inode);
	if (err)
		return err;

	err = ext4_convert_inline_data(inode);
	if (err)
		return err;

	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		ext4_warning_inode(inode,
				   "verity is only allowed on extent-based files");
		return -EOPNOTSUPP;
	}

	/*
	 * ext4 uses the last allocated block to find the verity descriptor, so
	 * we must remove any other blocks past EOF which might confuse things.
	 */
	err = ext4_truncate(inode);
	if (err)
		return err;

	handle = ext4_journal_start(inode, EXT4_HT_INODE, credits);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	err = ext4_orphan_add(handle, inode);
	if (err == 0)
		ext4_set_inode_state(inode, EXT4_STATE_VERITY_IN_PROGRESS);

	ext4_journal_stop(handle);
	return err;
}