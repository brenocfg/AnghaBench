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
struct buffer_head {int /*<<< orphan*/  b_state; int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int EIO ; 
 struct buffer_head* ERR_PTR (int) ; 
 int affs_get_block (struct inode*,int,struct buffer_head*,int) ; 
 struct buffer_head* affs_getzeroblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct buffer_head *
affs_getzeroblk_ino(struct inode *inode, int block)
{
	struct buffer_head *bh, tmp_bh;
	int err;

	tmp_bh.b_state = 0;
	err = affs_get_block(inode, block, &tmp_bh, 1);
	if (!err) {
		bh = affs_getzeroblk(inode->i_sb, tmp_bh.b_blocknr);
		if (bh) {
			bh->b_state |= tmp_bh.b_state;
			return bh;
		}
		err = -EIO;
	}
	return ERR_PTR(err);
}