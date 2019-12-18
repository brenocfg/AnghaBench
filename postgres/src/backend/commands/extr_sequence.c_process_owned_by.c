#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_14__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
struct TYPE_13__ {TYPE_1__* rd_rel; } ;
struct TYPE_12__ {scalar_t__ relkind; scalar_t__ relowner; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ DependencyType ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DEPENDENCY_AUTO ; 
 scalar_t__ DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELKIND_VIEW ; 
 scalar_t__ RelationGetNamespace (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 void* RelationGetRelid (TYPE_2__*) ; 
 void* RelationRelationId ; 
 int /*<<< orphan*/  deleteDependencyRecordsForClass (void*,void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_attnum (void*,char*) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_truncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * makeRangeVarFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_3__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_openrv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sequenceIsOwned (void*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strVal (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
process_owned_by(Relation seqrel, List *owned_by, bool for_identity)
{
	DependencyType deptype;
	int			nnames;
	Relation	tablerel;
	AttrNumber	attnum;

	deptype = for_identity ? DEPENDENCY_INTERNAL : DEPENDENCY_AUTO;

	nnames = list_length(owned_by);
	Assert(nnames > 0);
	if (nnames == 1)
	{
		/* Must be OWNED BY NONE */
		if (strcmp(strVal(linitial(owned_by)), "none") != 0)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("invalid OWNED BY option"),
					 errhint("Specify OWNED BY table.column or OWNED BY NONE.")));
		tablerel = NULL;
		attnum = 0;
	}
	else
	{
		List	   *relname;
		char	   *attrname;
		RangeVar   *rel;

		/* Separate relname and attr name */
		relname = list_truncate(list_copy(owned_by), nnames - 1);
		attrname = strVal(lfirst(list_tail(owned_by)));

		/* Open and lock rel to ensure it won't go away meanwhile */
		rel = makeRangeVarFromNameList(relname);
		tablerel = relation_openrv(rel, AccessShareLock);

		/* Must be a regular or foreign table */
		if (!(tablerel->rd_rel->relkind == RELKIND_RELATION ||
			  tablerel->rd_rel->relkind == RELKIND_FOREIGN_TABLE ||
			  tablerel->rd_rel->relkind == RELKIND_VIEW ||
			  tablerel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE))
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("referenced relation \"%s\" is not a table or foreign table",
							RelationGetRelationName(tablerel))));

		/* We insist on same owner and schema */
		if (seqrel->rd_rel->relowner != tablerel->rd_rel->relowner)
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("sequence must have same owner as table it is linked to")));
		if (RelationGetNamespace(seqrel) != RelationGetNamespace(tablerel))
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("sequence must be in same schema as table it is linked to")));

		/* Now, fetch the attribute number from the system cache */
		attnum = get_attnum(RelationGetRelid(tablerel), attrname);
		if (attnum == InvalidAttrNumber)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_COLUMN),
					 errmsg("column \"%s\" of relation \"%s\" does not exist",
							attrname, RelationGetRelationName(tablerel))));
	}

	/*
	 * Catch user explicitly running OWNED BY on identity sequence.
	 */
	if (deptype == DEPENDENCY_AUTO)
	{
		Oid			tableId;
		int32		colId;

		if (sequenceIsOwned(RelationGetRelid(seqrel), DEPENDENCY_INTERNAL, &tableId, &colId))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot change ownership of identity sequence"),
					 errdetail("Sequence \"%s\" is linked to table \"%s\".",
							   RelationGetRelationName(seqrel),
							   get_rel_name(tableId))));
	}

	/*
	 * OK, we are ready to update pg_depend.  First remove any existing
	 * dependencies for the sequence, then optionally add a new one.
	 */
	deleteDependencyRecordsForClass(RelationRelationId, RelationGetRelid(seqrel),
									RelationRelationId, deptype);

	if (tablerel)
	{
		ObjectAddress refobject,
					depobject;

		refobject.classId = RelationRelationId;
		refobject.objectId = RelationGetRelid(tablerel);
		refobject.objectSubId = attnum;
		depobject.classId = RelationRelationId;
		depobject.objectId = RelationGetRelid(seqrel);
		depobject.objectSubId = 0;
		recordDependencyOn(&depobject, &refobject, deptype);
	}

	/* Done, but hold lock until commit */
	if (tablerel)
		relation_close(tablerel, NoLock);
}