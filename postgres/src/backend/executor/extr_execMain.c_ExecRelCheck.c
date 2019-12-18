#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_20__ {char const* ccname; int /*<<< orphan*/  ccbin; } ;
struct TYPE_19__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_18__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_17__ {TYPE_2__* rd_att; } ;
struct TYPE_16__ {int /*<<< orphan*/ ** ri_ConstraintExprs; TYPE_4__* ri_RelationDesc; } ;
struct TYPE_15__ {TYPE_1__* constr; } ;
struct TYPE_14__ {int num_check; TYPE_7__* check; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_5__ ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_6__ EState ;
typedef  TYPE_7__ ConstrCheck ;

/* Variables and functions */
 int /*<<< orphan*/  ExecCheck (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * ExecPrepareExpr (int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_5__* GetPerTupleExprContext (TYPE_6__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * stringToNode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
ExecRelCheck(ResultRelInfo *resultRelInfo,
			 TupleTableSlot *slot, EState *estate)
{
	Relation	rel = resultRelInfo->ri_RelationDesc;
	int			ncheck = rel->rd_att->constr->num_check;
	ConstrCheck *check = rel->rd_att->constr->check;
	ExprContext *econtext;
	MemoryContext oldContext;
	int			i;

	/*
	 * If first time through for this result relation, build expression
	 * nodetrees for rel's constraint expressions.  Keep them in the per-query
	 * memory context so they'll survive throughout the query.
	 */
	if (resultRelInfo->ri_ConstraintExprs == NULL)
	{
		oldContext = MemoryContextSwitchTo(estate->es_query_cxt);
		resultRelInfo->ri_ConstraintExprs =
			(ExprState **) palloc(ncheck * sizeof(ExprState *));
		for (i = 0; i < ncheck; i++)
		{
			Expr	   *checkconstr;

			checkconstr = stringToNode(check[i].ccbin);
			resultRelInfo->ri_ConstraintExprs[i] =
				ExecPrepareExpr(checkconstr, estate);
		}
		MemoryContextSwitchTo(oldContext);
	}

	/*
	 * We will use the EState's per-tuple context for evaluating constraint
	 * expressions (creating it if it's not already there).
	 */
	econtext = GetPerTupleExprContext(estate);

	/* Arrange for econtext's scan tuple to be the tuple under test */
	econtext->ecxt_scantuple = slot;

	/* And evaluate the constraints */
	for (i = 0; i < ncheck; i++)
	{
		ExprState  *checkconstr = resultRelInfo->ri_ConstraintExprs[i];

		/*
		 * NOTE: SQL specifies that a NULL result from a constraint expression
		 * is not to be treated as a failure.  Therefore, use ExecCheck not
		 * ExecQual.
		 */
		if (!ExecCheck(checkconstr, econtext))
			return check[i].ccname;
	}

	/* NULL result means no error */
	return NULL;
}