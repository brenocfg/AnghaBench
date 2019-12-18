#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {unsigned int s_blocksize; int s_blocksize_bits; } ;
struct inode {int i_size; struct super_block* i_sb; } ;
struct ext3_dir_entry_2 {int /*<<< orphan*/  rec_len; scalar_t__ inode; } ;
struct ext2_icb {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int ext3_lblk_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_flags; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int ERR_BAD_DX_DIR ; 
 int /*<<< orphan*/  EXT3_FEATURE_COMPAT_DIR_INDEX ; 
 scalar_t__ EXT3_HAS_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_3__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  EXT3_INDEX_FL ; 
 int add_dirent_to_buf (struct ext2_icb*,struct dentry*,struct inode*,struct ext3_dir_entry_2*,struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* ext3_append (struct ext2_icb*,struct inode*,int*,int*) ; 
 struct buffer_head* ext3_bread (struct ext2_icb*,struct inode*,int,int*) ; 
 int ext3_dx_add_entry (struct ext2_icb*,struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ext3_rec_len_to_disk (unsigned int) ; 
 int /*<<< orphan*/  ext3_save_inode (struct ext2_icb*,struct inode*) ; 
 scalar_t__ is_dx (struct inode*) ; 
 int make_indexed_dir (struct ext2_icb*,struct dentry*,struct inode*,struct buffer_head*) ; 

int ext3_add_entry(struct ext2_icb *icb, struct dentry *dentry, struct inode *inode)
{
    struct inode *dir = dentry->d_parent->d_inode;
    struct buffer_head *bh;
    struct ext3_dir_entry_2 *de;
    struct super_block *sb;
    int	retval;
#ifdef EXT2_HTREE_INDEX
    int	dx_fallback=0;
#endif
    unsigned blocksize;
    ext3_lblk_t block, blocks;

    sb = dir->i_sb;
    blocksize = sb->s_blocksize;
    if (!dentry->d_name.len)
        return -EINVAL;

#ifdef EXT2_HTREE_INDEX
    if (is_dx(dir)) {
        retval = ext3_dx_add_entry(icb, dentry, inode);
        if (!retval || (retval != ERR_BAD_DX_DIR))
            return retval;
        EXT3_I(dir)->i_flags &= ~EXT3_INDEX_FL;
        dx_fallback++;
        ext3_save_inode(icb, dir);
    }
#endif

    blocks = (ext3_lblk_t)(dir->i_size >> sb->s_blocksize_bits);
    for (block = 0; block < blocks; block++) {
        bh = ext3_bread(icb, dir, block, &retval);
        if (!bh)
            return retval;
        retval = add_dirent_to_buf(icb, dentry, inode, NULL, bh);
        if (retval != -ENOSPC)
            return retval;

#ifdef EXT2_HTREE_INDEX
        if (blocks == 1 && !dx_fallback &&
                EXT3_HAS_COMPAT_FEATURE(sb, EXT3_FEATURE_COMPAT_DIR_INDEX))
            return make_indexed_dir(icb, dentry, inode, bh);
#endif

        brelse(bh);
    }
    bh = ext3_append(icb, dir, &block, &retval);
    if (!bh)
        return retval;
    de = (struct ext3_dir_entry_2 *) bh->b_data;
    de->inode = 0;
    de->rec_len = ext3_rec_len_to_disk(blocksize);
    return add_dirent_to_buf(icb, dentry, inode, de, bh);
}