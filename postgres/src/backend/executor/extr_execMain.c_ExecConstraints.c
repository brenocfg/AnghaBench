#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_17__ {scalar_t__ num_check; scalar_t__ has_not_null; } ;
typedef  TYPE_2__ TupleConstr ;
struct TYPE_19__ {int /*<<< orphan*/  attname; scalar_t__ attnotnull; } ;
struct TYPE_18__ {scalar_t__ ri_PartitionRoot; scalar_t__ ri_PartitionCheck; scalar_t__ ri_RelationDesc; } ;
struct TYPE_16__ {int natts; TYPE_2__* constr; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  scalar_t__ Relation ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_CHECK_VIOLATION ; 
 int /*<<< orphan*/  ERRCODE_NOT_NULL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 char* ExecBuildSlotValueDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 char* ExecRelCheck (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetInsertedColumns (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetUpdatedColumns (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeTupleTableSlot (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelid (scalar_t__) ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 TYPE_4__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * bms_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_tuples_by_name_map_if_req (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  errtablecol (scalar_t__,int) ; 
 int /*<<< orphan*/  errtableconstraint (scalar_t__,char const*) ; 
 int /*<<< orphan*/ * execute_attr_map_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ slot_attisnull (int /*<<< orphan*/ *,int) ; 

void
ExecConstraints(ResultRelInfo *resultRelInfo,
				TupleTableSlot *slot, EState *estate)
{
	Relation	rel = resultRelInfo->ri_RelationDesc;
	TupleDesc	tupdesc = RelationGetDescr(rel);
	TupleConstr *constr = tupdesc->constr;
	Bitmapset  *modifiedCols;
	Bitmapset  *insertedCols;
	Bitmapset  *updatedCols;

	Assert(constr || resultRelInfo->ri_PartitionCheck);

	if (constr && constr->has_not_null)
	{
		int			natts = tupdesc->natts;
		int			attrChk;

		for (attrChk = 1; attrChk <= natts; attrChk++)
		{
			Form_pg_attribute att = TupleDescAttr(tupdesc, attrChk - 1);

			if (att->attnotnull && slot_attisnull(slot, attrChk))
			{
				char	   *val_desc;
				Relation	orig_rel = rel;
				TupleDesc	orig_tupdesc = RelationGetDescr(rel);

				/*
				 * If the tuple has been routed, it's been converted to the
				 * partition's rowtype, which might differ from the root
				 * table's.  We must convert it back to the root table's
				 * rowtype so that val_desc shown error message matches the
				 * input tuple.
				 */
				if (resultRelInfo->ri_PartitionRoot)
				{
					AttrNumber *map;

					rel = resultRelInfo->ri_PartitionRoot;
					tupdesc = RelationGetDescr(rel);
					/* a reverse map */
					map = convert_tuples_by_name_map_if_req(orig_tupdesc,
															tupdesc);

					/*
					 * Partition-specific slot's tupdesc can't be changed, so
					 * allocate a new one.
					 */
					if (map != NULL)
						slot = execute_attr_map_slot(map, slot,
													 MakeTupleTableSlot(tupdesc, &TTSOpsVirtual));
				}

				insertedCols = GetInsertedColumns(resultRelInfo, estate);
				updatedCols = GetUpdatedColumns(resultRelInfo, estate);
				modifiedCols = bms_union(insertedCols, updatedCols);
				val_desc = ExecBuildSlotValueDescription(RelationGetRelid(rel),
														 slot,
														 tupdesc,
														 modifiedCols,
														 64);

				ereport(ERROR,
						(errcode(ERRCODE_NOT_NULL_VIOLATION),
						 errmsg("null value in column \"%s\" violates not-null constraint",
								NameStr(att->attname)),
						 val_desc ? errdetail("Failing row contains %s.", val_desc) : 0,
						 errtablecol(orig_rel, attrChk)));
			}
		}
	}

	if (constr && constr->num_check > 0)
	{
		const char *failed;

		if ((failed = ExecRelCheck(resultRelInfo, slot, estate)) != NULL)
		{
			char	   *val_desc;
			Relation	orig_rel = rel;

			/* See the comment above. */
			if (resultRelInfo->ri_PartitionRoot)
			{
				TupleDesc	old_tupdesc = RelationGetDescr(rel);
				AttrNumber *map;

				rel = resultRelInfo->ri_PartitionRoot;
				tupdesc = RelationGetDescr(rel);
				/* a reverse map */
				map = convert_tuples_by_name_map_if_req(old_tupdesc,
														tupdesc);

				/*
				 * Partition-specific slot's tupdesc can't be changed, so
				 * allocate a new one.
				 */
				if (map != NULL)
					slot = execute_attr_map_slot(map, slot,
												 MakeTupleTableSlot(tupdesc, &TTSOpsVirtual));
			}

			insertedCols = GetInsertedColumns(resultRelInfo, estate);
			updatedCols = GetUpdatedColumns(resultRelInfo, estate);
			modifiedCols = bms_union(insertedCols, updatedCols);
			val_desc = ExecBuildSlotValueDescription(RelationGetRelid(rel),
													 slot,
													 tupdesc,
													 modifiedCols,
													 64);
			ereport(ERROR,
					(errcode(ERRCODE_CHECK_VIOLATION),
					 errmsg("new row for relation \"%s\" violates check constraint \"%s\"",
							RelationGetRelationName(orig_rel), failed),
					 val_desc ? errdetail("Failing row contains %s.", val_desc) : 0,
					 errtableconstraint(orig_rel, failed)));
		}
	}
}