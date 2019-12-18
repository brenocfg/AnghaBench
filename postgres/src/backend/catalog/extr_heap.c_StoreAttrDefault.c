#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valuesAtt ;
typedef  int /*<<< orphan*/  replacesAtt ;
typedef  int /*<<< orphan*/  nullsAtt ;
struct TYPE_29__ {char attgenerated; int /*<<< orphan*/  attalign; int /*<<< orphan*/  attbyval; int /*<<< orphan*/  attlen; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  atthasdef; } ;
struct TYPE_28__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_27__ {void* objectSubId; void* objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_26__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  EState ;
typedef  int Datum ;
typedef  void* AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int Anum_pg_attrdef_adbin ; 
 int Anum_pg_attrdef_adnum ; 
 int Anum_pg_attrdef_adrelid ; 
 int Anum_pg_attrdef_oid ; 
 int Anum_pg_attribute_atthasdef ; 
 int Anum_pg_attribute_atthasmissing ; 
 int Anum_pg_attribute_attmissingval ; 
 int /*<<< orphan*/  AttrDefaultOidIndexId ; 
 int /*<<< orphan*/  AttrDefaultRelationId ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * CreateExecutorState () ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 char* DatumGetPointer (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int ExecEvalExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * ExecPrepareExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 void* GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/  Int16GetDatum (void*) ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHookArg (int /*<<< orphan*/ ,void*,void*,int) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int Natts_pg_attribute ; 
 int ObjectIdGetDatum (void*) ; 
 int PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_1__*) ; 
 void* RelationGetRelid (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_3__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  construct_array (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int /*<<< orphan*/ * expression_planner (int /*<<< orphan*/ *) ; 
 TYPE_3__* heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 
 TYPE_3__* heap_modify_tuple (TYPE_3__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 char* nodeToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnSingleRelExpr (TYPE_2__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
StoreAttrDefault(Relation rel, AttrNumber attnum,
				 Node *expr, bool is_internal, bool add_column_mode)
{
	char	   *adbin;
	Relation	adrel;
	HeapTuple	tuple;
	Datum		values[4];
	static bool nulls[4] = {false, false, false, false};
	Relation	attrrel;
	HeapTuple	atttup;
	Form_pg_attribute attStruct;
	char		attgenerated;
	Oid			attrdefOid;
	ObjectAddress colobject,
				defobject;

	adrel = table_open(AttrDefaultRelationId, RowExclusiveLock);

	/*
	 * Flatten expression to string form for storage.
	 */
	adbin = nodeToString(expr);

	/*
	 * Make the pg_attrdef entry.
	 */
	attrdefOid = GetNewOidWithIndex(adrel, AttrDefaultOidIndexId,
									Anum_pg_attrdef_oid);
	values[Anum_pg_attrdef_oid - 1] = ObjectIdGetDatum(attrdefOid);
	values[Anum_pg_attrdef_adrelid - 1] = RelationGetRelid(rel);
	values[Anum_pg_attrdef_adnum - 1] = attnum;
	values[Anum_pg_attrdef_adbin - 1] = CStringGetTextDatum(adbin);

	tuple = heap_form_tuple(adrel->rd_att, values, nulls);
	CatalogTupleInsert(adrel, tuple);

	defobject.classId = AttrDefaultRelationId;
	defobject.objectId = attrdefOid;
	defobject.objectSubId = 0;

	table_close(adrel, RowExclusiveLock);

	/* now can free some of the stuff allocated above */
	pfree(DatumGetPointer(values[Anum_pg_attrdef_adbin - 1]));
	heap_freetuple(tuple);
	pfree(adbin);

	/*
	 * Update the pg_attribute entry for the column to show that a default
	 * exists.
	 */
	attrrel = table_open(AttributeRelationId, RowExclusiveLock);
	atttup = SearchSysCacheCopy2(ATTNUM,
								 ObjectIdGetDatum(RelationGetRelid(rel)),
								 Int16GetDatum(attnum));
	if (!HeapTupleIsValid(atttup))
		elog(ERROR, "cache lookup failed for attribute %d of relation %u",
			 attnum, RelationGetRelid(rel));
	attStruct = (Form_pg_attribute) GETSTRUCT(atttup);
	attgenerated = attStruct->attgenerated;
	if (!attStruct->atthasdef)
	{
		Form_pg_attribute defAttStruct;

		ExprState  *exprState;
		Expr	   *expr2 = (Expr *) expr;
		EState	   *estate = NULL;
		ExprContext *econtext;
		Datum		valuesAtt[Natts_pg_attribute];
		bool		nullsAtt[Natts_pg_attribute];
		bool		replacesAtt[Natts_pg_attribute];
		Datum		missingval = (Datum) 0;
		bool		missingIsNull = true;

		MemSet(valuesAtt, 0, sizeof(valuesAtt));
		MemSet(nullsAtt, false, sizeof(nullsAtt));
		MemSet(replacesAtt, false, sizeof(replacesAtt));
		valuesAtt[Anum_pg_attribute_atthasdef - 1] = true;
		replacesAtt[Anum_pg_attribute_atthasdef - 1] = true;

		if (add_column_mode && !attgenerated)
		{
			expr2 = expression_planner(expr2);
			estate = CreateExecutorState();
			exprState = ExecPrepareExpr(expr2, estate);
			econtext = GetPerTupleExprContext(estate);

			missingval = ExecEvalExpr(exprState, econtext,
									  &missingIsNull);

			FreeExecutorState(estate);

			defAttStruct = TupleDescAttr(rel->rd_att, attnum - 1);

			if (missingIsNull)
			{
				/* if the default evaluates to NULL, just store a NULL array */
				missingval = (Datum) 0;
			}
			else
			{
				/* otherwise make a one-element array of the value */
				missingval = PointerGetDatum(
											 construct_array(&missingval,
															 1,
															 defAttStruct->atttypid,
															 defAttStruct->attlen,
															 defAttStruct->attbyval,
															 defAttStruct->attalign));
			}

			valuesAtt[Anum_pg_attribute_atthasmissing - 1] = !missingIsNull;
			replacesAtt[Anum_pg_attribute_atthasmissing - 1] = true;
			valuesAtt[Anum_pg_attribute_attmissingval - 1] = missingval;
			replacesAtt[Anum_pg_attribute_attmissingval - 1] = true;
			nullsAtt[Anum_pg_attribute_attmissingval - 1] = missingIsNull;
		}
		atttup = heap_modify_tuple(atttup, RelationGetDescr(attrrel),
								   valuesAtt, nullsAtt, replacesAtt);

		CatalogTupleUpdate(attrrel, &atttup->t_self, atttup);

		if (!missingIsNull)
			pfree(DatumGetPointer(missingval));

	}
	table_close(attrrel, RowExclusiveLock);
	heap_freetuple(atttup);

	/*
	 * Make a dependency so that the pg_attrdef entry goes away if the column
	 * (or whole table) is deleted.
	 */
	colobject.classId = RelationRelationId;
	colobject.objectId = RelationGetRelid(rel);
	colobject.objectSubId = attnum;

	recordDependencyOn(&defobject, &colobject, DEPENDENCY_AUTO);

	/*
	 * Record dependencies on objects used in the expression, too.
	 */
	if (attgenerated)
	{
		/*
		 * Generated column: Dropping anything that the generation expression
		 * refers to automatically drops the generated column.
		 */
		recordDependencyOnSingleRelExpr(&colobject, expr, RelationGetRelid(rel),
										DEPENDENCY_AUTO,
										DEPENDENCY_AUTO, false);
	}
	else
	{
		/*
		 * Normal default: Dropping anything that the default refers to
		 * requires CASCADE and drops the default only.
		 */
		recordDependencyOnSingleRelExpr(&defobject, expr, RelationGetRelid(rel),
										DEPENDENCY_NORMAL,
										DEPENDENCY_NORMAL, false);
	}

	/*
	 * Post creation hook for attribute defaults.
	 *
	 * XXX. ALTER TABLE ALTER COLUMN SET/DROP DEFAULT is implemented with a
	 * couple of deletion/creation of the attribute's default entry, so the
	 * callee should check existence of an older version of this entry if it
	 * needs to distinguish.
	 */
	InvokeObjectPostCreateHookArg(AttrDefaultRelationId,
								  RelationGetRelid(rel), attnum, is_internal);

	return attrdefOid;
}