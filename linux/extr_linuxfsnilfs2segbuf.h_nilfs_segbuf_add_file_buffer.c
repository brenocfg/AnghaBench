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
struct TYPE_2__ {int /*<<< orphan*/  nfileblk; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_segbuf_add_payload_buffer (struct nilfs_segment_buffer*,struct buffer_head*) ; 

__attribute__((used)) static inline void
nilfs_segbuf_add_file_buffer(struct nilfs_segment_buffer *segbuf,
			     struct buffer_head *bh)
{
	get_bh(bh);
	nilfs_segbuf_add_payload_buffer(segbuf, bh);
	segbuf->sb_sum.nfileblk++;
}