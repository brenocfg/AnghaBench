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
struct TYPE_2__ {unsigned int flags; } ;
struct nilfs_segment_buffer {TYPE_1__ sb_sum; } ;

/* Variables and functions */
 unsigned int NILFS_SS_LOGBGN ; 
 unsigned int NILFS_SS_LOGEND ; 

__attribute__((used)) static inline int nilfs_segbuf_simplex(struct nilfs_segment_buffer *segbuf)
{
	unsigned int flags = segbuf->sb_sum.flags;

	return (flags & (NILFS_SS_LOGBGN | NILFS_SS_LOGEND)) ==
		(NILFS_SS_LOGBGN | NILFS_SS_LOGEND);
}