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
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  OprCacheKey ;
typedef  int /*<<< orphan*/  Operator ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  FuncDetailCode ;
typedef  int /*<<< orphan*/ * FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCDETAIL_NOTFOUND ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpernameGetCandidates (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binary_oper_exact (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_oper_cache_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_oper_cache_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int make_oper_cache_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  op_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oper_select_candidate (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Operator
oper(ParseState *pstate, List *opname, Oid ltypeId, Oid rtypeId,
	 bool noError, int location)
{
	Oid			operOid;
	OprCacheKey key;
	bool		key_ok;
	FuncDetailCode fdresult = FUNCDETAIL_NOTFOUND;
	HeapTuple	tup = NULL;

	/*
	 * Try to find the mapping in the lookaside cache.
	 */
	key_ok = make_oper_cache_key(pstate, &key, opname, ltypeId, rtypeId, location);

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
	operOid = binary_oper_exact(opname, ltypeId, rtypeId);
	if (!OidIsValid(operOid))
	{
		/*
		 * Otherwise, search for the most suitable candidate.
		 */
		FuncCandidateList clist;

		/* Get binary operators of given name */
		clist = OpernameGetCandidates(opname, 'b', false);

		/* No operators found? Then fail... */
		if (clist != NULL)
		{
			/*
			 * Unspecified type for one of the arguments? then use the other
			 * (XXX this is probably dead code?)
			 */
			Oid			inputOids[2];

			if (rtypeId == InvalidOid)
				rtypeId = ltypeId;
			else if (ltypeId == InvalidOid)
				ltypeId = rtypeId;
			inputOids[0] = ltypeId;
			inputOids[1] = rtypeId;
			fdresult = oper_select_candidate(2, inputOids, clist, &operOid);
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
		op_error(pstate, opname, 'b', ltypeId, rtypeId, fdresult, location);

	return (Operator) tup;
}