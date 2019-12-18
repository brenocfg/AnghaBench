#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int n_members; TYPE_1__** members; } ;
struct TYPE_7__ {scalar_t__ amprocnum; scalar_t__ amprocrighttype; scalar_t__ amproc; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  int /*<<< orphan*/  ParseState ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_amproc ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  AMPROCNUM ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BTINRANGE_PROC ; 
 int /*<<< orphan*/  COERCION_IMPLICIT ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_WINDOW_FRAME_GROUPS ; 
 int /*<<< orphan*/  EXPR_KIND_WINDOW_FRAME_RANGE ; 
 int /*<<< orphan*/  EXPR_KIND_WINDOW_FRAME_ROWS ; 
 int FRAMEOPTION_GROUPS ; 
 int FRAMEOPTION_RANGE ; 
 int FRAMEOPTION_ROWS ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ INT8OID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseCatCacheList (TYPE_3__*) ; 
 TYPE_3__* SearchSysCacheList2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UNKNOWNOID ; 
 int /*<<< orphan*/  can_coerce_type (int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkExprIsVarFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * coerce_to_specific_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exprLocation (int /*<<< orphan*/ *) ; 
 scalar_t__ exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
transformFrameOffset(ParseState *pstate, int frameOptions,
					 Oid rangeopfamily, Oid rangeopcintype, Oid *inRangeFunc,
					 Node *clause)
{
	const char *constructName = NULL;
	Node	   *node;

	*inRangeFunc = InvalidOid;	/* default result */

	/* Quick exit if no offset expression */
	if (clause == NULL)
		return NULL;

	if (frameOptions & FRAMEOPTION_ROWS)
	{
		/* Transform the raw expression tree */
		node = transformExpr(pstate, clause, EXPR_KIND_WINDOW_FRAME_ROWS);

		/*
		 * Like LIMIT clause, simply coerce to int8
		 */
		constructName = "ROWS";
		node = coerce_to_specific_type(pstate, node, INT8OID, constructName);
	}
	else if (frameOptions & FRAMEOPTION_RANGE)
	{
		/*
		 * We must look up the in_range support function that's to be used,
		 * possibly choosing one of several, and coerce the "offset" value to
		 * the appropriate input type.
		 */
		Oid			nodeType;
		Oid			preferredType;
		int			nfuncs = 0;
		int			nmatches = 0;
		Oid			selectedType = InvalidOid;
		Oid			selectedFunc = InvalidOid;
		CatCList   *proclist;
		int			i;

		/* Transform the raw expression tree */
		node = transformExpr(pstate, clause, EXPR_KIND_WINDOW_FRAME_RANGE);
		nodeType = exprType(node);

		/*
		 * If there are multiple candidates, we'll prefer the one that exactly
		 * matches nodeType; or if nodeType is as yet unknown, prefer the one
		 * that exactly matches the sort column type.  (The second rule is
		 * like what we do for "known_type operator unknown".)
		 */
		preferredType = (nodeType != UNKNOWNOID) ? nodeType : rangeopcintype;

		/* Find the in_range support functions applicable to this case */
		proclist = SearchSysCacheList2(AMPROCNUM,
									   ObjectIdGetDatum(rangeopfamily),
									   ObjectIdGetDatum(rangeopcintype));
		for (i = 0; i < proclist->n_members; i++)
		{
			HeapTuple	proctup = &proclist->members[i]->tuple;
			Form_pg_amproc procform = (Form_pg_amproc) GETSTRUCT(proctup);

			/* The search will find all support proc types; ignore others */
			if (procform->amprocnum != BTINRANGE_PROC)
				continue;
			nfuncs++;

			/* Ignore function if given value can't be coerced to that type */
			if (!can_coerce_type(1, &nodeType, &procform->amprocrighttype,
								 COERCION_IMPLICIT))
				continue;
			nmatches++;

			/* Remember preferred match, or any match if didn't find that */
			if (selectedType != preferredType)
			{
				selectedType = procform->amprocrighttype;
				selectedFunc = procform->amproc;
			}
		}
		ReleaseCatCacheList(proclist);

		/*
		 * Throw error if needed.  It seems worth taking the trouble to
		 * distinguish "no support at all" from "you didn't match any
		 * available offset type".
		 */
		if (nfuncs == 0)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("RANGE with offset PRECEDING/FOLLOWING is not supported for column type %s",
							format_type_be(rangeopcintype)),
					 parser_errposition(pstate, exprLocation(node))));
		if (nmatches == 0)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("RANGE with offset PRECEDING/FOLLOWING is not supported for column type %s and offset type %s",
							format_type_be(rangeopcintype),
							format_type_be(nodeType)),
					 errhint("Cast the offset value to an appropriate type."),
					 parser_errposition(pstate, exprLocation(node))));
		if (nmatches != 1 && selectedType != preferredType)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("RANGE with offset PRECEDING/FOLLOWING has multiple interpretations for column type %s and offset type %s",
							format_type_be(rangeopcintype),
							format_type_be(nodeType)),
					 errhint("Cast the offset value to the exact intended type."),
					 parser_errposition(pstate, exprLocation(node))));

		/* OK, coerce the offset to the right type */
		constructName = "RANGE";
		node = coerce_to_specific_type(pstate, node,
									   selectedType, constructName);
		*inRangeFunc = selectedFunc;
	}
	else if (frameOptions & FRAMEOPTION_GROUPS)
	{
		/* Transform the raw expression tree */
		node = transformExpr(pstate, clause, EXPR_KIND_WINDOW_FRAME_GROUPS);

		/*
		 * Like LIMIT clause, simply coerce to int8
		 */
		constructName = "GROUPS";
		node = coerce_to_specific_type(pstate, node, INT8OID, constructName);
	}
	else
	{
		Assert(false);
		node = NULL;
	}

	/* Disallow variables in frame offsets */
	checkExprIsVarFree(pstate, node, constructName);

	return node;
}