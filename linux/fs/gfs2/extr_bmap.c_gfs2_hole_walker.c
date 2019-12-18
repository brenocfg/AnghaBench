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
struct metapath {int mp_aheight; int* mp_list; int mp_fheight; } ;
typedef  enum walker_status { ____Placeholder_walker_status } walker_status ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int WALK_CONTINUE ; 
 int WALK_FOLLOW ; 
 int WALK_STOP ; 
 scalar_t__* metapointer (unsigned int,struct metapath*) ; 

__attribute__((used)) static enum walker_status gfs2_hole_walker(struct metapath *mp,
					   unsigned int ptrs)
{
	const __be64 *start, *ptr, *end;
	unsigned int hgt;

	hgt = mp->mp_aheight - 1;
	start = metapointer(hgt, mp);
	end = start + ptrs;

	for (ptr = start; ptr < end; ptr++) {
		if (*ptr) {
			mp->mp_list[hgt] += ptr - start;
			if (mp->mp_aheight == mp->mp_fheight)
				return WALK_STOP;
			return WALK_FOLLOW;
		}
	}
	return WALK_CONTINUE;
}