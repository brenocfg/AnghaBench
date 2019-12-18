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
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ LookupFuncName (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  OBJECT_FUNCTION ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 scalar_t__ PROVOLATILE_IMMUTABLE ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_signature_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ func_volatile (scalar_t__) ; 
 int /*<<< orphan*/  get_func_name (scalar_t__) ; 
 scalar_t__ get_func_rettype (scalar_t__) ; 
 scalar_t__ pg_proc_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
findRangeCanonicalFunction(List *procname, Oid typeOid)
{
	Oid			argList[1];
	Oid			procOid;
	AclResult	aclresult;

	/*
	 * Range canonical functions must take and return the range type, and must
	 * be immutable.
	 */
	argList[0] = typeOid;

	procOid = LookupFuncName(procname, 1, argList, true);

	if (!OidIsValid(procOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function %s does not exist",
						func_signature_string(procname, 1, NIL, argList))));

	if (get_func_rettype(procOid) != typeOid)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("range canonical function %s must return range type",
						func_signature_string(procname, 1, NIL, argList))));

	if (func_volatile(procOid) != PROVOLATILE_IMMUTABLE)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("range canonical function %s must be immutable",
						func_signature_string(procname, 1, NIL, argList))));

	/* Also, range type's creator must have permission to call function */
	aclresult = pg_proc_aclcheck(procOid, GetUserId(), ACL_EXECUTE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_FUNCTION, get_func_name(procOid));

	return procOid;
}