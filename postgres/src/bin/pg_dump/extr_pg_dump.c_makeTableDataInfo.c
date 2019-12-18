#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  oid; } ;
struct TYPE_13__ {int /*<<< orphan*/  dumpId; int /*<<< orphan*/  namespace; int /*<<< orphan*/  name; TYPE_2__ catId; } ;
struct TYPE_14__ {scalar_t__ relkind; scalar_t__ relpersistence; TYPE_5__* dataObj; TYPE_3__ dobj; } ;
typedef  TYPE_4__ TableInfo ;
struct TYPE_11__ {int /*<<< orphan*/  oid; scalar_t__ tableoid; } ;
struct TYPE_17__ {int /*<<< orphan*/  namespace; int /*<<< orphan*/  name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_15__ {TYPE_9__ dobj; int /*<<< orphan*/ * filtercond; TYPE_4__* tdtable; } ;
typedef  TYPE_5__ TableDataInfo ;
struct TYPE_16__ {scalar_t__ no_unlogged_table_data; } ;
typedef  TYPE_6__ DumpOptions ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_9__*) ; 
 int /*<<< orphan*/  DO_REFRESH_MATVIEW ; 
 int /*<<< orphan*/  DO_SEQUENCE_SET ; 
 int /*<<< orphan*/  DO_TABLE_DATA ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 scalar_t__ RELKIND_VIEW ; 
 scalar_t__ RELPERSISTENCE_UNLOGGED ; 
 int /*<<< orphan*/  addObjectDependency (TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ simple_oid_list_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tabledata_exclude_oids ; 

__attribute__((used)) static void
makeTableDataInfo(DumpOptions *dopt, TableInfo *tbinfo)
{
	TableDataInfo *tdinfo;

	/*
	 * Nothing to do if we already decided to dump the table.  This will
	 * happen for "config" tables.
	 */
	if (tbinfo->dataObj != NULL)
		return;

	/* Skip VIEWs (no data to dump) */
	if (tbinfo->relkind == RELKIND_VIEW)
		return;
	/* Skip FOREIGN TABLEs (no data to dump) */
	if (tbinfo->relkind == RELKIND_FOREIGN_TABLE)
		return;
	/* Skip partitioned tables (data in partitions) */
	if (tbinfo->relkind == RELKIND_PARTITIONED_TABLE)
		return;

	/* Don't dump data in unlogged tables, if so requested */
	if (tbinfo->relpersistence == RELPERSISTENCE_UNLOGGED &&
		dopt->no_unlogged_table_data)
		return;

	/* Check that the data is not explicitly excluded */
	if (simple_oid_list_member(&tabledata_exclude_oids,
							   tbinfo->dobj.catId.oid))
		return;

	/* OK, let's dump it */
	tdinfo = (TableDataInfo *) pg_malloc(sizeof(TableDataInfo));

	if (tbinfo->relkind == RELKIND_MATVIEW)
		tdinfo->dobj.objType = DO_REFRESH_MATVIEW;
	else if (tbinfo->relkind == RELKIND_SEQUENCE)
		tdinfo->dobj.objType = DO_SEQUENCE_SET;
	else
		tdinfo->dobj.objType = DO_TABLE_DATA;

	/*
	 * Note: use tableoid 0 so that this object won't be mistaken for
	 * something that pg_depend entries apply to.
	 */
	tdinfo->dobj.catId.tableoid = 0;
	tdinfo->dobj.catId.oid = tbinfo->dobj.catId.oid;
	AssignDumpId(&tdinfo->dobj);
	tdinfo->dobj.name = tbinfo->dobj.name;
	tdinfo->dobj.namespace = tbinfo->dobj.namespace;
	tdinfo->tdtable = tbinfo;
	tdinfo->filtercond = NULL;	/* might get set later */
	addObjectDependency(&tdinfo->dobj, tbinfo->dobj.dumpId);

	tbinfo->dataObj = tdinfo;
}