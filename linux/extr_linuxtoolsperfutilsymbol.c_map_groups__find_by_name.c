#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct maps {int /*<<< orphan*/  lock; } ;
struct map_groups {struct maps maps; } ;
struct map {TYPE_1__* dso; } ;
struct TYPE_2__ {int /*<<< orphan*/  short_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct map* map__next (struct map*) ; 
 struct map* maps__first (struct maps*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct map *map_groups__find_by_name(struct map_groups *mg, const char *name)
{
	struct maps *maps = &mg->maps;
	struct map *map;

	down_read(&maps->lock);

	for (map = maps__first(maps); map; map = map__next(map)) {
		if (map->dso && strcmp(map->dso->short_name, name) == 0)
			goto out_unlock;
	}

	map = NULL;

out_unlock:
	up_read(&maps->lock);
	return map;
}