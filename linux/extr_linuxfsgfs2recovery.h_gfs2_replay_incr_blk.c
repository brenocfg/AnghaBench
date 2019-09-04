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
struct gfs2_jdesc {unsigned int jd_blocks; } ;

/* Variables and functions */

__attribute__((used)) static inline void gfs2_replay_incr_blk(struct gfs2_jdesc *jd, unsigned int *blk)
{
	if (++*blk == jd->jd_blocks)
	        *blk = 0;
}