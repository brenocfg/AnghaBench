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
struct uid_gid_map {int nr_extents; int /*<<< orphan*/  reverse; int /*<<< orphan*/  forward; } ;
struct uid_gid_extent {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UID_GID_MAP_MAX_BASE_EXTENTS ; 
 int /*<<< orphan*/  cmp_extents_forward ; 
 int /*<<< orphan*/  cmp_extents_reverse ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sort (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sort_idmaps(struct uid_gid_map *map)
{
	if (map->nr_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		return 0;

	/* Sort forward array. */
	sort(map->forward, map->nr_extents, sizeof(struct uid_gid_extent),
	     cmp_extents_forward, NULL);

	/* Only copy the memory from forward we actually need. */
	map->reverse = kmemdup(map->forward,
			       map->nr_extents * sizeof(struct uid_gid_extent),
			       GFP_KERNEL);
	if (!map->reverse)
		return -ENOMEM;

	/* Sort reverse array. */
	sort(map->reverse, map->nr_extents, sizeof(struct uid_gid_extent),
	     cmp_extents_reverse, NULL);

	return 0;
}