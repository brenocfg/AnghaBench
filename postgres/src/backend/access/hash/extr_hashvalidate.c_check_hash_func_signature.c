#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int16 ;
struct TYPE_3__ {scalar_t__* values; } ;
struct TYPE_4__ {scalar_t__ prorettype; int pronargs; TYPE_1__ proargtypes; scalar_t__ proretset; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 scalar_t__ BOOLOID ; 
 scalar_t__ BYTEAOID ; 
 scalar_t__ CIDOID ; 
 scalar_t__ DATEOID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ F_HASHCHAR ; 
 scalar_t__ F_HASHCHAREXTENDED ; 
 scalar_t__ F_HASHINT4 ; 
 scalar_t__ F_HASHINT4EXTENDED ; 
 scalar_t__ F_HASHVARLENA ; 
 scalar_t__ F_HASHVARLENAEXTENDED ; 
 scalar_t__ F_TIMESTAMP_HASH ; 
 scalar_t__ F_TIMESTAMP_HASH_EXTENDED ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
#define  HASHEXTENDED_PROC 129 
#define  HASHSTANDARD_PROC 128 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ INT4OID ; 
 scalar_t__ INT8OID ; 
 int /*<<< orphan*/  IsBinaryCoercible (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TIMESTAMPTZOID ; 
 scalar_t__ XIDOID ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool
check_hash_func_signature(Oid funcid, int16 amprocnum, Oid argtype)
{
	bool		result = true;
	Oid			restype;
	int16		nargs;
	HeapTuple	tp;
	Form_pg_proc procform;

	switch (amprocnum)
	{
		case HASHSTANDARD_PROC:
			restype = INT4OID;
			nargs = 1;
			break;

		case HASHEXTENDED_PROC:
			restype = INT8OID;
			nargs = 2;
			break;

		default:
			elog(ERROR, "invalid amprocnum");
	}

	tp = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "cache lookup failed for function %u", funcid);
	procform = (Form_pg_proc) GETSTRUCT(tp);

	if (procform->prorettype != restype || procform->proretset ||
		procform->pronargs != nargs)
		result = false;

	if (!IsBinaryCoercible(argtype, procform->proargtypes.values[0]))
	{
		/*
		 * Some of the built-in hash opclasses cheat by using hash functions
		 * that are different from but physically compatible with the opclass
		 * datatype.  In some of these cases, even a "binary coercible" check
		 * fails because there's no relevant cast.  For the moment, fix it by
		 * having a whitelist of allowed cases.  Test the specific function
		 * identity, not just its input type, because hashvarlena() takes
		 * INTERNAL and allowing any such function seems too scary.
		 */
		if ((funcid == F_HASHINT4 || funcid == F_HASHINT4EXTENDED) &&
			(argtype == DATEOID ||
			 argtype == XIDOID || argtype == CIDOID))
			 /* okay, allowed use of hashint4() */ ;
		else if ((funcid == F_TIMESTAMP_HASH ||
				  funcid == F_TIMESTAMP_HASH_EXTENDED) &&
				 argtype == TIMESTAMPTZOID)
			 /* okay, allowed use of timestamp_hash() */ ;
		else if ((funcid == F_HASHCHAR || funcid == F_HASHCHAREXTENDED) &&
				 argtype == BOOLOID)
			 /* okay, allowed use of hashchar() */ ;
		else if ((funcid == F_HASHVARLENA || funcid == F_HASHVARLENAEXTENDED) &&
				 argtype == BYTEAOID)
			 /* okay, allowed use of hashvarlena() */ ;
		else
			result = false;
	}

	/* If function takes a second argument, it must be for a 64-bit salt. */
	if (nargs == 2 && procform->proargtypes.values[1] != INT8OID)
		result = false;

	ReleaseSysCache(tp);
	return result;
}