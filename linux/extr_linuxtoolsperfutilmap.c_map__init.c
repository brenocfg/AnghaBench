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
typedef  void* u64 ;
struct map {int erange_warned; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * groups; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  unmap_ip; int /*<<< orphan*/  map_ip; int /*<<< orphan*/  dso; scalar_t__ reloc; void* pgoff; void* end; void* start; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso__get (struct dso*) ; 
 int /*<<< orphan*/  map__map_ip ; 
 int /*<<< orphan*/  map__unmap_ip ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

void map__init(struct map *map, u64 start, u64 end, u64 pgoff, struct dso *dso)
{
	map->start    = start;
	map->end      = end;
	map->pgoff    = pgoff;
	map->reloc    = 0;
	map->dso      = dso__get(dso);
	map->map_ip   = map__map_ip;
	map->unmap_ip = map__unmap_ip;
	RB_CLEAR_NODE(&map->rb_node);
	map->groups   = NULL;
	map->erange_warned = false;
	refcount_set(&map->refcnt, 1);
}