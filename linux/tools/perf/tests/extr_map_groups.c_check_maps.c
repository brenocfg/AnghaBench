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
struct map_groups {int dummy; } ;
struct map_def {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  name; } ;
struct map {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  refcnt; TYPE_1__* dso; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 int TEST_OK ; 
 struct map* map_groups__first (struct map_groups*) ; 
 struct map* map_groups__next (struct map*) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_maps(struct map_def *merged, unsigned int size, struct map_groups *mg)
{
	struct map *map;
	unsigned int i = 0;

	map = map_groups__first(mg);
	while (map) {
		TEST_ASSERT_VAL("wrong map start",  map->start == merged[i].start);
		TEST_ASSERT_VAL("wrong map end",    map->end == merged[i].end);
		TEST_ASSERT_VAL("wrong map name",  !strcmp(map->dso->name, merged[i].name));
		TEST_ASSERT_VAL("wrong map refcnt", refcount_read(&map->refcnt) == 2);

		i++;
		map = map_groups__next(map);

		TEST_ASSERT_VAL("less maps expected", (map && i < size) || (!map && i == size));
	}

	return TEST_OK;
}