#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  oid; int /*<<< orphan*/  args; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  FuncLookupError ;
typedef  TYPE_1__* FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FUNCLOOKUP_AMBIGUOUS ; 
 int /*<<< orphan*/  FUNCLOOKUP_NOSUCHFUNC ; 
 TYPE_1__* FuncnameGetCandidates (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Oid
LookupFuncNameInternal(List *funcname, int nargs, const Oid *argtypes,
					   bool missing_ok, FuncLookupError *lookupError)
{
	FuncCandidateList clist;

	/* NULL argtypes allowed for nullary functions only */
	Assert(argtypes != NULL || nargs == 0);

	/* Always set *lookupError, to forestall uninitialized-variable warnings */
	*lookupError = FUNCLOOKUP_NOSUCHFUNC;

	clist = FuncnameGetCandidates(funcname, nargs, NIL, false, false,
								  missing_ok);

	/*
	 * If no arguments were specified, the name must yield a unique candidate.
	 */
	if (nargs < 0)
	{
		if (clist)
		{
			/* If there is a second match then it's ambiguous */
			if (clist->next)
			{
				*lookupError = FUNCLOOKUP_AMBIGUOUS;
				return InvalidOid;
			}
			/* Otherwise return the match */
			return clist->oid;
		}
		else
			return InvalidOid;
	}

	/*
	 * Otherwise, look for a match to the arg types.  FuncnameGetCandidates
	 * has ensured that there's at most one match in the returned list.
	 */
	while (clist)
	{
		/* if nargs==0, argtypes can be null; don't pass that to memcmp */
		if (nargs == 0 ||
			memcmp(argtypes, clist->args, nargs * sizeof(Oid)) == 0)
			return clist->oid;
		clist = clist->next;
	}

	return InvalidOid;
}