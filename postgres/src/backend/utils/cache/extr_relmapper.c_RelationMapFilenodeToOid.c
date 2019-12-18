#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32 ;
struct TYPE_8__ {size_t num_mappings; TYPE_1__* mappings; } ;
struct TYPE_7__ {scalar_t__ mapfilenode; scalar_t__ mapoid; } ;
typedef  TYPE_2__ RelMapFile ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 TYPE_2__ active_local_updates ; 
 TYPE_2__ active_shared_updates ; 
 TYPE_2__ local_map ; 
 TYPE_2__ shared_map ; 

Oid
RelationMapFilenodeToOid(Oid filenode, bool shared)
{
	const RelMapFile *map;
	int32		i;

	/* If there are active updates, believe those over the main maps */
	if (shared)
	{
		map = &active_shared_updates;
		for (i = 0; i < map->num_mappings; i++)
		{
			if (filenode == map->mappings[i].mapfilenode)
				return map->mappings[i].mapoid;
		}
		map = &shared_map;
		for (i = 0; i < map->num_mappings; i++)
		{
			if (filenode == map->mappings[i].mapfilenode)
				return map->mappings[i].mapoid;
		}
	}
	else
	{
		map = &active_local_updates;
		for (i = 0; i < map->num_mappings; i++)
		{
			if (filenode == map->mappings[i].mapfilenode)
				return map->mappings[i].mapoid;
		}
		map = &local_map;
		for (i = 0; i < map->num_mappings; i++)
		{
			if (filenode == map->mappings[i].mapfilenode)
				return map->mappings[i].mapoid;
		}
	}

	return InvalidOid;
}