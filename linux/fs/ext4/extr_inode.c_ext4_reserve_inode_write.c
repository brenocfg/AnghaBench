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
struct ext4_iloc {int /*<<< orphan*/ * bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ *,char*) ; 
 int EIO ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int
ext4_reserve_inode_write(handle_t *handle, struct inode *inode,
			 struct ext4_iloc *iloc)
{
	int err;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	err = ext4_get_inode_loc(inode, iloc);
	if (!err) {
		BUFFER_TRACE(iloc->bh, "get_write_access");
		err = ext4_journal_get_write_access(handle, iloc->bh);
		if (err) {
			brelse(iloc->bh);
			iloc->bh = NULL;
		}
	}
	ext4_std_error(inode->i_sb, err);
	return err;
}