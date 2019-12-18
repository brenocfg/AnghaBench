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
struct TYPE_2__ {int /*<<< orphan*/  nblocks; } ;
struct nilfs_segment_buffer {scalar_t__ sb_nbio; scalar_t__ sb_segnum; TYPE_1__ sb_sum; scalar_t__ sb_pseg_start; int /*<<< orphan*/  sb_super; int /*<<< orphan*/  sb_err; int /*<<< orphan*/  sb_bio_event; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_segbuf_wait(struct nilfs_segment_buffer *segbuf)
{
	int err = 0;

	if (!segbuf->sb_nbio)
		return 0;

	do {
		wait_for_completion(&segbuf->sb_bio_event);
	} while (--segbuf->sb_nbio > 0);

	if (unlikely(atomic_read(&segbuf->sb_err) > 0)) {
		nilfs_msg(segbuf->sb_super, KERN_ERR,
			  "I/O error writing log (start-blocknr=%llu, block-count=%lu) in segment %llu",
			  (unsigned long long)segbuf->sb_pseg_start,
			  segbuf->sb_sum.nblocks,
			  (unsigned long long)segbuf->sb_segnum);
		err = -EIO;
	}
	return err;
}