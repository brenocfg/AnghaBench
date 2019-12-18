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
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  bforget (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned long) ; 
 struct buffer_head* sb_getblk (struct super_block*,unsigned long) ; 

__attribute__((used)) static int bfs_move_block(unsigned long from, unsigned long to,
					struct super_block *sb)
{
	struct buffer_head *bh, *new;

	bh = sb_bread(sb, from);
	if (!bh)
		return -EIO;
	new = sb_getblk(sb, to);
	memcpy(new->b_data, bh->b_data, bh->b_size);
	mark_buffer_dirty(new);
	bforget(bh);
	brelse(new);
	return 0;
}