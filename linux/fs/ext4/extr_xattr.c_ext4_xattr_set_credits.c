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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xattr_sem; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_journal; } ;

/* Variables and functions */
 TYPE_2__* EXT4_I (struct inode*) ; 
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int __ext4_xattr_set_credits (int /*<<< orphan*/ ,struct inode*,struct buffer_head*,size_t,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct buffer_head* ext4_xattr_get_block (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_xattr_set_credits(struct inode *inode, size_t value_len,
			   bool is_create, int *credits)
{
	struct buffer_head *bh;
	int err;

	*credits = 0;

	if (!EXT4_SB(inode->i_sb)->s_journal)
		return 0;

	down_read(&EXT4_I(inode)->xattr_sem);

	bh = ext4_xattr_get_block(inode);
	if (IS_ERR(bh)) {
		err = PTR_ERR(bh);
	} else {
		*credits = __ext4_xattr_set_credits(inode->i_sb, inode, bh,
						    value_len, is_create);
		brelse(bh);
		err = 0;
	}

	up_read(&EXT4_I(inode)->xattr_sem);
	return err;
}