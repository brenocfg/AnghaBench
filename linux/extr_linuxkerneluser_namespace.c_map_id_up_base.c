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
typedef  scalar_t__ u32 ;
struct uid_gid_map {struct uid_gid_extent* extent; } ;
struct uid_gid_extent {scalar_t__ lower_first; scalar_t__ count; } ;

/* Variables and functions */

__attribute__((used)) static struct uid_gid_extent *
map_id_up_base(unsigned extents, struct uid_gid_map *map, u32 id)
{
	unsigned idx;
	u32 first, last;

	/* Find the matching extent */
	for (idx = 0; idx < extents; idx++) {
		first = map->extent[idx].lower_first;
		last = first + map->extent[idx].count - 1;
		if (id >= first && id <= last)
			return &map->extent[idx];
	}
	return NULL;
}