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
typedef  size_t u16 ;
struct selinux_map {size_t size; TYPE_1__* mapping; } ;
struct TYPE_2__ {size_t value; } ;

/* Variables and functions */
 size_t SECCLASS_NULL ; 

__attribute__((used)) static u16 map_class(struct selinux_map *map, u16 pol_value)
{
	u16 i;

	for (i = 1; i < map->size; i++) {
		if (map->mapping[i].value == pol_value)
			return i;
	}

	return SECCLASS_NULL;
}