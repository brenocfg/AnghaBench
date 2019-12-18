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
typedef  int /*<<< orphan*/  DefElem ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_OBJECT_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INTERNALOID ; 
 scalar_t__ LookupFuncName (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/ * defGetQualifiedName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  func_signature_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ get_func_rettype (scalar_t__) ; 
 int /*<<< orphan*/  superuser () ; 

__attribute__((used)) static Oid
interpret_func_support(DefElem *defel)
{
	List	   *procName = defGetQualifiedName(defel);
	Oid			procOid;
	Oid			argList[1];

	/*
	 * Support functions always take one INTERNAL argument and return
	 * INTERNAL.
	 */
	argList[0] = INTERNALOID;

	procOid = LookupFuncName(procName, 1, argList, true);
	if (!OidIsValid(procOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function %s does not exist",
						func_signature_string(procName, 1, NIL, argList))));

	if (get_func_rettype(procOid) != INTERNALOID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_OBJECT_DEFINITION),
				 errmsg("support function %s must return type %s",
						NameListToString(procName), "internal")));

	/*
	 * Someday we might want an ACL check here; but for now, we insist that
	 * you be superuser to specify a support function, so privilege on the
	 * support function is moot.
	 */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser to specify a support function")));

	return procOid;
}