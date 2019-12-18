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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELALLOC ; 
 int /*<<< orphan*/ * EXT4_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_JDATA ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_get_block ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_write_and_wait (struct address_space*) ; 
 int /*<<< orphan*/  generic_block_bmap (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jbd2_journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ *) ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t ext4_bmap(struct address_space *mapping, sector_t block)
{
	struct inode *inode = mapping->host;
	journal_t *journal;
	int err;

	/*
	 * We can get here for an inline file via the FIBMAP ioctl
	 */
	if (ext4_has_inline_data(inode))
		return 0;

	if (mapping_tagged(mapping, PAGECACHE_TAG_DIRTY) &&
			test_opt(inode->i_sb, DELALLOC)) {
		/*
		 * With delalloc we want to sync the file
		 * so that we can make sure we allocate
		 * blocks for file
		 */
		filemap_write_and_wait(mapping);
	}

	if (EXT4_JOURNAL(inode) &&
	    ext4_test_inode_state(inode, EXT4_STATE_JDATA)) {
		/*
		 * This is a REALLY heavyweight approach, but the use of
		 * bmap on dirty files is expected to be extremely rare:
		 * only if we run lilo or swapon on a freshly made file
		 * do we expect this to happen.
		 *
		 * (bmap requires CAP_SYS_RAWIO so this does not
		 * represent an unprivileged user DOS attack --- we'd be
		 * in trouble if mortal users could trigger this path at
		 * will.)
		 *
		 * NB. EXT4_STATE_JDATA is not set on files other than
		 * regular files.  If somebody wants to bmap a directory
		 * or symlink and gets confused because the buffer
		 * hasn't yet been flushed to disk, they deserve
		 * everything they get.
		 */

		ext4_clear_inode_state(inode, EXT4_STATE_JDATA);
		journal = EXT4_JOURNAL(inode);
		jbd2_journal_lock_updates(journal);
		err = jbd2_journal_flush(journal);
		jbd2_journal_unlock_updates(journal);

		if (err)
			return 0;
	}

	return generic_block_bmap(mapping, block, ext4_get_block);
}