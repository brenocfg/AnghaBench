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
struct inode {int dummy; } ;
struct ext4_iloc {struct buffer_head* bh; } ;
struct ext4_filename {int dummy; } ;
struct ext4_dir_entry_2 {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xattr_sem; } ;
struct TYPE_3__ {scalar_t__ i_block; } ;

/* Variables and functions */
 TYPE_2__* EXT4_I (struct inode*) ; 
 int EXT4_INLINE_DOTDOT_SIZE ; 
 int EXT4_MIN_INLINE_DATA_SIZE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext4_get_inline_size (struct inode*) ; 
 void* ext4_get_inline_xattr_pos (struct inode*,struct ext4_iloc*) ; 
 scalar_t__ ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 TYPE_1__* ext4_raw_inode (struct ext4_iloc*) ; 
 int ext4_search_dir (struct buffer_head*,void*,int,struct inode*,struct ext4_filename*,int /*<<< orphan*/ ,struct ext4_dir_entry_2**) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct buffer_head *ext4_find_inline_entry(struct inode *dir,
					struct ext4_filename *fname,
					struct ext4_dir_entry_2 **res_dir,
					int *has_inline_data)
{
	int ret;
	struct ext4_iloc iloc;
	void *inline_start;
	int inline_size;

	if (ext4_get_inode_loc(dir, &iloc))
		return NULL;

	down_read(&EXT4_I(dir)->xattr_sem);
	if (!ext4_has_inline_data(dir)) {
		*has_inline_data = 0;
		goto out;
	}

	inline_start = (void *)ext4_raw_inode(&iloc)->i_block +
						EXT4_INLINE_DOTDOT_SIZE;
	inline_size = EXT4_MIN_INLINE_DATA_SIZE - EXT4_INLINE_DOTDOT_SIZE;
	ret = ext4_search_dir(iloc.bh, inline_start, inline_size,
			      dir, fname, 0, res_dir);
	if (ret == 1)
		goto out_find;
	if (ret < 0)
		goto out;

	if (ext4_get_inline_size(dir) == EXT4_MIN_INLINE_DATA_SIZE)
		goto out;

	inline_start = ext4_get_inline_xattr_pos(dir, &iloc);
	inline_size = ext4_get_inline_size(dir) - EXT4_MIN_INLINE_DATA_SIZE;

	ret = ext4_search_dir(iloc.bh, inline_start, inline_size,
			      dir, fname, 0, res_dir);
	if (ret == 1)
		goto out_find;

out:
	brelse(iloc.bh);
	iloc.bh = NULL;
out_find:
	up_read(&EXT4_I(dir)->xattr_sem);
	return iloc.bh;
}