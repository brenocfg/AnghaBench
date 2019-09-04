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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;

/* Variables and functions */
 struct buffer_head* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 struct buffer_head* ext4_read_block_bitmap_nowait (struct super_block*,int /*<<< orphan*/ ) ; 
 int ext4_wait_block_bitmap (struct super_block*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 

struct buffer_head *
ext4_read_block_bitmap(struct super_block *sb, ext4_group_t block_group)
{
	struct buffer_head *bh;
	int err;

	bh = ext4_read_block_bitmap_nowait(sb, block_group);
	if (IS_ERR(bh))
		return bh;
	err = ext4_wait_block_bitmap(sb, block_group, bh);
	if (err) {
		put_bh(bh);
		return ERR_PTR(err);
	}
	return bh;
}