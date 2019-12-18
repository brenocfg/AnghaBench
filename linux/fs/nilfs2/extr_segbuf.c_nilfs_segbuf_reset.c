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
typedef  int /*<<< orphan*/  time64_t ;
struct nilfs_segment_summary {int dummy; } ;
struct TYPE_2__ {unsigned int flags; int sumbytes; int /*<<< orphan*/  cno; int /*<<< orphan*/  ctime; scalar_t__ nfileblk; scalar_t__ nfinfo; scalar_t__ nsumblk; scalar_t__ nblocks; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int nilfs_segbuf_extend_segsum (struct nilfs_segment_buffer*) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_segbuf_reset(struct nilfs_segment_buffer *segbuf, unsigned int flags,
		       time64_t ctime, __u64 cno)
{
	int err;

	segbuf->sb_sum.nblocks = segbuf->sb_sum.nsumblk = 0;
	err = nilfs_segbuf_extend_segsum(segbuf);
	if (unlikely(err))
		return err;

	segbuf->sb_sum.flags = flags;
	segbuf->sb_sum.sumbytes = sizeof(struct nilfs_segment_summary);
	segbuf->sb_sum.nfinfo = segbuf->sb_sum.nfileblk = 0;
	segbuf->sb_sum.ctime = ctime;
	segbuf->sb_sum.cno = cno;
	return 0;
}