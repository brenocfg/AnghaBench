#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct super_block {int dummy; } ;
struct TYPE_8__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_7__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct inode {int i_state; int i_mode; int i_size; scalar_t__ i_nlink; char* i_link; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_fop; void* i_generation; void* i_blocks; TYPE_4__ i_ctime; TYPE_3__ i_mtime; TYPE_2__ i_atime; } ;
struct ext2_inode_info {unsigned long i_block_group; scalar_t__* i_data; scalar_t__ i_dir_start_lookup; scalar_t__ i_state; void* i_dtime; void* i_dir_acl; void* i_file_acl; int /*<<< orphan*/  i_frag_size; int /*<<< orphan*/  i_frag_no; void* i_faddr; void* i_flags; int /*<<< orphan*/ * i_block_alloc_info; } ;
struct ext2_inode {scalar_t__* i_block; scalar_t__ i_generation; scalar_t__ i_dir_acl; scalar_t__ i_size_high; scalar_t__ i_file_acl; int /*<<< orphan*/  i_fsize; int /*<<< orphan*/  i_frag; scalar_t__ i_faddr; scalar_t__ i_flags; scalar_t__ i_blocks; scalar_t__ i_dtime; scalar_t__ i_mtime; scalar_t__ i_ctime; scalar_t__ i_atime; scalar_t__ i_size; int /*<<< orphan*/  i_links_count; int /*<<< orphan*/  i_gid_high; int /*<<< orphan*/  i_uid_high; int /*<<< orphan*/  i_gid_low; int /*<<< orphan*/  i_uid_low; int /*<<< orphan*/  i_mode; } ;
struct buffer_head {int dummy; } ;
typedef  int gid_t ;
typedef  int __u64 ;
struct TYPE_5__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 long EFSCORRUPTED ; 
 long EIO ; 
 long ENOMEM ; 
 struct inode* ERR_PTR (long) ; 
 long ESTALE ; 
 struct ext2_inode_info* EXT2_I (struct inode*) ; 
 unsigned long EXT2_INODES_PER_GROUP (int /*<<< orphan*/ ) ; 
 int EXT2_N_BLOCKS ; 
 int /*<<< orphan*/  EXT2_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct ext2_inode*) ; 
 int I_NEW ; 
 int /*<<< orphan*/  NOBH ; 
 int /*<<< orphan*/  NO_UID32 ; 
 long PTR_ERR (struct ext2_inode*) ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 scalar_t__ S_ISREG (scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ext2_aops ; 
 int /*<<< orphan*/  ext2_data_block_valid (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ext2_dir_inode_operations ; 
 int /*<<< orphan*/  ext2_dir_operations ; 
 int /*<<< orphan*/  ext2_error (struct super_block*,char*,char*,void*) ; 
 int /*<<< orphan*/  ext2_fast_symlink_inode_operations ; 
 struct ext2_inode* ext2_get_inode (int /*<<< orphan*/ ,unsigned long,struct buffer_head**) ; 
 scalar_t__ ext2_inode_is_fast_symlink (struct inode*) ; 
 int /*<<< orphan*/  ext2_nobh_aops ; 
 int /*<<< orphan*/  ext2_set_file_ops (struct inode*) ; 
 int /*<<< orphan*/  ext2_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ext2_special_inode_operations ; 
 int /*<<< orphan*/  ext2_symlink_inode_operations ; 
 int /*<<< orphan*/  i_gid_write (struct inode*,int) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_uid_write (struct inode*,int) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  nd_terminate_link (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  new_decode_dev (void*) ; 
 int /*<<< orphan*/  old_decode_dev (void*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ext2_iget (struct super_block *sb, unsigned long ino)
{
	struct ext2_inode_info *ei;
	struct buffer_head * bh = NULL;
	struct ext2_inode *raw_inode;
	struct inode *inode;
	long ret = -EIO;
	int n;
	uid_t i_uid;
	gid_t i_gid;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	ei = EXT2_I(inode);
	ei->i_block_alloc_info = NULL;

	raw_inode = ext2_get_inode(inode->i_sb, ino, &bh);
	if (IS_ERR(raw_inode)) {
		ret = PTR_ERR(raw_inode);
 		goto bad_inode;
	}

	inode->i_mode = le16_to_cpu(raw_inode->i_mode);
	i_uid = (uid_t)le16_to_cpu(raw_inode->i_uid_low);
	i_gid = (gid_t)le16_to_cpu(raw_inode->i_gid_low);
	if (!(test_opt (inode->i_sb, NO_UID32))) {
		i_uid |= le16_to_cpu(raw_inode->i_uid_high) << 16;
		i_gid |= le16_to_cpu(raw_inode->i_gid_high) << 16;
	}
	i_uid_write(inode, i_uid);
	i_gid_write(inode, i_gid);
	set_nlink(inode, le16_to_cpu(raw_inode->i_links_count));
	inode->i_size = le32_to_cpu(raw_inode->i_size);
	inode->i_atime.tv_sec = (signed)le32_to_cpu(raw_inode->i_atime);
	inode->i_ctime.tv_sec = (signed)le32_to_cpu(raw_inode->i_ctime);
	inode->i_mtime.tv_sec = (signed)le32_to_cpu(raw_inode->i_mtime);
	inode->i_atime.tv_nsec = inode->i_mtime.tv_nsec = inode->i_ctime.tv_nsec = 0;
	ei->i_dtime = le32_to_cpu(raw_inode->i_dtime);
	/* We now have enough fields to check if the inode was active or not.
	 * This is needed because nfsd might try to access dead inodes
	 * the test is that same one that e2fsck uses
	 * NeilBrown 1999oct15
	 */
	if (inode->i_nlink == 0 && (inode->i_mode == 0 || ei->i_dtime)) {
		/* this inode is deleted */
		ret = -ESTALE;
		goto bad_inode;
	}
	inode->i_blocks = le32_to_cpu(raw_inode->i_blocks);
	ei->i_flags = le32_to_cpu(raw_inode->i_flags);
	ext2_set_inode_flags(inode);
	ei->i_faddr = le32_to_cpu(raw_inode->i_faddr);
	ei->i_frag_no = raw_inode->i_frag;
	ei->i_frag_size = raw_inode->i_fsize;
	ei->i_file_acl = le32_to_cpu(raw_inode->i_file_acl);
	ei->i_dir_acl = 0;

	if (ei->i_file_acl &&
	    !ext2_data_block_valid(EXT2_SB(sb), ei->i_file_acl, 1)) {
		ext2_error(sb, "ext2_iget", "bad extended attribute block %u",
			   ei->i_file_acl);
		ret = -EFSCORRUPTED;
		goto bad_inode;
	}

	if (S_ISREG(inode->i_mode))
		inode->i_size |= ((__u64)le32_to_cpu(raw_inode->i_size_high)) << 32;
	else
		ei->i_dir_acl = le32_to_cpu(raw_inode->i_dir_acl);
	if (i_size_read(inode) < 0) {
		ret = -EFSCORRUPTED;
		goto bad_inode;
	}
	ei->i_dtime = 0;
	inode->i_generation = le32_to_cpu(raw_inode->i_generation);
	ei->i_state = 0;
	ei->i_block_group = (ino - 1) / EXT2_INODES_PER_GROUP(inode->i_sb);
	ei->i_dir_start_lookup = 0;

	/*
	 * NOTE! The in-memory inode i_data array is in little-endian order
	 * even on big-endian machines: we do NOT byteswap the block numbers!
	 */
	for (n = 0; n < EXT2_N_BLOCKS; n++)
		ei->i_data[n] = raw_inode->i_block[n];

	if (S_ISREG(inode->i_mode)) {
		ext2_set_file_ops(inode);
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &ext2_dir_inode_operations;
		inode->i_fop = &ext2_dir_operations;
		if (test_opt(inode->i_sb, NOBH))
			inode->i_mapping->a_ops = &ext2_nobh_aops;
		else
			inode->i_mapping->a_ops = &ext2_aops;
	} else if (S_ISLNK(inode->i_mode)) {
		if (ext2_inode_is_fast_symlink(inode)) {
			inode->i_link = (char *)ei->i_data;
			inode->i_op = &ext2_fast_symlink_inode_operations;
			nd_terminate_link(ei->i_data, inode->i_size,
				sizeof(ei->i_data) - 1);
		} else {
			inode->i_op = &ext2_symlink_inode_operations;
			inode_nohighmem(inode);
			if (test_opt(inode->i_sb, NOBH))
				inode->i_mapping->a_ops = &ext2_nobh_aops;
			else
				inode->i_mapping->a_ops = &ext2_aops;
		}
	} else {
		inode->i_op = &ext2_special_inode_operations;
		if (raw_inode->i_block[0])
			init_special_inode(inode, inode->i_mode,
			   old_decode_dev(le32_to_cpu(raw_inode->i_block[0])));
		else 
			init_special_inode(inode, inode->i_mode,
			   new_decode_dev(le32_to_cpu(raw_inode->i_block[1])));
	}
	brelse (bh);
	unlock_new_inode(inode);
	return inode;
	
bad_inode:
	brelse(bh);
	iget_failed(inode);
	return ERR_PTR(ret);
}