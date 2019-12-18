#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
struct TYPE_5__ {int rtekind; int /*<<< orphan*/  functions; int /*<<< orphan*/  funcordinality; int /*<<< orphan*/  relid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * funcexpr; } ;
typedef  TYPE_1__ RangeTblFunction ;
typedef  TYPE_2__ RangeTblEntry ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int InvalidAttrNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RECORDOID ; 
#define  RTE_FUNCTION 129 
#define  RTE_RELATION 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprCollation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rel_type_id (int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_is_rowtype (int /*<<< orphan*/ ) ; 

Var *
makeWholeRowVar(RangeTblEntry *rte,
				Index varno,
				Index varlevelsup,
				bool allowScalar)
{
	Var		   *result;
	Oid			toid;
	Node	   *fexpr;

	switch (rte->rtekind)
	{
		case RTE_RELATION:
			/* relation: the rowtype is a named composite type */
			toid = get_rel_type_id(rte->relid);
			if (!OidIsValid(toid))
				elog(ERROR, "could not find type OID for relation %u",
					 rte->relid);
			result = makeVar(varno,
							 InvalidAttrNumber,
							 toid,
							 -1,
							 InvalidOid,
							 varlevelsup);
			break;

		case RTE_FUNCTION:

			/*
			 * If there's more than one function, or ordinality is requested,
			 * force a RECORD result, since there's certainly more than one
			 * column involved and it can't be a known named type.
			 */
			if (rte->funcordinality || list_length(rte->functions) != 1)
			{
				/* always produces an anonymous RECORD result */
				result = makeVar(varno,
								 InvalidAttrNumber,
								 RECORDOID,
								 -1,
								 InvalidOid,
								 varlevelsup);
				break;
			}

			fexpr = ((RangeTblFunction *) linitial(rte->functions))->funcexpr;
			toid = exprType(fexpr);
			if (type_is_rowtype(toid))
			{
				/* func returns composite; same as relation case */
				result = makeVar(varno,
								 InvalidAttrNumber,
								 toid,
								 -1,
								 InvalidOid,
								 varlevelsup);
			}
			else if (allowScalar)
			{
				/* func returns scalar; just return its output as-is */
				result = makeVar(varno,
								 1,
								 toid,
								 -1,
								 exprCollation(fexpr),
								 varlevelsup);
			}
			else
			{
				/* func returns scalar, but we want a composite result */
				result = makeVar(varno,
								 InvalidAttrNumber,
								 RECORDOID,
								 -1,
								 InvalidOid,
								 varlevelsup);
			}
			break;

		default:

			/*
			 * RTE is a join, subselect, tablefunc, or VALUES.  We represent
			 * this as a whole-row Var of RECORD type. (Note that in most
			 * cases the Var will be expanded to a RowExpr during planning,
			 * but that is not our concern here.)
			 */
			result = makeVar(varno,
							 InvalidAttrNumber,
							 RECORDOID,
							 -1,
							 InvalidOid,
							 varlevelsup);
			break;
	}

	return result;
}