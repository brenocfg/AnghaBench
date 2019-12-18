#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num_mappings; } ;
struct TYPE_7__ {scalar_t__ num_mappings; } ;
struct TYPE_6__ {scalar_t__ num_mappings; } ;
struct TYPE_5__ {scalar_t__ num_mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatabasePath ; 
 int /*<<< orphan*/  GLOBALTABLESPACE_OID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  MyDatabaseTableSpace ; 
 TYPE_4__ active_local_updates ; 
 TYPE_3__ active_shared_updates ; 
 int /*<<< orphan*/  local_map ; 
 TYPE_2__ pending_local_updates ; 
 TYPE_1__ pending_shared_updates ; 
 int /*<<< orphan*/  shared_map ; 
 int /*<<< orphan*/  write_relmap_file (int,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
RelationMapFinishBootstrap(void)
{
	Assert(IsBootstrapProcessingMode());

	/* Shouldn't be anything "pending" ... */
	Assert(active_shared_updates.num_mappings == 0);
	Assert(active_local_updates.num_mappings == 0);
	Assert(pending_shared_updates.num_mappings == 0);
	Assert(pending_local_updates.num_mappings == 0);

	/* Write the files; no WAL or sinval needed */
	write_relmap_file(true, &shared_map, false, false, false,
					  InvalidOid, GLOBALTABLESPACE_OID, NULL);
	write_relmap_file(false, &local_map, false, false, false,
					  MyDatabaseId, MyDatabaseTableSpace, DatabasePath);
}