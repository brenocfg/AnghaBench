#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_2__* i_sb; } ;
struct ext4_xattr_ibody_header {int dummy; } ;
struct ext4_sb_info {int s_inode_size; TYPE_1__* s_es; } ;
struct ext4_inode {int dummy; } ;
struct buffer_head {int b_size; void* b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_8__ {int i_extra_isize; scalar_t__ i_file_acl; } ;
struct TYPE_7__ {size_t s_blocksize; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_mnt_count; int /*<<< orphan*/  s_min_extra_isize; } ;

/* Variables and functions */
 void* BFIRST (struct buffer_head*) ; 
 void* BHDR (struct buffer_head*) ; 
 int ENOSPC ; 
 int EXT4_GOOD_OLD_INODE_SIZE ; 
 TYPE_5__* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (TYPE_2__*) ; 
 void* IFIRST (struct ext4_xattr_ibody_header*) ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,struct ext4_inode*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  REQ_PRIO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* ext4_sb_bread (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_warning (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int ext4_xattr_check_block (struct inode*,struct buffer_head*) ; 
 size_t ext4_xattr_free_space (void*,size_t*,void*,int*) ; 
 int ext4_xattr_make_inode_space (int /*<<< orphan*/ *,struct inode*,struct ext4_inode*,int,size_t,size_t,int*) ; 
 int /*<<< orphan*/  ext4_xattr_shift_entries (void*,int,void*,void*,int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int xattr_check_inode (struct inode*,struct ext4_xattr_ibody_header*,void*) ; 

int ext4_expand_extra_isize_ea(struct inode *inode, int new_extra_isize,
			       struct ext4_inode *raw_inode, handle_t *handle)
{
	struct ext4_xattr_ibody_header *header;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	static unsigned int mnt_count;
	size_t min_offs;
	size_t ifree, bfree;
	int total_ino;
	void *base, *end;
	int error = 0, tried_min_extra_isize = 0;
	int s_min_extra_isize = le16_to_cpu(sbi->s_es->s_min_extra_isize);
	int isize_diff;	/* How much do we need to grow i_extra_isize */

retry:
	isize_diff = new_extra_isize - EXT4_I(inode)->i_extra_isize;
	if (EXT4_I(inode)->i_extra_isize >= new_extra_isize)
		return 0;

	header = IHDR(inode, raw_inode);

	/*
	 * Check if enough free space is available in the inode to shift the
	 * entries ahead by new_extra_isize.
	 */

	base = IFIRST(header);
	end = (void *)raw_inode + EXT4_SB(inode->i_sb)->s_inode_size;
	min_offs = end - base;
	total_ino = sizeof(struct ext4_xattr_ibody_header) + sizeof(u32);

	error = xattr_check_inode(inode, header, end);
	if (error)
		goto cleanup;

	ifree = ext4_xattr_free_space(base, &min_offs, base, &total_ino);
	if (ifree >= isize_diff)
		goto shift;

	/*
	 * Enough free space isn't available in the inode, check if
	 * EA block can hold new_extra_isize bytes.
	 */
	if (EXT4_I(inode)->i_file_acl) {
		struct buffer_head *bh;

		bh = ext4_sb_bread(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
		if (IS_ERR(bh)) {
			error = PTR_ERR(bh);
			goto cleanup;
		}
		error = ext4_xattr_check_block(inode, bh);
		if (error) {
			brelse(bh);
			goto cleanup;
		}
		base = BHDR(bh);
		end = bh->b_data + bh->b_size;
		min_offs = end - base;
		bfree = ext4_xattr_free_space(BFIRST(bh), &min_offs, base,
					      NULL);
		brelse(bh);
		if (bfree + ifree < isize_diff) {
			if (!tried_min_extra_isize && s_min_extra_isize) {
				tried_min_extra_isize++;
				new_extra_isize = s_min_extra_isize;
				goto retry;
			}
			error = -ENOSPC;
			goto cleanup;
		}
	} else {
		bfree = inode->i_sb->s_blocksize;
	}

	error = ext4_xattr_make_inode_space(handle, inode, raw_inode,
					    isize_diff, ifree, bfree,
					    &total_ino);
	if (error) {
		if (error == -ENOSPC && !tried_min_extra_isize &&
		    s_min_extra_isize) {
			tried_min_extra_isize++;
			new_extra_isize = s_min_extra_isize;
			goto retry;
		}
		goto cleanup;
	}
shift:
	/* Adjust the offsets and shift the remaining entries ahead */
	ext4_xattr_shift_entries(IFIRST(header), EXT4_I(inode)->i_extra_isize
			- new_extra_isize, (void *)raw_inode +
			EXT4_GOOD_OLD_INODE_SIZE + new_extra_isize,
			(void *)header, total_ino);
	EXT4_I(inode)->i_extra_isize = new_extra_isize;

cleanup:
	if (error && (mnt_count != le16_to_cpu(sbi->s_es->s_mnt_count))) {
		ext4_warning(inode->i_sb, "Unable to expand inode %lu. Delete some EAs or run e2fsck.",
			     inode->i_ino);
		mnt_count = le16_to_cpu(sbi->s_es->s_mnt_count);
	}
	return error;
}