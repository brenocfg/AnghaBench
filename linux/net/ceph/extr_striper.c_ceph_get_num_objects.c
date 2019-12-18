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
struct ceph_file_layout {int stripe_count; int object_size; int stripe_unit; } ;

/* Variables and functions */
 int DIV64_U64_ROUND_UP (int,int) ; 
 int DIV_ROUND_UP_ULL (int,int) ; 
 int /*<<< orphan*/  div64_u64_rem (int,int,int*) ; 

u64 ceph_get_num_objects(struct ceph_file_layout *l, u64 size)
{
	u64 period = (u64)l->stripe_count * l->object_size;
	u64 num_periods = DIV64_U64_ROUND_UP(size, period);
	u64 remainder_bytes;
	u64 remainder_objs = 0;

	div64_u64_rem(size, period, &remainder_bytes);
	if (remainder_bytes > 0 &&
	    remainder_bytes < (u64)l->stripe_count * l->stripe_unit)
		remainder_objs = l->stripe_count -
			    DIV_ROUND_UP_ULL(remainder_bytes, l->stripe_unit);

	return num_periods * l->stripe_count - remainder_objs;
}