#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
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
 scalar_t__ BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CharGetDatum (char) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERRCODE_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetUserId () ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NameGetDatum (int /*<<< orphan*/ *) ; 
 int Natts_pg_operator ; 
 scalar_t__ ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OperatorOidIndexId ; 
 int /*<<< orphan*/  OperatorRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeOperatorDependencies (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validOperatorName (char const*) ; 

__attribute__((used)) static Oid
OperatorShellMake(const char *operatorName,
				  Oid operatorNamespace,
				  Oid leftTypeId,
				  Oid rightTypeId)
{
	Relation	pg_operator_desc;
	Oid			operatorObjectId;
	int			i;
	HeapTuple	tup;
	Datum		values[Natts_pg_operator];
	bool		nulls[Natts_pg_operator];
	NameData	oname;
	TupleDesc	tupDesc;

	/*
	 * validate operator name
	 */
	if (!validOperatorName(operatorName))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_NAME),
				 errmsg("\"%s\" is not a valid operator name",
						operatorName)));

	/*
	 * open pg_operator
	 */
	pg_operator_desc = table_open(OperatorRelationId, RowExclusiveLock);
	tupDesc = pg_operator_desc->rd_att;

	/*
	 * initialize our *nulls and *values arrays
	 */
	for (i = 0; i < Natts_pg_operator; ++i)
	{
		nulls[i] = false;
		values[i] = (Datum) NULL;	/* redundant, but safe */
	}

	/*
	 * initialize values[] with the operator name and input data types. Note
	 * that oprcode is set to InvalidOid, indicating it's a shell.
	 */
	operatorObjectId = GetNewOidWithIndex(pg_operator_desc, OperatorOidIndexId,
										  Anum_pg_operator_oid);
	values[Anum_pg_operator_oid - 1] = ObjectIdGetDatum(operatorObjectId);
	namestrcpy(&oname, operatorName);
	values[Anum_pg_operator_oprname - 1] = NameGetDatum(&oname);
	values[Anum_pg_operator_oprnamespace - 1] = ObjectIdGetDatum(operatorNamespace);
	values[Anum_pg_operator_oprowner - 1] = ObjectIdGetDatum(GetUserId());
	values[Anum_pg_operator_oprkind - 1] = CharGetDatum(leftTypeId ? (rightTypeId ? 'b' : 'r') : 'l');
	values[Anum_pg_operator_oprcanmerge - 1] = BoolGetDatum(false);
	values[Anum_pg_operator_oprcanhash - 1] = BoolGetDatum(false);
	values[Anum_pg_operator_oprleft - 1] = ObjectIdGetDatum(leftTypeId);
	values[Anum_pg_operator_oprright - 1] = ObjectIdGetDatum(rightTypeId);
	values[Anum_pg_operator_oprresult - 1] = ObjectIdGetDatum(InvalidOid);
	values[Anum_pg_operator_oprcom - 1] = ObjectIdGetDatum(InvalidOid);
	values[Anum_pg_operator_oprnegate - 1] = ObjectIdGetDatum(InvalidOid);
	values[Anum_pg_operator_oprcode - 1] = ObjectIdGetDatum(InvalidOid);
	values[Anum_pg_operator_oprrest - 1] = ObjectIdGetDatum(InvalidOid);
	values[Anum_pg_operator_oprjoin - 1] = ObjectIdGetDatum(InvalidOid);

	/*
	 * create a new operator tuple
	 */
	tup = heap_form_tuple(tupDesc, values, nulls);

	/*
	 * insert our "shell" operator tuple
	 */
	CatalogTupleInsert(pg_operator_desc, tup);

	/* Add dependencies for the entry */
	makeOperatorDependencies(tup, false);

	heap_freetuple(tup);

	/* Post creation hook for new shell operator */
	InvokeObjectPostCreateHook(OperatorRelationId, operatorObjectId, 0);

	/*
	 * Make sure the tuple is visible for subsequent lookups/updates.
	 */
	CommandCounterIncrement();

	/*
	 * close the operator relation and return the oid.
	 */
	table_close(pg_operator_desc, RowExclusiveLock);

	return operatorObjectId;
}