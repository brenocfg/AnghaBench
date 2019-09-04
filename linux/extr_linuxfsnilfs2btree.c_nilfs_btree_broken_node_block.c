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
struct nilfs_btree_node {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_size; scalar_t__ b_data; TYPE_2__* b_page; } ;
struct TYPE_4__ {TYPE_1__* mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ buffer_nilfs_checked (struct buffer_head*) ; 
 scalar_t__ likely (int) ; 
 int nilfs_btree_node_broken (struct nilfs_btree_node*,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_nilfs_checked (struct buffer_head*) ; 

int nilfs_btree_broken_node_block(struct buffer_head *bh)
{
	struct inode *inode;
	int ret;

	if (buffer_nilfs_checked(bh))
		return 0;

	inode = bh->b_page->mapping->host;
	ret = nilfs_btree_node_broken((struct nilfs_btree_node *)bh->b_data,
				      bh->b_size, inode, bh->b_blocknr);
	if (likely(!ret))
		set_buffer_nilfs_checked(bh);
	return ret;
}