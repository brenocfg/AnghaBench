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

/* Variables and functions */
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupFuncName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPAQUEOID ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFunctionArgType (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_signature_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
findTypeOutputFunction(List *procname, Oid typeOid)
{
	Oid			argList[1];
	Oid			procOid;

	/*
	 * Output functions can take a single argument of the type.
	 *
	 * For backwards compatibility we allow OPAQUE in place of the actual type
	 * name; if we see this, we issue a warning and fix up the pg_proc entry.
	 */
	argList[0] = typeOid;

	procOid = LookupFuncName(procname, 1, argList, true);
	if (OidIsValid(procOid))
		return procOid;

	/* No luck, try it with OPAQUE */
	argList[0] = OPAQUEOID;

	procOid = LookupFuncName(procname, 1, argList, true);

	if (OidIsValid(procOid))
	{
		/* Found, but must complain and fix the pg_proc entry */
		ereport(WARNING,
				(errmsg("changing argument type of function %s from \"opaque\" to %s",
						NameListToString(procname), format_type_be(typeOid))));
		SetFunctionArgType(procOid, 0, typeOid);

		/*
		 * Need CommandCounterIncrement since DefineType will likely try to
		 * alter the pg_proc tuple again.
		 */
		CommandCounterIncrement();

		return procOid;
	}

	/* Use type name, not OPAQUE, in the failure message. */
	argList[0] = typeOid;

	ereport(ERROR,
			(errcode(ERRCODE_UNDEFINED_FUNCTION),
			 errmsg("function %s does not exist",
					func_signature_string(procname, 1, NIL, argList))));

	return InvalidOid;			/* keep compiler quiet */
}