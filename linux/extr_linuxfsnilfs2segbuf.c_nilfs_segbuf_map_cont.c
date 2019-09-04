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
struct TYPE_2__ {scalar_t__ nblocks; } ;
struct nilfs_segment_buffer {scalar_t__ sb_pseg_start; scalar_t__ sb_fseg_end; scalar_t__ sb_rest_blocks; TYPE_1__ sb_sum; int /*<<< orphan*/  sb_fseg_start; int /*<<< orphan*/  sb_segnum; } ;

/* Variables and functions */

void nilfs_segbuf_map_cont(struct nilfs_segment_buffer *segbuf,
			   struct nilfs_segment_buffer *prev)
{
	segbuf->sb_segnum = prev->sb_segnum;
	segbuf->sb_fseg_start = prev->sb_fseg_start;
	segbuf->sb_fseg_end = prev->sb_fseg_end;
	segbuf->sb_pseg_start = prev->sb_pseg_start + prev->sb_sum.nblocks;
	segbuf->sb_rest_blocks =
		segbuf->sb_fseg_end - segbuf->sb_pseg_start + 1;
}