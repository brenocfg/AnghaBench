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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_super_block {int dummy; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_data_sem; int /*<<< orphan*/ * i_data; } ;
struct ext4_extent_header {scalar_t__ eh_depth; scalar_t__ eh_entries; } ;
struct ext4_extent {scalar_t__ ee_len; int /*<<< orphan*/  ee_block; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned int ext4_lblk_t ;
typedef  unsigned int ext4_fsblk_t ;
struct TYPE_2__ {struct ext4_super_block* s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELALLOC ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT4_HT_MIGRATE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 scalar_t__ EXT4_MAX_BLOCK_FILE_PHYS ; 
 unsigned int EXT4_NDIR_BLOCKS ; 
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_alloc_da_blocks (struct inode*) ; 
 scalar_t__ ext4_blocks_count (struct ext4_super_block*) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_ext_check_inode (struct inode*) ; 
 unsigned int ext4_ext_pblock (struct ext4_extent*) ; 
 scalar_t__ ext4_has_feature_bigalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_has_feature_extents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 struct ext4_extent_header* ext_inode_hdr (struct inode*) ; 
 int le16_to_cpu (scalar_t__) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_ind_migrate(struct inode *inode)
{
	struct ext4_extent_header	*eh;
	struct ext4_super_block		*es = EXT4_SB(inode->i_sb)->s_es;
	struct ext4_inode_info		*ei = EXT4_I(inode);
	struct ext4_extent		*ex;
	unsigned int			i, len;
	ext4_lblk_t			start, end;
	ext4_fsblk_t			blk;
	handle_t			*handle;
	int				ret;

	if (!ext4_has_feature_extents(inode->i_sb) ||
	    (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		return -EINVAL;

	if (ext4_has_feature_bigalloc(inode->i_sb))
		return -EOPNOTSUPP;

	/*
	 * In order to get correct extent info, force all delayed allocation
	 * blocks to be allocated, otherwise delayed allocation blocks may not
	 * be reflected and bypass the checks on extent header.
	 */
	if (test_opt(inode->i_sb, DELALLOC))
		ext4_alloc_da_blocks(inode);

	handle = ext4_journal_start(inode, EXT4_HT_MIGRATE, 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	down_write(&EXT4_I(inode)->i_data_sem);
	ret = ext4_ext_check_inode(inode);
	if (ret)
		goto errout;

	eh = ext_inode_hdr(inode);
	ex  = EXT_FIRST_EXTENT(eh);
	if (ext4_blocks_count(es) > EXT4_MAX_BLOCK_FILE_PHYS ||
	    eh->eh_depth != 0 || le16_to_cpu(eh->eh_entries) > 1) {
		ret = -EOPNOTSUPP;
		goto errout;
	}
	if (eh->eh_entries == 0)
		blk = len = start = end = 0;
	else {
		len = le16_to_cpu(ex->ee_len);
		blk = ext4_ext_pblock(ex);
		start = le32_to_cpu(ex->ee_block);
		end = start + len - 1;
		if (end >= EXT4_NDIR_BLOCKS) {
			ret = -EOPNOTSUPP;
			goto errout;
		}
	}

	ext4_clear_inode_flag(inode, EXT4_INODE_EXTENTS);
	memset(ei->i_data, 0, sizeof(ei->i_data));
	for (i = start; i <= end; i++)
		ei->i_data[i] = cpu_to_le32(blk++);
	ext4_mark_inode_dirty(handle, inode);
errout:
	ext4_journal_stop(handle);
	up_write(&EXT4_I(inode)->i_data_sem);
	return ret;
}