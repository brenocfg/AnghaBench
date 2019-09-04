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
typedef  int u64 ;
struct metapath {scalar_t__ mp_aheight; scalar_t__ mp_fheight; } ;
struct gfs2_hole_walker_args {int blocks; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 scalar_t__ const* WALK_NEXT ; 
 scalar_t__ const* WALK_STOP ; 

__attribute__((used)) static const __be64 *gfs2_hole_walker(struct metapath *mp,
		const __be64 *start, const __be64 *end,
		u64 factor, void *data)
{
	struct gfs2_hole_walker_args *args = data;
	const __be64 *ptr;

	for (ptr = start; ptr < end; ptr++) {
		if (*ptr) {
			args->blocks += (ptr - start) * factor;
			if (mp->mp_aheight == mp->mp_fheight)
				return WALK_STOP;
			return ptr;  /* increase height */
		}
	}
	args->blocks += (end - start) * factor;
	return WALK_NEXT;
}