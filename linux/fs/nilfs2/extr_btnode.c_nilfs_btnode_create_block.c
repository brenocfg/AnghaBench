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
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_data; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_NILFS_Node ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 struct inode* NILFS_BTNC_I (struct address_space*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

struct buffer_head *
nilfs_btnode_create_block(struct address_space *btnc, __u64 blocknr)
{
	struct inode *inode = NILFS_BTNC_I(btnc);
	struct buffer_head *bh;

	bh = nilfs_grab_buffer(inode, btnc, blocknr, BIT(BH_NILFS_Node));
	if (unlikely(!bh))
		return NULL;

	if (unlikely(buffer_mapped(bh) || buffer_uptodate(bh) ||
		     buffer_dirty(bh))) {
		brelse(bh);
		BUG();
	}
	memset(bh->b_data, 0, i_blocksize(inode));
	bh->b_bdev = inode->i_sb->s_bdev;
	bh->b_blocknr = blocknr;
	set_buffer_mapped(bh);
	set_buffer_uptodate(bh);

	unlock_page(bh->b_page);
	put_page(bh->b_page);
	return bh;
}