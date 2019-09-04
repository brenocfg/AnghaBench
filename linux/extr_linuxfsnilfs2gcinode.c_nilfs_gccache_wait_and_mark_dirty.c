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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; TYPE_2__* b_page; } ;
struct TYPE_4__ {TYPE_1__* mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int EEXIST ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_nilfs_node (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 scalar_t__ nilfs_btree_broken_node_block (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int nilfs_gccache_wait_and_mark_dirty(struct buffer_head *bh)
{
	wait_on_buffer(bh);
	if (!buffer_uptodate(bh)) {
		struct inode *inode = bh->b_page->mapping->host;

		nilfs_msg(inode->i_sb, KERN_ERR,
			  "I/O error reading %s block for GC (ino=%lu, vblocknr=%llu)",
			  buffer_nilfs_node(bh) ? "node" : "data",
			  inode->i_ino, (unsigned long long)bh->b_blocknr);
		return -EIO;
	}
	if (buffer_dirty(bh))
		return -EEXIST;

	if (buffer_nilfs_node(bh) && nilfs_btree_broken_node_block(bh)) {
		clear_buffer_uptodate(bh);
		return -EIO;
	}
	mark_buffer_dirty(bh);
	return 0;
}