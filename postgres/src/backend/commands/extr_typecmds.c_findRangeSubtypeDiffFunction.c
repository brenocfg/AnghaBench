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
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FLOAT8OID ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PROVOLATILE_IMMUTABLE ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  func_signature_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ func_volatile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_func_name (int /*<<< orphan*/ ) ; 
 scalar_t__ get_func_rettype (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_proc_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
findRangeSubtypeDiffFunction(List *procname, Oid subtype)
{
	Oid			argList[2];
	Oid			procOid;
	AclResult	aclresult;

	/*
	 * Range subtype diff functions must take two arguments of the subtype,
	 * must return float8, and must be immutable.
	 */
	argList[0] = subtype;
	argList[1] = subtype;

	procOid = LookupFuncName(procname, 2, argList, true);

	if (!OidIsValid(procOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function %s does not exist",
						func_signature_string(procname, 2, NIL, argList))));

	if (get_func_rettype(procOid) != FLOAT8OID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("range subtype diff function %s must return type %s",
						func_signature_string(procname, 2, NIL, argList),
						"double precision")));

	if (func_volatile(procOid) != PROVOLATILE_IMMUTABLE)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("range subtype diff function %s must be immutable",
						func_signature_string(procname, 2, NIL, argList))));

	/* Also, range type's creator must have permission to call function */
	aclresult = pg_proc_aclcheck(procOid, GetUserId(), ACL_EXECUTE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_FUNCTION, get_func_name(procOid));

	return procOid;
}