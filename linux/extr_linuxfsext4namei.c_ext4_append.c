#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_size; TYPE_1__* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_7__ {int i_disksize; } ;
struct TYPE_6__ {int s_max_dir_size_kb; } ;
struct TYPE_5__ {int s_blocksize_bits; scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int ENOSPC ; 
 struct buffer_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXT4_GET_BLOCKS_CREATE ; 
 TYPE_4__* EXT4_I (struct inode*) ; 
 TYPE_2__* EXT4_SB (TYPE_1__*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* ext4_bread (int /*<<< orphan*/ *,struct inode*,int,int /*<<< orphan*/ ) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_std_error (TYPE_1__*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct buffer_head *ext4_append(handle_t *handle,
					struct inode *inode,
					ext4_lblk_t *block)
{
	struct buffer_head *bh;
	int err;

	if (unlikely(EXT4_SB(inode->i_sb)->s_max_dir_size_kb &&
		     ((inode->i_size >> 10) >=
		      EXT4_SB(inode->i_sb)->s_max_dir_size_kb)))
		return ERR_PTR(-ENOSPC);

	*block = inode->i_size >> inode->i_sb->s_blocksize_bits;

	bh = ext4_bread(handle, inode, *block, EXT4_GET_BLOCKS_CREATE);
	if (IS_ERR(bh))
		return bh;
	inode->i_size += inode->i_sb->s_blocksize;
	EXT4_I(inode)->i_disksize = inode->i_size;
	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_write_access(handle, bh);
	if (err) {
		brelse(bh);
		ext4_std_error(inode->i_sb, err);
		return ERR_PTR(err);
	}
	return bh;
}