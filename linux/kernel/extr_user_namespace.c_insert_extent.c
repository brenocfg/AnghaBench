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
struct uid_gid_map {int nr_extents; struct uid_gid_extent* forward; struct uid_gid_extent* extent; int /*<<< orphan*/ * reverse; } ;
struct uid_gid_extent {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UID_GID_MAP_MAX_BASE_EXTENTS ; 
 int /*<<< orphan*/  UID_GID_MAP_MAX_EXTENTS ; 
 struct uid_gid_extent* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct uid_gid_extent*,struct uid_gid_extent*,int) ; 

__attribute__((used)) static int insert_extent(struct uid_gid_map *map, struct uid_gid_extent *extent)
{
	struct uid_gid_extent *dest;

	if (map->nr_extents == UID_GID_MAP_MAX_BASE_EXTENTS) {
		struct uid_gid_extent *forward;

		/* Allocate memory for 340 mappings. */
		forward = kmalloc_array(UID_GID_MAP_MAX_EXTENTS,
					sizeof(struct uid_gid_extent),
					GFP_KERNEL);
		if (!forward)
			return -ENOMEM;

		/* Copy over memory. Only set up memory for the forward pointer.
		 * Defer the memory setup for the reverse pointer.
		 */
		memcpy(forward, map->extent,
		       map->nr_extents * sizeof(map->extent[0]));

		map->forward = forward;
		map->reverse = NULL;
	}

	if (map->nr_extents < UID_GID_MAP_MAX_BASE_EXTENTS)
		dest = &map->extent[map->nr_extents];
	else
		dest = &map->forward[map->nr_extents];

	*dest = *extent;
	map->nr_extents++;
	return 0;
}