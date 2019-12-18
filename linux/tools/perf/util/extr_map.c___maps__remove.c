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
struct maps {int /*<<< orphan*/  names; int /*<<< orphan*/  entries; } ;
struct map {int /*<<< orphan*/  rb_node_name; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  map__put (struct map*) ; 
 int /*<<< orphan*/  rb_erase_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __maps__remove(struct maps *maps, struct map *map)
{
	rb_erase_init(&map->rb_node, &maps->entries);
	map__put(map);

	rb_erase_init(&map->rb_node_name, &maps->names);
	map__put(map);
}