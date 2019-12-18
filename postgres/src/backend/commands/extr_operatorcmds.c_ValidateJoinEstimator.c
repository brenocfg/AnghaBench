#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FLOAT8OID ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  INT2OID ; 
 int /*<<< orphan*/  INTERNALOID ; 
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_func_rettype (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_proc_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
ValidateJoinEstimator(List *joinName)
{
	Oid			typeId[5];
	Oid			joinOid;
	AclResult	aclresult;

	typeId[0] = INTERNALOID;	/* PlannerInfo */
	typeId[1] = OIDOID;			/* operator OID */
	typeId[2] = INTERNALOID;	/* args list */
	typeId[3] = INT2OID;		/* jointype */
	typeId[4] = INTERNALOID;	/* SpecialJoinInfo */

	/*
	 * As of Postgres 8.4, the preferred signature for join estimators has 5
	 * arguments, but we still allow the old 4-argument form. Try the
	 * preferred form first.
	 */
	joinOid = LookupFuncName(joinName, 5, typeId, true);
	if (!OidIsValid(joinOid))
		joinOid = LookupFuncName(joinName, 4, typeId, true);
	/* If not found, reference the 5-argument signature in error msg */
	if (!OidIsValid(joinOid))
		joinOid = LookupFuncName(joinName, 5, typeId, false);

	/* estimators must return float8 */
	if (get_func_rettype(joinOid) != FLOAT8OID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("join estimator function %s must return type %s",
						NameListToString(joinName), "float8")));

	/* Require EXECUTE rights for the estimator */
	aclresult = pg_proc_aclcheck(joinOid, GetUserId(), ACL_EXECUTE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_FUNCTION,
					   NameListToString(joinName));

	return joinOid;
}