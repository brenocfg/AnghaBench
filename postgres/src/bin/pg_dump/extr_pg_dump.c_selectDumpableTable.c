#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  oid; } ;
struct TYPE_15__ {void* dump; TYPE_3__ catId; TYPE_2__* namespace; } ;
struct TYPE_13__ {TYPE_9__ dobj; } ;
typedef  TYPE_4__ TableInfo ;
struct TYPE_14__ {int /*<<< orphan*/ * head; } ;
struct TYPE_10__ {void* dump_contains; } ;
struct TYPE_11__ {TYPE_1__ dobj; } ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 void* DUMP_COMPONENT_ALL ; 
 void* DUMP_COMPONENT_NONE ; 
 scalar_t__ checkExtensionMembership (TYPE_9__*,int /*<<< orphan*/ *) ; 
 scalar_t__ simple_oid_list_member (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__ table_exclude_oids ; 
 TYPE_5__ table_include_oids ; 

__attribute__((used)) static void
selectDumpableTable(TableInfo *tbinfo, Archive *fout)
{
	if (checkExtensionMembership(&tbinfo->dobj, fout))
		return;					/* extension membership overrides all else */

	/*
	 * If specific tables are being dumped, dump just those tables; else, dump
	 * according to the parent namespace's dump flag.
	 */
	if (table_include_oids.head != NULL)
		tbinfo->dobj.dump = simple_oid_list_member(&table_include_oids,
												   tbinfo->dobj.catId.oid) ?
			DUMP_COMPONENT_ALL : DUMP_COMPONENT_NONE;
	else
		tbinfo->dobj.dump = tbinfo->dobj.namespace->dobj.dump_contains;

	/*
	 * In any case, a table can be excluded by an exclusion switch
	 */
	if (tbinfo->dobj.dump &&
		simple_oid_list_member(&table_exclude_oids,
							   tbinfo->dobj.catId.oid))
		tbinfo->dobj.dump = DUMP_COMPONENT_NONE;
}