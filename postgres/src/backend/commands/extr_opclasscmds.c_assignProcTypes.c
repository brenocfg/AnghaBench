#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* values; } ;
struct TYPE_7__ {int pronargs; scalar_t__ prorettype; TYPE_1__ proargtypes; } ;
struct TYPE_6__ {scalar_t__ number; scalar_t__ lefttype; scalar_t__ righttype; int /*<<< orphan*/  object; } ;
typedef  TYPE_2__ OpFamilyMember ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;

/* Variables and functions */
 scalar_t__ BOOLOID ; 
 scalar_t__ BTINRANGE_PROC ; 
 scalar_t__ BTORDER_PROC ; 
 scalar_t__ BTREE_AM_OID ; 
 scalar_t__ BTSORTSUPPORT_PROC ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HASHEXTENDED_PROC ; 
 scalar_t__ HASHSTANDARD_PROC ; 
 scalar_t__ HASH_AM_OID ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ INT4OID ; 
 scalar_t__ INT8OID ; 
 scalar_t__ INTERNALOID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
assignProcTypes(OpFamilyMember *member, Oid amoid, Oid typeoid)
{
	HeapTuple	proctup;
	Form_pg_proc procform;

	/* Fetch the procedure definition */
	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(member->object));
	if (!HeapTupleIsValid(proctup))
		elog(ERROR, "cache lookup failed for function %u", member->object);
	procform = (Form_pg_proc) GETSTRUCT(proctup);

	/*
	 * btree comparison procs must be 2-arg procs returning int4.  btree
	 * sortsupport procs must take internal and return void.  btree in_range
	 * procs must be 5-arg procs returning bool.  hash support proc 1 must be
	 * a 1-arg proc returning int4, while proc 2 must be a 2-arg proc
	 * returning int8.  Otherwise we don't know.
	 */
	if (amoid == BTREE_AM_OID)
	{
		if (member->number == BTORDER_PROC)
		{
			if (procform->pronargs != 2)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("btree comparison functions must have two arguments")));
			if (procform->prorettype != INT4OID)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("btree comparison functions must return integer")));

			/*
			 * If lefttype/righttype isn't specified, use the proc's input
			 * types
			 */
			if (!OidIsValid(member->lefttype))
				member->lefttype = procform->proargtypes.values[0];
			if (!OidIsValid(member->righttype))
				member->righttype = procform->proargtypes.values[1];
		}
		else if (member->number == BTSORTSUPPORT_PROC)
		{
			if (procform->pronargs != 1 ||
				procform->proargtypes.values[0] != INTERNALOID)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("btree sort support functions must accept type \"internal\"")));
			if (procform->prorettype != VOIDOID)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("btree sort support functions must return void")));

			/*
			 * Can't infer lefttype/righttype from proc, so use default rule
			 */
		}
		else if (member->number == BTINRANGE_PROC)
		{
			if (procform->pronargs != 5)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("btree in_range functions must have five arguments")));
			if (procform->prorettype != BOOLOID)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("btree in_range functions must return boolean")));

			/*
			 * If lefttype/righttype isn't specified, use the proc's input
			 * types (we look at the test-value and offset arguments)
			 */
			if (!OidIsValid(member->lefttype))
				member->lefttype = procform->proargtypes.values[0];
			if (!OidIsValid(member->righttype))
				member->righttype = procform->proargtypes.values[2];
		}
	}
	else if (amoid == HASH_AM_OID)
	{
		if (member->number == HASHSTANDARD_PROC)
		{
			if (procform->pronargs != 1)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("hash function 1 must have one argument")));
			if (procform->prorettype != INT4OID)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("hash function 1 must return integer")));
		}
		else if (member->number == HASHEXTENDED_PROC)
		{
			if (procform->pronargs != 2)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("hash function 2 must have two arguments")));
			if (procform->prorettype != INT8OID)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
						 errmsg("hash function 2 must return bigint")));
		}

		/*
		 * If lefttype/righttype isn't specified, use the proc's input type
		 */
		if (!OidIsValid(member->lefttype))
			member->lefttype = procform->proargtypes.values[0];
		if (!OidIsValid(member->righttype))
			member->righttype = procform->proargtypes.values[0];
	}

	/*
	 * The default in CREATE OPERATOR CLASS is to use the class' opcintype as
	 * lefttype and righttype.  In CREATE or ALTER OPERATOR FAMILY, opcintype
	 * isn't available, so make the user specify the types.
	 */
	if (!OidIsValid(member->lefttype))
		member->lefttype = typeoid;
	if (!OidIsValid(member->righttype))
		member->righttype = typeoid;

	if (!OidIsValid(member->lefttype) || !OidIsValid(member->righttype))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("associated data types must be specified for index support function")));

	ReleaseSysCache(proctup);
}