#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_2__ TupleTableSlot ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_14__ {scalar_t__ attgenerated; scalar_t__ attisdropped; } ;
struct TYPE_10__ {int natts; } ;
struct TYPE_13__ {scalar_t__* attrmap; int /*<<< orphan*/  localrel; TYPE_1__ remoterel; } ;
struct TYPE_12__ {int natts; } ;
typedef  TYPE_4__ LogicalRepRelMapEntry ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEvalExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecInitExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 TYPE_3__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_7__* TupleDescAttr (TYPE_3__*,int) ; 
 scalar_t__ build_column_default (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * expression_planner (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
slot_fill_defaults(LogicalRepRelMapEntry *rel, EState *estate,
				   TupleTableSlot *slot)
{
	TupleDesc	desc = RelationGetDescr(rel->localrel);
	int			num_phys_attrs = desc->natts;
	int			i;
	int			attnum,
				num_defaults = 0;
	int		   *defmap;
	ExprState **defexprs;
	ExprContext *econtext;

	econtext = GetPerTupleExprContext(estate);

	/* We got all the data via replication, no need to evaluate anything. */
	if (num_phys_attrs == rel->remoterel.natts)
		return;

	defmap = (int *) palloc(num_phys_attrs * sizeof(int));
	defexprs = (ExprState **) palloc(num_phys_attrs * sizeof(ExprState *));

	for (attnum = 0; attnum < num_phys_attrs; attnum++)
	{
		Expr	   *defexpr;

		if (TupleDescAttr(desc, attnum)->attisdropped || TupleDescAttr(desc, attnum)->attgenerated)
			continue;

		if (rel->attrmap[attnum] >= 0)
			continue;

		defexpr = (Expr *) build_column_default(rel->localrel, attnum + 1);

		if (defexpr != NULL)
		{
			/* Run the expression through planner */
			defexpr = expression_planner(defexpr);

			/* Initialize executable expression in copycontext */
			defexprs[num_defaults] = ExecInitExpr(defexpr, NULL);
			defmap[num_defaults] = attnum;
			num_defaults++;
		}

	}

	for (i = 0; i < num_defaults; i++)
		slot->tts_values[defmap[i]] =
			ExecEvalExpr(defexprs[i], econtext, &slot->tts_isnull[defmap[i]]);
}