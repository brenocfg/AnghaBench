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
struct map {int /*<<< orphan*/ * groups; int /*<<< orphan*/  dso; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dso__get (int /*<<< orphan*/ ) ; 
 struct map* memdup (struct map*,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

struct map *map__clone(struct map *from)
{
	struct map *map = memdup(from, sizeof(*map));

	if (map != NULL) {
		refcount_set(&map->refcnt, 1);
		RB_CLEAR_NODE(&map->rb_node);
		dso__get(map->dso);
		map->groups = NULL;
	}

	return map;
}