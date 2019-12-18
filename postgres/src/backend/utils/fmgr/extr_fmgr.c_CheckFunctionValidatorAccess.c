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
struct TYPE_4__ {scalar_t__ lanvalidator; int /*<<< orphan*/  lanname; } ;
struct TYPE_3__ {scalar_t__ prolang; int /*<<< orphan*/  proname; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;
typedef  TYPE_2__* Form_pg_language ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANGOID ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 int /*<<< orphan*/  OBJECT_LANGUAGE ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,...) ; 
 scalar_t__ pg_language_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_proc_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
CheckFunctionValidatorAccess(Oid validatorOid, Oid functionOid)
{
	HeapTuple	procTup;
	HeapTuple	langTup;
	Form_pg_proc procStruct;
	Form_pg_language langStruct;
	AclResult	aclresult;

	/*
	 * Get the function's pg_proc entry.  Throw a user-facing error for bad
	 * OID, because validators can be called with user-specified OIDs.
	 */
	procTup = SearchSysCache1(PROCOID, ObjectIdGetDatum(functionOid));
	if (!HeapTupleIsValid(procTup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function with OID %u does not exist", functionOid)));
	procStruct = (Form_pg_proc) GETSTRUCT(procTup);

	/*
	 * Fetch pg_language entry to know if this is the correct validation
	 * function for that pg_proc entry.
	 */
	langTup = SearchSysCache1(LANGOID, ObjectIdGetDatum(procStruct->prolang));
	if (!HeapTupleIsValid(langTup))
		elog(ERROR, "cache lookup failed for language %u", procStruct->prolang);
	langStruct = (Form_pg_language) GETSTRUCT(langTup);

	if (langStruct->lanvalidator != validatorOid)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("language validation function %u called for language %u instead of %u",
						validatorOid, procStruct->prolang,
						langStruct->lanvalidator)));

	/* first validate that we have permissions to use the language */
	aclresult = pg_language_aclcheck(procStruct->prolang, GetUserId(),
									 ACL_USAGE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_LANGUAGE,
					   NameStr(langStruct->lanname));

	/*
	 * Check whether we are allowed to execute the function itself. If we can
	 * execute it, there should be no possible side-effect of
	 * compiling/validation that execution can't have.
	 */
	aclresult = pg_proc_aclcheck(functionOid, GetUserId(), ACL_EXECUTE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_FUNCTION, NameStr(procStruct->proname));

	ReleaseSysCache(procTup);
	ReleaseSysCache(langTup);

	return true;
}