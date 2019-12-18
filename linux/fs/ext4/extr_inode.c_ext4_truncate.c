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
struct inode {int i_state; int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; scalar_t__ i_nlink; TYPE_1__* i_sb; struct address_space* i_mapping; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_data_sem; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_HT_TRUNCATE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EOFBLOCKS ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_DA_ALLOC_CLOSE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int I_FREEING ; 
 int I_NEW ; 
 int /*<<< orphan*/  NO_AUTO_DA_ALLOC ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_block_truncate_page (int /*<<< orphan*/ *,struct address_space*,int) ; 
 unsigned int ext4_blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_can_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int ext4_ext_truncate (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_ind_truncate (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_inline_data_truncate (struct inode*,int*) ; 
 scalar_t__ ext4_inode_attach_jinode (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 unsigned int ext4_writepage_trans_blocks (struct inode*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  test_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_truncate_enter (struct inode*) ; 
 int /*<<< orphan*/  trace_ext4_truncate_exit (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_truncate(struct inode *inode)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	unsigned int credits;
	int err = 0;
	handle_t *handle;
	struct address_space *mapping = inode->i_mapping;

	/*
	 * There is a possibility that we're either freeing the inode
	 * or it's a completely new inode. In those cases we might not
	 * have i_mutex locked because it's not necessary.
	 */
	if (!(inode->i_state & (I_NEW|I_FREEING)))
		WARN_ON(!inode_is_locked(inode));
	trace_ext4_truncate_enter(inode);

	if (!ext4_can_truncate(inode))
		return 0;

	ext4_clear_inode_flag(inode, EXT4_INODE_EOFBLOCKS);

	if (inode->i_size == 0 && !test_opt(inode->i_sb, NO_AUTO_DA_ALLOC))
		ext4_set_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE);

	if (ext4_has_inline_data(inode)) {
		int has_inline = 1;

		err = ext4_inline_data_truncate(inode, &has_inline);
		if (err)
			return err;
		if (has_inline)
			return 0;
	}

	/* If we zero-out tail of the page, we have to create jinode for jbd2 */
	if (inode->i_size & (inode->i_sb->s_blocksize - 1)) {
		if (ext4_inode_attach_jinode(inode) < 0)
			return 0;
	}

	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		credits = ext4_writepage_trans_blocks(inode);
	else
		credits = ext4_blocks_for_truncate(inode);

	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (inode->i_size & (inode->i_sb->s_blocksize - 1))
		ext4_block_truncate_page(handle, mapping, inode->i_size);

	/*
	 * We add the inode to the orphan list, so that if this
	 * truncate spans multiple transactions, and we crash, we will
	 * resume the truncate when the filesystem recovers.  It also
	 * marks the inode dirty, to catch the new size.
	 *
	 * Implication: the file must always be in a sane, consistent
	 * truncatable state while each transaction commits.
	 */
	err = ext4_orphan_add(handle, inode);
	if (err)
		goto out_stop;

	down_write(&EXT4_I(inode)->i_data_sem);

	ext4_discard_preallocations(inode);

	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		err = ext4_ext_truncate(handle, inode);
	else
		ext4_ind_truncate(handle, inode);

	up_write(&ei->i_data_sem);
	if (err)
		goto out_stop;

	if (IS_SYNC(inode))
		ext4_handle_sync(handle);

out_stop:
	/*
	 * If this was a simple ftruncate() and the file will remain alive,
	 * then we need to clear up the orphan record which we created above.
	 * However, if this was a real unlink then we were called by
	 * ext4_evict_inode(), and we allow that function to clean up the
	 * orphan info for us.
	 */
	if (inode->i_nlink)
		ext4_orphan_del(handle, inode);

	inode->i_mtime = inode->i_ctime = current_time(inode);
	ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);

	trace_ext4_truncate_exit(inode);
	return err;
}