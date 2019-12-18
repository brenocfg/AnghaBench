#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FuncDetailCode ;
typedef  TYPE_1__* FuncCandidateList ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCDETAIL_MULTIPLE ; 
 int /*<<< orphan*/  FUNCDETAIL_NORMAL ; 
 int /*<<< orphan*/  FUNCDETAIL_NOTFOUND ; 
 int /*<<< orphan*/  InvalidOid ; 
 int func_match_argtypes (int,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__**) ; 
 TYPE_1__* func_select_candidate (int,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static FuncDetailCode
oper_select_candidate(int nargs,
					  Oid *input_typeids,
					  FuncCandidateList candidates,
					  Oid *operOid) /* output argument */
{
	int			ncandidates;

	/*
	 * Delete any candidates that cannot actually accept the given input
	 * types, whether directly or by coercion.
	 */
	ncandidates = func_match_argtypes(nargs, input_typeids,
									  candidates, &candidates);

	/* Done if no candidate or only one candidate survives */
	if (ncandidates == 0)
	{
		*operOid = InvalidOid;
		return FUNCDETAIL_NOTFOUND;
	}
	if (ncandidates == 1)
	{
		*operOid = candidates->oid;
		return FUNCDETAIL_NORMAL;
	}

	/*
	 * Use the same heuristics as for ambiguous functions to resolve the
	 * conflict.
	 */
	candidates = func_select_candidate(nargs, input_typeids, candidates);

	if (candidates)
	{
		*operOid = candidates->oid;
		return FUNCDETAIL_NORMAL;
	}

	*operOid = InvalidOid;
	return FUNCDETAIL_MULTIPLE; /* failed to select a best candidate */
}