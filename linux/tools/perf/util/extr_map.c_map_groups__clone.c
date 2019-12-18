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
struct thread {struct map_groups* mg; } ;
struct maps {int /*<<< orphan*/  lock; } ;
struct map_groups {struct maps maps; } ;
struct map {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct map* map__clone (struct map*) ; 
 struct map* map__next (struct map*) ; 
 int /*<<< orphan*/  map__put (struct map*) ; 
 int /*<<< orphan*/  map_groups__insert (struct map_groups*,struct map*) ; 
 struct map* maps__first (struct maps*) ; 
 int unwind__prepare_access (struct map_groups*,struct map*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int map_groups__clone(struct thread *thread, struct map_groups *parent)
{
	struct map_groups *mg = thread->mg;
	int err = -ENOMEM;
	struct map *map;
	struct maps *maps = &parent->maps;

	down_read(&maps->lock);

	for (map = maps__first(maps); map; map = map__next(map)) {
		struct map *new = map__clone(map);
		if (new == NULL)
			goto out_unlock;

		err = unwind__prepare_access(mg, new, NULL);
		if (err)
			goto out_unlock;

		map_groups__insert(mg, new);
		map__put(new);
	}

	err = 0;
out_unlock:
	up_read(&maps->lock);
	return err;
}