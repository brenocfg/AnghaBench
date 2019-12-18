#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ufs_sb_private_info {unsigned int s_fpbshift; unsigned int s_fpbmask; } ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/ * b_page; } ;
typedef  unsigned int sector_t ;
struct TYPE_4__ {unsigned int i_lastfrag; int /*<<< orphan*/  truncate_mutex; int /*<<< orphan*/  meta_lock; } ;
struct TYPE_3__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  UFSD (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 TYPE_2__* UFS_I (struct inode*) ; 
 unsigned int UFS_NDIR_FRAGMENT ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int ufs_block_to_path (struct inode*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  ufs_extend_tail (struct inode*,unsigned int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ufs_frag_map (struct inode*,unsigned int*,int) ; 
 scalar_t__ ufs_inode_getblock (struct inode*,scalar_t__,unsigned int,unsigned int,int*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ufs_inode_getfrag (struct inode*,unsigned int,unsigned int,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufs_warning (struct super_block*,char*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ufs_getfrag_block(struct inode *inode, sector_t fragment, struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	int err = 0, new = 0;
	unsigned offsets[4];
	int depth = ufs_block_to_path(inode, fragment >> uspi->s_fpbshift, offsets);
	u64 phys64 = 0;
	unsigned frag = fragment & uspi->s_fpbmask;

	phys64 = ufs_frag_map(inode, offsets, depth);
	if (!create)
		goto done;

	if (phys64) {
		if (fragment >= UFS_NDIR_FRAGMENT)
			goto done;
		read_seqlock_excl(&UFS_I(inode)->meta_lock);
		if (fragment < UFS_I(inode)->i_lastfrag) {
			read_sequnlock_excl(&UFS_I(inode)->meta_lock);
			goto done;
		}
		read_sequnlock_excl(&UFS_I(inode)->meta_lock);
	}
        /* This code entered only while writing ....? */

	mutex_lock(&UFS_I(inode)->truncate_mutex);

	UFSD("ENTER, ino %lu, fragment %llu\n", inode->i_ino, (unsigned long long)fragment);
	if (unlikely(!depth)) {
		ufs_warning(sb, "ufs_get_block", "block > big");
		err = -EIO;
		goto out;
	}

	if (UFS_I(inode)->i_lastfrag < UFS_NDIR_FRAGMENT) {
		unsigned lastfrag = UFS_I(inode)->i_lastfrag;
		unsigned tailfrags = lastfrag & uspi->s_fpbmask;
		if (tailfrags && fragment >= lastfrag) {
			if (!ufs_extend_tail(inode, fragment,
					     &err, bh_result->b_page))
				goto out;
		}
	}

	if (depth == 1) {
		phys64 = ufs_inode_getfrag(inode, offsets[0], fragment,
					   &err, &new, bh_result->b_page);
	} else {
		int i;
		phys64 = ufs_inode_getfrag(inode, offsets[0], fragment,
					   &err, NULL, NULL);
		for (i = 1; i < depth - 1; i++)
			phys64 = ufs_inode_getblock(inode, phys64, offsets[i],
						fragment, &err, NULL, NULL);
		phys64 = ufs_inode_getblock(inode, phys64, offsets[depth - 1],
					fragment, &err, &new, bh_result->b_page);
	}
out:
	if (phys64) {
		phys64 += frag;
		map_bh(bh_result, sb, phys64);
		if (new)
			set_buffer_new(bh_result);
	}
	mutex_unlock(&UFS_I(inode)->truncate_mutex);
	return err;

done:
	if (phys64)
		map_bh(bh_result, sb, phys64 + frag);
	return 0;
}