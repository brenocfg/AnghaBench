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
struct tree_balance {int dummy; } ;
struct buffer_head {int dummy; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 int /*<<< orphan*/  FREE_LEVEL ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_blkh_level (struct block_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blkh_nr_item (struct block_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_thrown (struct tree_balance*,struct buffer_head*) ; 

void reiserfs_invalidate_buffer(struct tree_balance *tb, struct buffer_head *bh)
{
	struct block_head *blkh;
	blkh = B_BLK_HEAD(bh);
	set_blkh_level(blkh, FREE_LEVEL);
	set_blkh_nr_item(blkh, 0);

	clear_buffer_dirty(bh);
	store_thrown(tb, bh);
}