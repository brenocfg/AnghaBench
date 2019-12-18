#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent_idx {int /*<<< orphan*/  ei_block; } ;
struct ext4_ext_path {TYPE_1__* p_hdr; struct ext4_extent_idx* p_idx; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
struct TYPE_3__ {int /*<<< orphan*/  eh_entries; int /*<<< orphan*/  eh_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,...) ; 
 struct ext4_extent_idx* EXT_LAST_INDEX (TYPE_1__*) ; 
 struct ext4_extent_idx* EXT_MAX_INDEX (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ext4_ext_dirty (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int ext4_ext_get_access (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_idx_store_pblock (struct ext4_extent_idx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ext4_extent_idx*,struct ext4_extent_idx*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_ext_insert_index(void *icb, handle_t *handle, struct inode *inode,
		struct ext4_ext_path *curp,
		int logical, ext4_fsblk_t ptr)
{
	struct ext4_extent_idx *ix;
	int len, err;

	err = ext4_ext_get_access(icb, handle, inode, curp);
	if (err)
		return err;

	if (unlikely(logical == le32_to_cpu(curp->p_idx->ei_block))) {
		EXT4_ERROR_INODE(inode,
				"logical %d == ei_block %d!",
				logical, le32_to_cpu(curp->p_idx->ei_block));
		return -EIO;
	}

	if (unlikely(le16_to_cpu(curp->p_hdr->eh_entries)
				>= le16_to_cpu(curp->p_hdr->eh_max))) {
		EXT4_ERROR_INODE(inode,
				"eh_entries %d >= eh_max %d!",
				le16_to_cpu(curp->p_hdr->eh_entries),
				le16_to_cpu(curp->p_hdr->eh_max));
		return -EIO;
	}

	if (logical > le32_to_cpu(curp->p_idx->ei_block)) {
		/* insert after */
		ext_debug("insert new index %d after: %llu\n", logical, ptr);
		ix = curp->p_idx + 1;
	} else {
		/* insert before */
		ext_debug("insert new index %d before: %llu\n", logical, ptr);
		ix = curp->p_idx;
	}

	len = EXT_LAST_INDEX(curp->p_hdr) - ix + 1;
	BUG_ON(len < 0);
	if (len > 0) {
		ext_debug("insert new index %d: "
				"move %d indices from 0x%p to 0x%p\n",
				logical, len, ix, ix + 1);
		memmove(ix + 1, ix, len * sizeof(struct ext4_extent_idx));
	}

	if (unlikely(ix > EXT_MAX_INDEX(curp->p_hdr))) {
		EXT4_ERROR_INODE(inode, "ix > EXT_MAX_INDEX!");
		return -EIO;
	}

	ix->ei_block = cpu_to_le32(logical);
	ext4_idx_store_pblock(ix, ptr);
	le16_add_cpu(&curp->p_hdr->eh_entries, 1);

	if (unlikely(ix > EXT_LAST_INDEX(curp->p_hdr))) {
		EXT4_ERROR_INODE(inode, "ix > EXT_LAST_INDEX!");
		return -EIO;
	}

	err = ext4_ext_dirty(icb, handle, inode, curp);
	ext4_std_error(inode->i_sb, err);

	return err;
}