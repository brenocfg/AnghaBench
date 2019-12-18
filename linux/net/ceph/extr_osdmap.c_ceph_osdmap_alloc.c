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
struct ceph_osdmap {int pool_max; int /*<<< orphan*/  crush_workspace_mutex; void* pg_upmap_items; void* pg_upmap; void* primary_temp; void* pg_temp; void* pg_pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 void* RB_ROOT ; 
 struct ceph_osdmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct ceph_osdmap *ceph_osdmap_alloc(void)
{
	struct ceph_osdmap *map;

	map = kzalloc(sizeof(*map), GFP_NOIO);
	if (!map)
		return NULL;

	map->pg_pools = RB_ROOT;
	map->pool_max = -1;
	map->pg_temp = RB_ROOT;
	map->primary_temp = RB_ROOT;
	map->pg_upmap = RB_ROOT;
	map->pg_upmap_items = RB_ROOT;
	mutex_init(&map->crush_workspace_mutex);

	return map;
}