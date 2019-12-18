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
struct the_nilfs {int dummy; } ;
struct nilfs_segment_buffer {scalar_t__ sb_pseg_start; scalar_t__ sb_fseg_end; scalar_t__ sb_rest_blocks; scalar_t__ sb_fseg_start; int /*<<< orphan*/  sb_segnum; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_get_segment_range (struct the_nilfs*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

void nilfs_segbuf_map(struct nilfs_segment_buffer *segbuf, __u64 segnum,
		     unsigned long offset, struct the_nilfs *nilfs)
{
	segbuf->sb_segnum = segnum;
	nilfs_get_segment_range(nilfs, segnum, &segbuf->sb_fseg_start,
				&segbuf->sb_fseg_end);

	segbuf->sb_pseg_start = segbuf->sb_fseg_start + offset;
	segbuf->sb_rest_blocks =
		segbuf->sb_fseg_end - segbuf->sb_pseg_start + 1;
}