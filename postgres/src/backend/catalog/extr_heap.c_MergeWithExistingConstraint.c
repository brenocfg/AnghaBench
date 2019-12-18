#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ contype; int conislocal; int connoinherit; int coninhcount; int /*<<< orphan*/  convalidated; } ;
struct TYPE_21__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_20__ {TYPE_1__* rd_rel; int /*<<< orphan*/  rd_att; } ;
struct TYPE_19__ {scalar_t__ relispartition; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_constraint_conbin ; 
 int /*<<< orphan*/  Anum_pg_constraint_conname ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  Anum_pg_constraint_contypid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_CHECK ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  fastgetattr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* heap_copytuple (TYPE_3__*) ; 
 int /*<<< orphan*/  stringToNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_3__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
MergeWithExistingConstraint(Relation rel, const char *ccname, Node *expr,
							bool allow_merge, bool is_local,
							bool is_initially_valid,
							bool is_no_inherit)
{
	bool		found;
	Relation	conDesc;
	SysScanDesc conscan;
	ScanKeyData skey[3];
	HeapTuple	tup;

	/* Search for a pg_constraint entry with same name and relation */
	conDesc = table_open(ConstraintRelationId, RowExclusiveLock);

	found = false;

	ScanKeyInit(&skey[0],
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(RelationGetRelid(rel)));
	ScanKeyInit(&skey[1],
				Anum_pg_constraint_contypid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(InvalidOid));
	ScanKeyInit(&skey[2],
				Anum_pg_constraint_conname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(ccname));

	conscan = systable_beginscan(conDesc, ConstraintRelidTypidNameIndexId, true,
								 NULL, 3, skey);

	/* There can be at most one matching row */
	if (HeapTupleIsValid(tup = systable_getnext(conscan)))
	{
		Form_pg_constraint con = (Form_pg_constraint) GETSTRUCT(tup);

		/* Found it.  Conflicts if not identical check constraint */
		if (con->contype == CONSTRAINT_CHECK)
		{
			Datum		val;
			bool		isnull;

			val = fastgetattr(tup,
							  Anum_pg_constraint_conbin,
							  conDesc->rd_att, &isnull);
			if (isnull)
				elog(ERROR, "null conbin for rel %s",
					 RelationGetRelationName(rel));
			if (equal(expr, stringToNode(TextDatumGetCString(val))))
				found = true;
		}

		/*
		 * If the existing constraint is purely inherited (no local
		 * definition) then interpret addition of a local constraint as a
		 * legal merge.  This allows ALTER ADD CONSTRAINT on parent and child
		 * tables to be given in either order with same end state.  However if
		 * the relation is a partition, all inherited constraints are always
		 * non-local, including those that were merged.
		 */
		if (is_local && !con->conislocal && !rel->rd_rel->relispartition)
			allow_merge = true;

		if (!found || !allow_merge)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("constraint \"%s\" for relation \"%s\" already exists",
							ccname, RelationGetRelationName(rel))));

		/* If the child constraint is "no inherit" then cannot merge */
		if (con->connoinherit)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("constraint \"%s\" conflicts with non-inherited constraint on relation \"%s\"",
							ccname, RelationGetRelationName(rel))));

		/*
		 * Must not change an existing inherited constraint to "no inherit"
		 * status.  That's because inherited constraints should be able to
		 * propagate to lower-level children.
		 */
		if (con->coninhcount > 0 && is_no_inherit)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("constraint \"%s\" conflicts with inherited constraint on relation \"%s\"",
							ccname, RelationGetRelationName(rel))));

		/*
		 * If the child constraint is "not valid" then cannot merge with a
		 * valid parent constraint.
		 */
		if (is_initially_valid && !con->convalidated)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
					 errmsg("constraint \"%s\" conflicts with NOT VALID constraint on relation \"%s\"",
							ccname, RelationGetRelationName(rel))));

		/* OK to update the tuple */
		ereport(NOTICE,
				(errmsg("merging constraint \"%s\" with inherited definition",
						ccname)));

		tup = heap_copytuple(tup);
		con = (Form_pg_constraint) GETSTRUCT(tup);

		/*
		 * In case of partitions, an inherited constraint must be inherited
		 * only once since it cannot have multiple parents and it is never
		 * considered local.
		 */
		if (rel->rd_rel->relispartition)
		{
			con->coninhcount = 1;
			con->conislocal = false;
		}
		else
		{
			if (is_local)
				con->conislocal = true;
			else
				con->coninhcount++;
		}

		if (is_no_inherit)
		{
			Assert(is_local);
			con->connoinherit = true;
		}

		CatalogTupleUpdate(conDesc, &tup->t_self, tup);
	}

	systable_endscan(conscan);
	table_close(conDesc, RowExclusiveLock);

	return found;
}