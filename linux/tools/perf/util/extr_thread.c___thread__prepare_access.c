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
struct thread {TYPE_1__* mg; } ;
struct maps {int /*<<< orphan*/  lock; } ;
struct map {int dummy; } ;
struct TYPE_2__ {struct maps maps; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct map* map__next (struct map*) ; 
 struct map* maps__first (struct maps*) ; 
 int unwind__prepare_access (TYPE_1__*,struct map*,int*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __thread__prepare_access(struct thread *thread)
{
	bool initialized = false;
	int err = 0;
	struct maps *maps = &thread->mg->maps;
	struct map *map;

	down_read(&maps->lock);

	for (map = maps__first(maps); map; map = map__next(map)) {
		err = unwind__prepare_access(thread->mg, map, &initialized);
		if (err || initialized)
			break;
	}

	up_read(&maps->lock);

	return err;
}