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
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_file_acl; } ;

/* Variables and functions */
 struct buffer_head* ERR_PTR (int) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  REQ_PRIO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* ext4_sb_bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_xattr_check_block (struct inode*,struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *ext4_xattr_get_block(struct inode *inode)
{
	struct buffer_head *bh;
	int error;

	if (!EXT4_I(inode)->i_file_acl)
		return NULL;
	bh = ext4_sb_bread(inode->i_sb, EXT4_I(inode)->i_file_acl, REQ_PRIO);
	if (IS_ERR(bh))
		return bh;
	error = ext4_xattr_check_block(inode, bh);
	if (error) {
		brelse(bh);
		return ERR_PTR(error);
	}
	return bh;
}