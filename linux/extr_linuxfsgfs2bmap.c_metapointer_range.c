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
struct metapath {struct buffer_head** mp_bh; } ;
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/ * metaptr1 (int,struct metapath*) ; 
 scalar_t__ mp_eq_to_hgt (struct metapath*,int*,int) ; 

__attribute__((used)) static inline void
metapointer_range(struct metapath *mp, int height,
		  __u16 *start_list, unsigned int start_aligned,
		  __u16 *end_list, unsigned int end_aligned,
		  __be64 **start, __be64 **end)
{
	struct buffer_head *bh = mp->mp_bh[height];
	__be64 *first;

	first = metaptr1(height, mp);
	*start = first;
	if (mp_eq_to_hgt(mp, start_list, height)) {
		bool keep_start = height < start_aligned;
		*start = first + start_list[height] + keep_start;
	}
	*end = (__be64 *)(bh->b_data + bh->b_size);
	if (end_list && mp_eq_to_hgt(mp, end_list, height)) {
		bool keep_end = height < end_aligned;
		*end = first + end_list[height] + keep_end;
	}
}