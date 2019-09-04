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
struct uid_gid_map {unsigned int nr_extents; } ;
struct uid_gid_extent {scalar_t__ lower_first; scalar_t__ first; } ;

/* Variables and functions */
 unsigned int UID_GID_MAP_MAX_BASE_EXTENTS ; 
 struct uid_gid_extent* map_id_range_down_base (unsigned int,struct uid_gid_map*,scalar_t__,scalar_t__) ; 
 struct uid_gid_extent* map_id_range_down_max (unsigned int,struct uid_gid_map*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static u32 map_id_range_down(struct uid_gid_map *map, u32 id, u32 count)
{
	struct uid_gid_extent *extent;
	unsigned extents = map->nr_extents;
	smp_rmb();

	if (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		extent = map_id_range_down_base(extents, map, id, count);
	else
		extent = map_id_range_down_max(extents, map, id, count);

	/* Map the id or note failure */
	if (extent)
		id = (id - extent->first) + extent->lower_first;
	else
		id = (u32) -1;

	return id;
}