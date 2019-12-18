#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * args; struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  OprCacheKey ;
typedef  int /*<<< orphan*/  Operator ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  FuncDetailCode ;
typedef  TYPE_1__* FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCDETAIL_NOTFOUND ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 TYPE_1__* OpernameGetCandidates (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  OpernameGetOprid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_oper_cache_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_oper_cache_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int make_oper_cache_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  op_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oper_select_candidate (int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

Operator
left_oper(ParseState *pstate, List *op, Oid arg, bool noError, int location)
{
	Oid			operOid;
	OprCacheKey key;
	bool		key_ok;
	FuncDetailCode fdresult = FUNCDETAIL_NOTFOUND;
	HeapTuple	tup = NULL;

	/*
	 * Try to find the mapping in the lookaside cache.
	 */
	key_ok = make_oper_cache_key(pstate, &key, op, InvalidOid, arg, location);

	if (key_ok)
	{
		operOid = find_oper_cache_entry(&key);
		if (OidIsValid(operOid))
		{
			tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operOid));
			if (HeapTupleIsValid(tup))
				return (Operator) tup;
		}
	}

	/*
	 * First try for an "exact" match.
	 */
	operOid = OpernameGetOprid(op, InvalidOid, arg);
	if (!OidIsValid(operOid))
	{
		/*
		 * Otherwise, search for the most suitable candidate.
		 */
		FuncCandidateList clist;

		/* Get prefix operators of given name */
		clist = OpernameGetCandidates(op, 'l', false);

		/* No operators found? Then fail... */
		if (clist != NULL)
		{
			/*
			 * The returned list has args in the form (0, oprright). Move the
			 * useful data into args[0] to keep oper_select_candidate simple.
			 * XXX we are assuming here that we may scribble on the list!
			 */
			FuncCandidateList clisti;

			for (clisti = clist; clisti != NULL; clisti = clisti->next)
			{
				clisti->args[0] = clisti->args[1];
			}

			/*
			 * We must run oper_select_candidate even if only one candidate,
			 * otherwise we may falsely return a non-type-compatible operator.
			 */
			fdresult = oper_select_candidate(1, &arg, clist, &operOid);
		}
	}

	if (OidIsValid(operOid))
		tup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operOid));

	if (HeapTupleIsValid(tup))
	{
		if (key_ok)
			make_oper_cache_entry(&key, operOid);
	}
	else if (!noError)
		op_error(pstate, op, 'l', InvalidOid, arg, fdresult, location);

	return (Operator) tup;
}