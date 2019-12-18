#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tracing_map_sort_entry {TYPE_2__* elt; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {TYPE_1__* map; } ;
struct TYPE_3__ {int /*<<< orphan*/  key_size; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_entries_dup(const struct tracing_map_sort_entry **a,
			   const struct tracing_map_sort_entry **b)
{
	int ret = 0;

	if (memcmp((*a)->key, (*b)->key, (*a)->elt->map->key_size))
		ret = 1;

	return ret;
}