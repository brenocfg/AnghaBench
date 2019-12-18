#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct migrate_struct {scalar_t__ curr_block; } ;
struct inode {scalar_t__ i_blocks; int i_ino; TYPE_1__* i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext4_inode_info {scalar_t__* i_data; int /*<<< orphan*/  i_data_sem; } ;
typedef  int /*<<< orphan*/  lb ;
typedef  struct inode handle_t ;
typedef  int __u32 ;
typedef  scalar_t__ __le32 ;
struct TYPE_4__ {int s_blocksize; int /*<<< orphan*/  s_root; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EXT4_DIND_BLOCK ; 
 int /*<<< orphan*/  EXT4_HT_MIGRATE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 size_t EXT4_IND_BLOCK ; 
 int EXT4_INODES_PER_GROUP (TYPE_1__*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int EXT4_MAXQUOTAS_TRANS_BLOCKS (TYPE_1__*) ; 
 int EXT4_NDIR_BLOCKS ; 
 int /*<<< orphan*/  EXT4_STATE_EXT_MIGRATE ; 
 size_t EXT4_TIND_BLOCK ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext4_ext_swap_inode_data (struct inode*,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_ext_tree_init (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_has_feature_extents (TYPE_1__*) ; 
 scalar_t__ ext4_journal_extend (struct inode*,int) ; 
 int /*<<< orphan*/  ext4_journal_restart (struct inode*,int) ; 
 struct inode* ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (struct inode*) ; 
 struct inode* ext4_new_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_orphan_add (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int finish_range (struct inode*,struct inode*,struct migrate_struct*) ; 
 int /*<<< orphan*/  free_ext_block (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_uid_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct migrate_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int update_dind_extent_range (struct inode*,struct inode*,int /*<<< orphan*/ ,struct migrate_struct*) ; 
 int update_extent_range (struct inode*,struct inode*,int /*<<< orphan*/ ,struct migrate_struct*) ; 
 int update_ind_extent_range (struct inode*,struct inode*,int /*<<< orphan*/ ,struct migrate_struct*) ; 
 int update_tind_extent_range (struct inode*,struct inode*,int /*<<< orphan*/ ,struct migrate_struct*) ; 

int ext4_ext_migrate(struct inode *inode)
{
	handle_t *handle;
	int retval = 0, i;
	__le32 *i_data;
	struct ext4_inode_info *ei;
	struct inode *tmp_inode = NULL;
	struct migrate_struct lb;
	unsigned long max_entries;
	__u32 goal;
	uid_t owner[2];

	/*
	 * If the filesystem does not support extents, or the inode
	 * already is extent-based, error out.
	 */
	if (!ext4_has_feature_extents(inode->i_sb) ||
	    (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		return -EINVAL;

	if (S_ISLNK(inode->i_mode) && inode->i_blocks == 0)
		/*
		 * don't migrate fast symlink
		 */
		return retval;

	/*
	 * Worst case we can touch the allocation bitmaps, a bgd
	 * block, and a block to link in the orphan list.  We do need
	 * need to worry about credits for modifying the quota inode.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_MIGRATE,
		4 + EXT4_MAXQUOTAS_TRANS_BLOCKS(inode->i_sb));

	if (IS_ERR(handle)) {
		retval = PTR_ERR(handle);
		return retval;
	}
	goal = (((inode->i_ino - 1) / EXT4_INODES_PER_GROUP(inode->i_sb)) *
		EXT4_INODES_PER_GROUP(inode->i_sb)) + 1;
	owner[0] = i_uid_read(inode);
	owner[1] = i_gid_read(inode);
	tmp_inode = ext4_new_inode(handle, d_inode(inode->i_sb->s_root),
				   S_IFREG, NULL, goal, owner, 0);
	if (IS_ERR(tmp_inode)) {
		retval = PTR_ERR(tmp_inode);
		ext4_journal_stop(handle);
		return retval;
	}
	i_size_write(tmp_inode, i_size_read(inode));
	/*
	 * Set the i_nlink to zero so it will be deleted later
	 * when we drop inode reference.
	 */
	clear_nlink(tmp_inode);

	ext4_ext_tree_init(handle, tmp_inode);
	ext4_orphan_add(handle, tmp_inode);
	ext4_journal_stop(handle);

	/*
	 * start with one credit accounted for
	 * superblock modification.
	 *
	 * For the tmp_inode we already have committed the
	 * transaction that created the inode. Later as and
	 * when we add extents we extent the journal
	 */
	/*
	 * Even though we take i_mutex we can still cause block
	 * allocation via mmap write to holes. If we have allocated
	 * new blocks we fail migrate.  New block allocation will
	 * clear EXT4_STATE_EXT_MIGRATE flag.  The flag is updated
	 * with i_data_sem held to prevent racing with block
	 * allocation.
	 */
	down_read(&EXT4_I(inode)->i_data_sem);
	ext4_set_inode_state(inode, EXT4_STATE_EXT_MIGRATE);
	up_read((&EXT4_I(inode)->i_data_sem));

	handle = ext4_journal_start(inode, EXT4_HT_MIGRATE, 1);
	if (IS_ERR(handle)) {
		/*
		 * It is impossible to update on-disk structures without
		 * a handle, so just rollback in-core changes and live other
		 * work to orphan_list_cleanup()
		 */
		ext4_orphan_del(NULL, tmp_inode);
		retval = PTR_ERR(handle);
		goto out;
	}

	ei = EXT4_I(inode);
	i_data = ei->i_data;
	memset(&lb, 0, sizeof(lb));

	/* 32 bit block address 4 bytes */
	max_entries = inode->i_sb->s_blocksize >> 2;
	for (i = 0; i < EXT4_NDIR_BLOCKS; i++) {
		if (i_data[i]) {
			retval = update_extent_range(handle, tmp_inode,
						le32_to_cpu(i_data[i]), &lb);
			if (retval)
				goto err_out;
		} else
			lb.curr_block++;
	}
	if (i_data[EXT4_IND_BLOCK]) {
		retval = update_ind_extent_range(handle, tmp_inode,
				le32_to_cpu(i_data[EXT4_IND_BLOCK]), &lb);
		if (retval)
			goto err_out;
	} else
		lb.curr_block += max_entries;
	if (i_data[EXT4_DIND_BLOCK]) {
		retval = update_dind_extent_range(handle, tmp_inode,
				le32_to_cpu(i_data[EXT4_DIND_BLOCK]), &lb);
		if (retval)
			goto err_out;
	} else
		lb.curr_block += max_entries * max_entries;
	if (i_data[EXT4_TIND_BLOCK]) {
		retval = update_tind_extent_range(handle, tmp_inode,
				le32_to_cpu(i_data[EXT4_TIND_BLOCK]), &lb);
		if (retval)
			goto err_out;
	}
	/*
	 * Build the last extent
	 */
	retval = finish_range(handle, tmp_inode, &lb);
err_out:
	if (retval)
		/*
		 * Failure case delete the extent information with the
		 * tmp_inode
		 */
		free_ext_block(handle, tmp_inode);
	else {
		retval = ext4_ext_swap_inode_data(handle, inode, tmp_inode);
		if (retval)
			/*
			 * if we fail to swap inode data free the extent
			 * details of the tmp inode
			 */
			free_ext_block(handle, tmp_inode);
	}

	/* We mark the tmp_inode dirty via ext4_ext_tree_init. */
	if (ext4_journal_extend(handle, 1) != 0)
		ext4_journal_restart(handle, 1);

	/*
	 * Mark the tmp_inode as of size zero
	 */
	i_size_write(tmp_inode, 0);

	/*
	 * set the  i_blocks count to zero
	 * so that the ext4_evict_inode() does the
	 * right job
	 *
	 * We don't need to take the i_lock because
	 * the inode is not visible to user space.
	 */
	tmp_inode->i_blocks = 0;

	/* Reset the extent details */
	ext4_ext_tree_init(handle, tmp_inode);
	ext4_journal_stop(handle);
out:
	unlock_new_inode(tmp_inode);
	iput(tmp_inode);

	return retval;
}