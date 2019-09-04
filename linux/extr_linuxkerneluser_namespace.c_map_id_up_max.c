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
typedef  int /*<<< orphan*/  u32 ;
struct uid_gid_map {int /*<<< orphan*/  reverse; } ;
struct uid_gid_extent {int dummy; } ;
struct idmap_key {int map_up; int count; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct uid_gid_extent* bsearch (struct idmap_key*,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_map_id ; 

__attribute__((used)) static struct uid_gid_extent *
map_id_up_max(unsigned extents, struct uid_gid_map *map, u32 id)
{
	struct idmap_key key;

	key.map_up = true;
	key.count = 1;
	key.id = id;

	return bsearch(&key, map->reverse, extents,
		       sizeof(struct uid_gid_extent), cmp_map_id);
}