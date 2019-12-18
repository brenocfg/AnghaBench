#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  isnull ;
struct TYPE_31__ {int /*<<< orphan*/ * qual; int /*<<< orphan*/ * with_check; int /*<<< orphan*/  policy_name; int /*<<< orphan*/  table; int /*<<< orphan*/ * roles; } ;
struct TYPE_30__ {void* oid; } ;
struct TYPE_29__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_28__ {scalar_t__ objectId; scalar_t__ objectSubId; int /*<<< orphan*/  classId; } ;
struct TYPE_27__ {int /*<<< orphan*/ * p_rtable; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ ParseState ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_policy ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  ArrayType ;
typedef  TYPE_5__ AlterPolicyStmt ;

/* Variables and functions */
 char ACL_DELETE_CHR ; 
 scalar_t__ ACL_ID_PUBLIC ; 
 char ACL_INSERT_CHR ; 
 char ACL_SELECT_CHR ; 
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int Anum_pg_policy_polcmd ; 
 int /*<<< orphan*/  Anum_pg_policy_polname ; 
 int Anum_pg_policy_polqual ; 
 int /*<<< orphan*/  Anum_pg_policy_polrelid ; 
 int Anum_pg_policy_polroles ; 
 int Anum_pg_policy_polwithcheck ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AuthIdRelationId ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int CStringGetDatum (int /*<<< orphan*/ ) ; 
 int CStringGetTextDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/ * DatumGetArrayTypePCopy (int) ; 
 char DatumGetChar (int) ; 
 scalar_t__ DatumGetObjectId (int) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_POLICY ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int Natts_pg_policy ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OIDOID ; 
 int ObjectIdGetDatum (void*) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PolicyPolrelidPolnameIndexId ; 
 int /*<<< orphan*/  PolicyRelationId ; 
 int /*<<< orphan*/  RangeVarCallbackForPolicy ; 
 void* RangeVarGetRelidExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SHARED_DEPENDENCY_POLICY ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* TextDatumGetCString (int) ; 
 int /*<<< orphan*/  addRTEtoQuery (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * addRangeTableEntryForRelation (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  assign_expr_collations (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * construct_array (int*,int,int /*<<< orphan*/ ,int,int,char) ; 
 int /*<<< orphan*/  copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deleteDependencyRecordsFor (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  deleteSharedDependencyRecordsFor (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  free_parsestate (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 
 int heap_getattr (TYPE_3__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* heap_modify_tuple (TYPE_3__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 TYPE_1__* make_parsestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nodeToString (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 int* policy_role_list_to_array (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnExpr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordSharedDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stringToNode (char*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_3__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformWhereClause (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ObjectAddress
AlterPolicy(AlterPolicyStmt *stmt)
{
	Relation	pg_policy_rel;
	Oid			policy_id;
	Relation	target_table;
	Oid			table_id;
	Datum	   *role_oids = NULL;
	int			nitems = 0;
	ArrayType  *role_ids = NULL;
	List	   *qual_parse_rtable = NIL;
	List	   *with_check_parse_rtable = NIL;
	Node	   *qual = NULL;
	Node	   *with_check_qual = NULL;
	ScanKeyData skey[2];
	SysScanDesc sscan;
	HeapTuple	policy_tuple;
	HeapTuple	new_tuple;
	Datum		values[Natts_pg_policy];
	bool		isnull[Natts_pg_policy];
	bool		replaces[Natts_pg_policy];
	ObjectAddress target;
	ObjectAddress myself;
	Datum		polcmd_datum;
	char		polcmd;
	bool		polcmd_isnull;
	int			i;

	/* Parse role_ids */
	if (stmt->roles != NULL)
	{
		role_oids = policy_role_list_to_array(stmt->roles, &nitems);
		role_ids = construct_array(role_oids, nitems, OIDOID,
								   sizeof(Oid), true, 'i');
	}

	/* Get id of table.  Also handles permissions checks. */
	table_id = RangeVarGetRelidExtended(stmt->table, AccessExclusiveLock,
										0,
										RangeVarCallbackForPolicy,
										(void *) stmt);

	target_table = relation_open(table_id, NoLock);

	/* Parse the using policy clause */
	if (stmt->qual)
	{
		RangeTblEntry *rte;
		ParseState *qual_pstate = make_parsestate(NULL);

		rte = addRangeTableEntryForRelation(qual_pstate, target_table,
											AccessShareLock,
											NULL, false, false);

		addRTEtoQuery(qual_pstate, rte, false, true, true);

		qual = transformWhereClause(qual_pstate, copyObject(stmt->qual),
									EXPR_KIND_POLICY,
									"POLICY");

		/* Fix up collation information */
		assign_expr_collations(qual_pstate, qual);

		qual_parse_rtable = qual_pstate->p_rtable;
		free_parsestate(qual_pstate);
	}

	/* Parse the with-check policy clause */
	if (stmt->with_check)
	{
		RangeTblEntry *rte;
		ParseState *with_check_pstate = make_parsestate(NULL);

		rte = addRangeTableEntryForRelation(with_check_pstate, target_table,
											AccessShareLock,
											NULL, false, false);

		addRTEtoQuery(with_check_pstate, rte, false, true, true);

		with_check_qual = transformWhereClause(with_check_pstate,
											   copyObject(stmt->with_check),
											   EXPR_KIND_POLICY,
											   "POLICY");

		/* Fix up collation information */
		assign_expr_collations(with_check_pstate, with_check_qual);

		with_check_parse_rtable = with_check_pstate->p_rtable;
		free_parsestate(with_check_pstate);
	}

	/* zero-clear */
	memset(values, 0, sizeof(values));
	memset(replaces, 0, sizeof(replaces));
	memset(isnull, 0, sizeof(isnull));

	/* Find policy to update. */
	pg_policy_rel = table_open(PolicyRelationId, RowExclusiveLock);

	/* Set key - policy's relation id. */
	ScanKeyInit(&skey[0],
				Anum_pg_policy_polrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(table_id));

	/* Set key - policy's name. */
	ScanKeyInit(&skey[1],
				Anum_pg_policy_polname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(stmt->policy_name));

	sscan = systable_beginscan(pg_policy_rel,
							   PolicyPolrelidPolnameIndexId, true, NULL, 2,
							   skey);

	policy_tuple = systable_getnext(sscan);

	/* Check that the policy is found, raise an error if not. */
	if (!HeapTupleIsValid(policy_tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("policy \"%s\" for table \"%s\" does not exist",
						stmt->policy_name,
						RelationGetRelationName(target_table))));

	/* Get policy command */
	polcmd_datum = heap_getattr(policy_tuple, Anum_pg_policy_polcmd,
								RelationGetDescr(pg_policy_rel),
								&polcmd_isnull);
	Assert(!polcmd_isnull);
	polcmd = DatumGetChar(polcmd_datum);

	/*
	 * If the command is SELECT or DELETE then WITH CHECK should be NULL.
	 */
	if ((polcmd == ACL_SELECT_CHR || polcmd == ACL_DELETE_CHR)
		&& stmt->with_check != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("only USING expression allowed for SELECT, DELETE")));

	/*
	 * If the command is INSERT then WITH CHECK should be the only expression
	 * provided.
	 */
	if ((polcmd == ACL_INSERT_CHR)
		&& stmt->qual != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("only WITH CHECK expression allowed for INSERT")));

	policy_id = ((Form_pg_policy) GETSTRUCT(policy_tuple))->oid;

	if (role_ids != NULL)
	{
		replaces[Anum_pg_policy_polroles - 1] = true;
		values[Anum_pg_policy_polroles - 1] = PointerGetDatum(role_ids);
	}
	else
	{
		Oid		   *roles;
		Datum		roles_datum;
		bool		attr_isnull;
		ArrayType  *policy_roles;

		/*
		 * We need to pull the set of roles this policy applies to from what's
		 * in the catalog, so that we can recreate the dependencies correctly
		 * for the policy.
		 */

		roles_datum = heap_getattr(policy_tuple, Anum_pg_policy_polroles,
								   RelationGetDescr(pg_policy_rel),
								   &attr_isnull);
		Assert(!attr_isnull);

		policy_roles = DatumGetArrayTypePCopy(roles_datum);

		roles = (Oid *) ARR_DATA_PTR(policy_roles);

		nitems = ARR_DIMS(policy_roles)[0];

		role_oids = (Datum *) palloc(nitems * sizeof(Datum));

		for (i = 0; i < nitems; i++)
			role_oids[i] = ObjectIdGetDatum(roles[i]);
	}

	if (qual != NULL)
	{
		replaces[Anum_pg_policy_polqual - 1] = true;
		values[Anum_pg_policy_polqual - 1]
			= CStringGetTextDatum(nodeToString(qual));
	}
	else
	{
		Datum		value_datum;
		bool		attr_isnull;

		/*
		 * We need to pull the USING expression and build the range table for
		 * the policy from what's in the catalog, so that we can recreate the
		 * dependencies correctly for the policy.
		 */

		/* Check if the policy has a USING expr */
		value_datum = heap_getattr(policy_tuple, Anum_pg_policy_polqual,
								   RelationGetDescr(pg_policy_rel),
								   &attr_isnull);
		if (!attr_isnull)
		{
			char	   *qual_value;
			ParseState *qual_pstate;

			/* parsestate is built just to build the range table */
			qual_pstate = make_parsestate(NULL);

			qual_value = TextDatumGetCString(value_datum);
			qual = stringToNode(qual_value);

			/* Add this rel to the parsestate's rangetable, for dependencies */
			addRangeTableEntryForRelation(qual_pstate, target_table,
										  AccessShareLock,
										  NULL, false, false);

			qual_parse_rtable = qual_pstate->p_rtable;
			free_parsestate(qual_pstate);
		}
	}

	if (with_check_qual != NULL)
	{
		replaces[Anum_pg_policy_polwithcheck - 1] = true;
		values[Anum_pg_policy_polwithcheck - 1]
			= CStringGetTextDatum(nodeToString(with_check_qual));
	}
	else
	{
		Datum		value_datum;
		bool		attr_isnull;

		/*
		 * We need to pull the WITH CHECK expression and build the range table
		 * for the policy from what's in the catalog, so that we can recreate
		 * the dependencies correctly for the policy.
		 */

		/* Check if the policy has a WITH CHECK expr */
		value_datum = heap_getattr(policy_tuple, Anum_pg_policy_polwithcheck,
								   RelationGetDescr(pg_policy_rel),
								   &attr_isnull);
		if (!attr_isnull)
		{
			char	   *with_check_value;
			ParseState *with_check_pstate;

			/* parsestate is built just to build the range table */
			with_check_pstate = make_parsestate(NULL);

			with_check_value = TextDatumGetCString(value_datum);
			with_check_qual = stringToNode(with_check_value);

			/* Add this rel to the parsestate's rangetable, for dependencies */
			addRangeTableEntryForRelation(with_check_pstate, target_table,
										  AccessShareLock,
										  NULL, false, false);

			with_check_parse_rtable = with_check_pstate->p_rtable;
			free_parsestate(with_check_pstate);
		}
	}

	new_tuple = heap_modify_tuple(policy_tuple,
								  RelationGetDescr(pg_policy_rel),
								  values, isnull, replaces);
	CatalogTupleUpdate(pg_policy_rel, &new_tuple->t_self, new_tuple);

	/* Update Dependencies. */
	deleteDependencyRecordsFor(PolicyRelationId, policy_id, false);

	/* Record Dependencies */
	target.classId = RelationRelationId;
	target.objectId = table_id;
	target.objectSubId = 0;

	myself.classId = PolicyRelationId;
	myself.objectId = policy_id;
	myself.objectSubId = 0;

	recordDependencyOn(&myself, &target, DEPENDENCY_AUTO);

	recordDependencyOnExpr(&myself, qual, qual_parse_rtable, DEPENDENCY_NORMAL);

	recordDependencyOnExpr(&myself, with_check_qual, with_check_parse_rtable,
						   DEPENDENCY_NORMAL);

	/* Register role dependencies */
	deleteSharedDependencyRecordsFor(PolicyRelationId, policy_id, 0);
	target.classId = AuthIdRelationId;
	target.objectSubId = 0;
	for (i = 0; i < nitems; i++)
	{
		target.objectId = DatumGetObjectId(role_oids[i]);
		/* no dependency if public */
		if (target.objectId != ACL_ID_PUBLIC)
			recordSharedDependencyOn(&myself, &target,
									 SHARED_DEPENDENCY_POLICY);
	}

	InvokeObjectPostAlterHook(PolicyRelationId, policy_id, 0);

	heap_freetuple(new_tuple);

	/* Invalidate Relation Cache */
	CacheInvalidateRelcache(target_table);

	/* Clean up. */
	systable_endscan(sscan);
	relation_close(target_table, NoLock);
	table_close(pg_policy_rel, RowExclusiveLock);

	return myself;
}