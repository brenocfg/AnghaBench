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
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_remove_block_from_cache (struct ocfs2_caching_info*,int /*<<< orphan*/ ) ; 

void ocfs2_remove_from_cache(struct ocfs2_caching_info *ci,
			     struct buffer_head *bh)
{
	sector_t block = bh->b_blocknr;

	ocfs2_remove_block_from_cache(ci, block);
}