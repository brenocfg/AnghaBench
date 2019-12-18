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
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecBuildGroupingEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_opcode (int /*<<< orphan*/  const) ; 
 scalar_t__ palloc (int) ; 

ExprState *
execTuplesMatchPrepare(TupleDesc desc,
					   int numCols,
					   const AttrNumber *keyColIdx,
					   const Oid *eqOperators,
					   const Oid *collations,
					   PlanState *parent)
{
	Oid		   *eqFunctions = (Oid *) palloc(numCols * sizeof(Oid));
	int			i;
	ExprState  *expr;

	if (numCols == 0)
		return NULL;

	/* lookup equality functions */
	for (i = 0; i < numCols; i++)
		eqFunctions[i] = get_opcode(eqOperators[i]);

	/* build actual expression */
	expr = ExecBuildGroupingEqual(desc, desc, NULL, NULL,
								  numCols, keyColIdx, eqFunctions, collations,
								  parent);

	return expr;
}