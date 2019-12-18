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
struct btf_dedup {int hypot_cnt; int hypot_cap; size_t* hypot_list; size_t* hypot_map; } ;
typedef  size_t __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ max (int,int) ; 
 size_t* realloc (size_t*,int) ; 

__attribute__((used)) static int btf_dedup_hypot_map_add(struct btf_dedup *d,
				   __u32 from_id, __u32 to_id)
{
	if (d->hypot_cnt == d->hypot_cap) {
		__u32 *new_list;

		d->hypot_cap += max(16, d->hypot_cap / 2);
		new_list = realloc(d->hypot_list, sizeof(__u32) * d->hypot_cap);
		if (!new_list)
			return -ENOMEM;
		d->hypot_list = new_list;
	}
	d->hypot_list[d->hypot_cnt++] = from_id;
	d->hypot_map[from_id] = to_id;
	return 0;
}