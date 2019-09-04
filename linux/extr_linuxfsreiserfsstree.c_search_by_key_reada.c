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
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  REQ_RAHEAD ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int search_by_key_reada(struct super_block *s,
				struct buffer_head **bh,
				b_blocknr_t *b, int num)
{
	int i, j;
	int depth = -1;

	for (i = 0; i < num; i++) {
		bh[i] = sb_getblk(s, b[i]);
	}
	/*
	 * We are going to read some blocks on which we
	 * have a reference. It's safe, though we might be
	 * reading blocks concurrently changed if we release
	 * the lock. But it's still fine because we check later
	 * if the tree changed
	 */
	for (j = 0; j < i; j++) {
		/*
		 * note, this needs attention if we are getting rid of the BKL
		 * you have to make sure the prepared bit isn't set on this
		 * buffer
		 */
		if (!buffer_uptodate(bh[j])) {
			if (depth == -1)
				depth = reiserfs_write_unlock_nested(s);
			ll_rw_block(REQ_OP_READ, REQ_RAHEAD, 1, bh + j);
		}
		brelse(bh[j]);
	}
	return depth;
}