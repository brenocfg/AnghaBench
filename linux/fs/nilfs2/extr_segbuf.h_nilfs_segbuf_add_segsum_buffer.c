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
struct TYPE_2__ {int /*<<< orphan*/  nsumblk; int /*<<< orphan*/  nblocks; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; int /*<<< orphan*/  sb_segsum_buffers; } ;
struct buffer_head {int /*<<< orphan*/  b_assoc_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
nilfs_segbuf_add_segsum_buffer(struct nilfs_segment_buffer *segbuf,
			       struct buffer_head *bh)
{
	list_add_tail(&bh->b_assoc_buffers, &segbuf->sb_segsum_buffers);
	segbuf->sb_sum.nblocks++;
	segbuf->sb_sum.nsumblk++;
}