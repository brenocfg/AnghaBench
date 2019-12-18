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
struct metapath {int* mp_list; struct buffer_head** mp_bh; } ;
struct gfs2_sbd {int dummy; } ;
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;
typedef  int __u16 ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 unsigned int GFS2_MAX_META_HEIGHT ; 
 scalar_t__* metaptr1 (unsigned int,struct metapath*) ; 
 scalar_t__ mp_eq_to_hgt (struct metapath*,int*,unsigned int) ; 

__attribute__((used)) static bool find_nonnull_ptr(struct gfs2_sbd *sdp, struct metapath *mp,
			     unsigned int h,
			     __u16 *end_list, unsigned int end_aligned)
{
	struct buffer_head *bh = mp->mp_bh[h];
	__be64 *first, *ptr, *end;

	first = metaptr1(h, mp);
	ptr = first + mp->mp_list[h];
	end = (__be64 *)(bh->b_data + bh->b_size);
	if (end_list && mp_eq_to_hgt(mp, end_list, h)) {
		bool keep_end = h < end_aligned;
		end = first + end_list[h] + keep_end;
	}

	while (ptr < end) {
		if (*ptr) { /* if we have a non-null pointer */
			mp->mp_list[h] = ptr - first;
			h++;
			if (h < GFS2_MAX_META_HEIGHT)
				mp->mp_list[h] = 0;
			return true;
		}
		ptr++;
	}
	return false;
}