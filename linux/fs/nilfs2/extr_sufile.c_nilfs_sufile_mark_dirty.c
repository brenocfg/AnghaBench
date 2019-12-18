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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int nilfs_sufile_get_segment_usage_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 

int nilfs_sufile_mark_dirty(struct inode *sufile, __u64 segnum)
{
	struct buffer_head *bh;
	int ret;

	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0, &bh);
	if (!ret) {
		mark_buffer_dirty(bh);
		nilfs_mdt_mark_dirty(sufile);
		brelse(bh);
	}
	return ret;
}