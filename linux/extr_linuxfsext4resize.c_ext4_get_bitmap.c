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
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ bh_submit_read (struct buffer_head*) ; 
 int /*<<< orphan*/  bh_uptodate_or_lock (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct buffer_head *ext4_get_bitmap(struct super_block *sb, __u64 block)
{
	struct buffer_head *bh = sb_getblk(sb, block);
	if (unlikely(!bh))
		return NULL;
	if (!bh_uptodate_or_lock(bh)) {
		if (bh_submit_read(bh) < 0) {
			brelse(bh);
			return NULL;
		}
	}

	return bh;
}