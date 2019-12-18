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
typedef  int FuncLookupError ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_AMBIGUOUS_FUNCTION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
#define  FUNCLOOKUP_AMBIGUOUS 129 
#define  FUNCLOOKUP_NOSUCHFUNC 128 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LookupFuncNameInternal (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_signature_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

Oid
LookupFuncName(List *funcname, int nargs, const Oid *argtypes, bool missing_ok)
{
	Oid			funcoid;
	FuncLookupError lookupError;

	funcoid = LookupFuncNameInternal(funcname, nargs, argtypes, missing_ok,
									 &lookupError);

	if (OidIsValid(funcoid))
		return funcoid;

	switch (lookupError)
	{
		case FUNCLOOKUP_NOSUCHFUNC:
			/* Let the caller deal with it when missing_ok is true */
			if (missing_ok)
				return InvalidOid;

			if (nargs < 0)
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_FUNCTION),
						 errmsg("could not find a function named \"%s\"",
								NameListToString(funcname))));
			else
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_FUNCTION),
						 errmsg("function %s does not exist",
								func_signature_string(funcname, nargs,
													  NIL, argtypes))));
			break;

		case FUNCLOOKUP_AMBIGUOUS:
			/* Raise an error regardless of missing_ok */
			ereport(ERROR,
					(errcode(ERRCODE_AMBIGUOUS_FUNCTION),
					 errmsg("function name \"%s\" is not unique",
							NameListToString(funcname)),
					 errhint("Specify the argument list to select the function unambiguously.")));
			break;
	}

	return InvalidOid;			/* Keep compiler quiet */
}