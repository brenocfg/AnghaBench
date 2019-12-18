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
struct TYPE_2__ {scalar_t__ nblocks; scalar_t__ nsumblk; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; } ;

/* Variables and functions */

__attribute__((used)) static inline int nilfs_segbuf_empty(struct nilfs_segment_buffer *segbuf)
{
	return segbuf->sb_sum.nblocks == segbuf->sb_sum.nsumblk;
}