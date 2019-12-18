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
struct the_nilfs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; int /*<<< orphan*/  sb_nextnum; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_get_segment_start_blocknr (struct the_nilfs*,int /*<<< orphan*/ ) ; 

void nilfs_segbuf_set_next_segnum(struct nilfs_segment_buffer *segbuf,
				  __u64 nextnum, struct the_nilfs *nilfs)
{
	segbuf->sb_nextnum = nextnum;
	segbuf->sb_sum.next = nilfs_get_segment_start_blocknr(nilfs, nextnum);
}