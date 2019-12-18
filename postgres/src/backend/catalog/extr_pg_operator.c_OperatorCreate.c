#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* HeapTuple ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int Anum_pg_operator_oid ; 
 int Anum_pg_operator_oprcanhash ; 
 int Anum_pg_operator_oprcanmerge ; 
 int Anum_pg_operator_oprcode ; 
 int Anum_pg_operator_oprcom ; 
 int Anum_pg_operator_oprjoin ; 
 int Anum_pg_operator_oprkind ; 
 int Anum_pg_operator_oprleft ; 
 int Anum_pg_operator_oprname ; 
 int Anum_pg_operator_oprnamespace ; 
 int Anum_pg_operator_oprnegate ; 
 int Anum_pg_operator_oprowner ; 
 int Anum_pg_operator_oprrest ; 
 int Anum_pg_operator_oprresult ; 
 int Anum_pg_operator_oprright ; 
 scalar_t__ BOOLOID ; 
 scalar_t__ BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ CharGetDatum (char) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_FUNCTION ; 
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NameGetDatum (int /*<<< orphan*/ *) ; 
 char const* NameListToString (int /*<<< orphan*/ *) ; 
 int Natts_pg_operator ; 
 int /*<<< orphan*/  OBJECT_OPERATOR ; 
 int /*<<< orphan*/  OPEROID ; 
 scalar_t__ ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ OperatorGet (char const*,scalar_t__,scalar_t__,scalar_t__,int*) ; 
 int /*<<< orphan*/  OperatorOidIndexId ; 
 int /*<<< orphan*/  OperatorRelationId ; 
 int /*<<< orphan*/  OperatorUpd (scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_func_rettype (scalar_t__) ; 
 scalar_t__ get_other_operator (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char const*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 TYPE_1__* heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  makeOperatorDependencies (TYPE_1__*,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_oper_ownercheck (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validOperatorName (char const*) ; 

ObjectAddress
OperatorCreate(const char *operatorName,
			   Oid operatorNamespace,
			   Oid leftTypeId,
			   Oid rightTypeId,
			   Oid procedureId,
			   List *commutatorName,
			   List *negatorName,
			   Oid restrictionId,
			   Oid joinId,
			   bool canMerge,
			   bool canHash)
{
	Relation	pg_operator_desc;
	HeapTuple	tup;
	bool		isUpdate;
	bool		nulls[Natts_pg_operator];
	bool		replaces[Natts_pg_operator];
	Datum		values[Natts_pg_operator];
	Oid			operatorObjectId;
	bool		operatorAlreadyDefined;
	Oid			operResultType;
	Oid			commutatorId,
				negatorId;
	bool		selfCommutator = false;
	NameData	oname;
	int			i;
	ObjectAddress address;

	/*
	 * Sanity checks
	 */
	if (!validOperatorName(operatorName))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("\"%s\" is not a valid operator name",
						operatorName)));

	if (!(OidIsValid(leftTypeId) && OidIsValid(rightTypeId)))
	{
		/* If it's not a binary op, these things mustn't be set: */
		if (commutatorName)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only binary operators can have commutators")));
		if (OidIsValid(joinId))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only binary operators can have join selectivity")));
		if (canMerge)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only binary operators can merge join")));
		if (canHash)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only binary operators can hash")));
	}

	operResultType = get_func_rettype(procedureId);

	if (operResultType != BOOLOID)
	{
		/* If it's not a boolean op, these things mustn't be set: */
		if (negatorName)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only boolean operators can have negators")));
		if (OidIsValid(restrictionId))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only boolean operators can have restriction selectivity")));
		if (OidIsValid(joinId))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only boolean operators can have join selectivity")));
		if (canMerge)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only boolean operators can merge join")));
		if (canHash)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("only boolean operators can hash")));
	}

	operatorObjectId = OperatorGet(operatorName,
								   operatorNamespace,
								   leftTypeId,
								   rightTypeId,
								   &operatorAlreadyDefined);

	if (operatorAlreadyDefined)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_FUNCTION),
				 errmsg("operator %s already exists",
						operatorName)));

	/*
	 * At this point, if operatorObjectId is not InvalidOid then we are
	 * filling in a previously-created shell.  Insist that the user own any
	 * such shell.
	 */
	if (OidIsValid(operatorObjectId) &&
		!pg_oper_ownercheck(operatorObjectId, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_OPERATOR,
					   operatorName);

	/*
	 * Set up the other operators.  If they do not currently exist, create
	 * shells in order to get ObjectId's.
	 */

	if (commutatorName)
	{
		/* commutator has reversed arg types */
		commutatorId = get_other_operator(commutatorName,
										  rightTypeId, leftTypeId,
										  operatorName, operatorNamespace,
										  leftTypeId, rightTypeId,
										  true);

		/* Permission check: must own other operator */
		if (OidIsValid(commutatorId) &&
			!pg_oper_ownercheck(commutatorId, GetUserId()))
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_OPERATOR,
						   NameListToString(commutatorName));

		/*
		 * self-linkage to this operator; will fix below. Note that only
		 * self-linkage for commutation makes sense.
		 */
		if (!OidIsValid(commutatorId))
			selfCommutator = true;
	}
	else
		commutatorId = InvalidOid;

	if (negatorName)
	{
		/* negator has same arg types */
		negatorId = get_other_operator(negatorName,
									   leftTypeId, rightTypeId,
									   operatorName, operatorNamespace,
									   leftTypeId, rightTypeId,
									   false);

		/* Permission check: must own other operator */
		if (OidIsValid(negatorId) &&
			!pg_oper_ownercheck(negatorId, GetUserId()))
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_OPERATOR,
						   NameListToString(negatorName));
	}
	else
		negatorId = InvalidOid;

	/*
	 * set up values in the operator tuple
	 */

	for (i = 0; i < Natts_pg_operator; ++i)
	{
		values[i] = (Datum) NULL;
		replaces[i] = true;
		nulls[i] = false;
	}

	namestrcpy(&oname, operatorName);
	values[Anum_pg_operator_oprname - 1] = NameGetDatum(&oname);
	values[Anum_pg_operator_oprnamespace - 1] = ObjectIdGetDatum(operatorNamespace);
	values[Anum_pg_operator_oprowner - 1] = ObjectIdGetDatum(GetUserId());
	values[Anum_pg_operator_oprkind - 1] = CharGetDatum(leftTypeId ? (rightTypeId ? 'b' : 'r') : 'l');
	values[Anum_pg_operator_oprcanmerge - 1] = BoolGetDatum(canMerge);
	values[Anum_pg_operator_oprcanhash - 1] = BoolGetDatum(canHash);
	values[Anum_pg_operator_oprleft - 1] = ObjectIdGetDatum(leftTypeId);
	values[Anum_pg_operator_oprright - 1] = ObjectIdGetDatum(rightTypeId);
	values[Anum_pg_operator_oprresult - 1] = ObjectIdGetDatum(operResultType);
	values[Anum_pg_operator_oprcom - 1] = ObjectIdGetDatum(commutatorId);
	values[Anum_pg_operator_oprnegate - 1] = ObjectIdGetDatum(negatorId);
	values[Anum_pg_operator_oprcode - 1] = ObjectIdGetDatum(procedureId);
	values[Anum_pg_operator_oprrest - 1] = ObjectIdGetDatum(restrictionId);
	values[Anum_pg_operator_oprjoin - 1] = ObjectIdGetDatum(joinId);

	pg_operator_desc = table_open(OperatorRelationId, RowExclusiveLock);

	/*
	 * If we are replacing an operator shell, update; else insert
	 */
	if (operatorObjectId)
	{
		isUpdate = true;

		tup = SearchSysCacheCopy1(OPEROID,
								  ObjectIdGetDatum(operatorObjectId));
		if (!HeapTupleIsValid(tup))
			elog(ERROR, "cache lookup failed for operator %u",
				 operatorObjectId);

		replaces[Anum_pg_operator_oid - 1] = false;
		tup = heap_modify_tuple(tup,
								RelationGetDescr(pg_operator_desc),
								values,
								nulls,
								replaces);

		CatalogTupleUpdate(pg_operator_desc, &tup->t_self, tup);
	}
	else
	{
		isUpdate = false;

		operatorObjectId = GetNewOidWithIndex(pg_operator_desc,
											  OperatorOidIndexId,
											  Anum_pg_operator_oid);
		values[Anum_pg_operator_oid - 1] = ObjectIdGetDatum(operatorObjectId);

		tup = heap_form_tuple(RelationGetDescr(pg_operator_desc),
							  values, nulls);

		CatalogTupleInsert(pg_operator_desc, tup);
	}

	/* Add dependencies for the entry */
	address = makeOperatorDependencies(tup, isUpdate);

	/* Post creation hook for new operator */
	InvokeObjectPostCreateHook(OperatorRelationId, operatorObjectId, 0);

	table_close(pg_operator_desc, RowExclusiveLock);

	/*
	 * If a commutator and/or negator link is provided, update the other
	 * operator(s) to point at this one, if they don't already have a link.
	 * This supports an alternative style of operator definition wherein the
	 * user first defines one operator without giving negator or commutator,
	 * then defines the other operator of the pair with the proper commutator
	 * or negator attribute.  That style doesn't require creation of a shell,
	 * and it's the only style that worked right before Postgres version 6.5.
	 * This code also takes care of the situation where the new operator is
	 * its own commutator.
	 */
	if (selfCommutator)
		commutatorId = operatorObjectId;

	if (OidIsValid(commutatorId) || OidIsValid(negatorId))
		OperatorUpd(operatorObjectId, commutatorId, negatorId, false);

	return address;
}