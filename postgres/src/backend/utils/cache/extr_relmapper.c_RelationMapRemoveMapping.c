#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32 ;
struct TYPE_5__ {size_t num_mappings; TYPE_1__* mappings; } ;
struct TYPE_4__ {scalar_t__ mapoid; } ;
typedef  TYPE_2__ RelMapFile ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__ active_local_updates ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
RelationMapRemoveMapping(Oid relationId)
{
	RelMapFile *map = &active_local_updates;
	int32		i;

	for (i = 0; i < map->num_mappings; i++)
	{
		if (relationId == map->mappings[i].mapoid)
		{
			/* Found it, collapse it out */
			map->mappings[i] = map->mappings[map->num_mappings - 1];
			map->num_mappings--;
			return;
		}
	}
	elog(ERROR, "could not find temporary mapping for relation %u",
		 relationId);
}