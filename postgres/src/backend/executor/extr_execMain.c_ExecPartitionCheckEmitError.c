#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {scalar_t__ ri_RelationDesc; scalar_t__ ri_PartitionRoot; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CHECK_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 char* ExecBuildSlotValueDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetInsertedColumns (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUpdatedColumns (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeTupleTableSlot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelid (scalar_t__) ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/ * bms_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * convert_tuples_by_name_map_if_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * execute_attr_map_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecPartitionCheckEmitError(ResultRelInfo *resultRelInfo,
							TupleTableSlot *slot,
							EState *estate)
{
	Oid			root_relid;
	TupleDesc	tupdesc;
	char	   *val_desc;
	Bitmapset  *modifiedCols;

	/*
	 * If the tuple has been routed, it's been converted to the partition's
	 * rowtype, which might differ from the root table's.  We must convert it
	 * back to the root table's rowtype so that val_desc in the error message
	 * matches the input tuple.
	 */
	if (resultRelInfo->ri_PartitionRoot)
	{
		TupleDesc	old_tupdesc;
		AttrNumber *map;

		root_relid = RelationGetRelid(resultRelInfo->ri_PartitionRoot);
		tupdesc = RelationGetDescr(resultRelInfo->ri_PartitionRoot);

		old_tupdesc = RelationGetDescr(resultRelInfo->ri_RelationDesc);
		/* a reverse map */
		map = convert_tuples_by_name_map_if_req(old_tupdesc, tupdesc);

		/*
		 * Partition-specific slot's tupdesc can't be changed, so allocate a
		 * new one.
		 */
		if (map != NULL)
			slot = execute_attr_map_slot(map, slot,
										 MakeTupleTableSlot(tupdesc, &TTSOpsVirtual));
	}
	else
	{
		root_relid = RelationGetRelid(resultRelInfo->ri_RelationDesc);
		tupdesc = RelationGetDescr(resultRelInfo->ri_RelationDesc);
	}

	modifiedCols = bms_union(GetInsertedColumns(resultRelInfo, estate),
							 GetUpdatedColumns(resultRelInfo, estate));

	val_desc = ExecBuildSlotValueDescription(root_relid,
											 slot,
											 tupdesc,
											 modifiedCols,
											 64);
	ereport(ERROR,
			(errcode(ERRCODE_CHECK_VIOLATION),
			 errmsg("new row for relation \"%s\" violates partition constraint",
					RelationGetRelationName(resultRelInfo->ri_RelationDesc)),
			 val_desc ? errdetail("Failing row contains %s.", val_desc) : 0));
}