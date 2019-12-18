#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_21__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ fn_oid; } ;
struct TYPE_26__ {int partnatts; int strategy; TYPE_5__* stepcmpfuncs; int /*<<< orphan*/  ppccontext; TYPE_21__* partsupfunc; } ;
struct TYPE_22__ {int /*<<< orphan*/  step_id; } ;
struct TYPE_25__ {int /*<<< orphan*/  nullkeys; int /*<<< orphan*/  opstrategy; TYPE_1__ step; int /*<<< orphan*/  cmpfns; int /*<<< orphan*/  exprs; } ;
struct TYPE_24__ {int scan_default; int scan_null; int /*<<< orphan*/ * bound_offsets; } ;
struct TYPE_23__ {scalar_t__ fn_oid; } ;
typedef  TYPE_2__ PruneStepResult ;
typedef  TYPE_3__ PartitionPruneStepOp ;
typedef  TYPE_4__ PartitionPruneContext ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_5__ FmgrInfo ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int OidIsValid (scalar_t__) ; 
 int PARTITION_MAX_KEYS ; 
#define  PARTITION_STRATEGY_HASH 130 
#define  PARTITION_STRATEGY_LIST 129 
#define  PARTITION_STRATEGY_RANGE 128 
 int PruneCxtStateIdx (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bms_is_member (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fmgr_info_copy (TYPE_5__*,TYPE_21__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_cxt (scalar_t__,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_matching_hash_bounds (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_matching_list_bounds (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_matching_range_bounds (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lfirst (int /*<<< orphan*/ *) ; 
 scalar_t__ lfirst_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ ) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  partkey_datum_from_expr (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static PruneStepResult *
perform_pruning_base_step(PartitionPruneContext *context,
						  PartitionPruneStepOp *opstep)
{
	ListCell   *lc1,
			   *lc2;
	int			keyno,
				nvalues;
	Datum		values[PARTITION_MAX_KEYS];
	FmgrInfo   *partsupfunc;
	int			stateidx;

	/*
	 * There better be the same number of expressions and compare functions.
	 */
	Assert(list_length(opstep->exprs) == list_length(opstep->cmpfns));

	nvalues = 0;
	lc1 = list_head(opstep->exprs);
	lc2 = list_head(opstep->cmpfns);

	/*
	 * Generate the partition lookup key that will be used by one of the
	 * get_matching_*_bounds functions called below.
	 */
	for (keyno = 0; keyno < context->partnatts; keyno++)
	{
		/*
		 * For hash partitioning, it is possible that values of some keys are
		 * not provided in operator clauses, but instead the planner found
		 * that they appeared in a IS NULL clause.
		 */
		if (bms_is_member(keyno, opstep->nullkeys))
			continue;

		/*
		 * For range partitioning, we must only perform pruning with values
		 * for either all partition keys or a prefix thereof.
		 */
		if (keyno > nvalues && context->strategy == PARTITION_STRATEGY_RANGE)
			break;

		if (lc1 != NULL)
		{
			Expr	   *expr;
			Datum		datum;
			bool		isnull;
			Oid			cmpfn;

			expr = lfirst(lc1);
			stateidx = PruneCxtStateIdx(context->partnatts,
										opstep->step.step_id, keyno);
			partkey_datum_from_expr(context, expr, stateidx,
									&datum, &isnull);

			/*
			 * Since we only allow strict operators in pruning steps, any
			 * null-valued comparison value must cause the comparison to fail,
			 * so that no partitions could match.
			 */
			if (isnull)
			{
				PruneStepResult *result;

				result = (PruneStepResult *) palloc(sizeof(PruneStepResult));
				result->bound_offsets = NULL;
				result->scan_default = false;
				result->scan_null = false;

				return result;
			}

			/* Set up the stepcmpfuncs entry, unless we already did */
			cmpfn = lfirst_oid(lc2);
			Assert(OidIsValid(cmpfn));
			if (cmpfn != context->stepcmpfuncs[stateidx].fn_oid)
			{
				/*
				 * If the needed support function is the same one cached in
				 * the relation's partition key, copy the cached FmgrInfo.
				 * Otherwise (i.e., when we have a cross-type comparison), an
				 * actual lookup is required.
				 */
				if (cmpfn == context->partsupfunc[keyno].fn_oid)
					fmgr_info_copy(&context->stepcmpfuncs[stateidx],
								   &context->partsupfunc[keyno],
								   context->ppccontext);
				else
					fmgr_info_cxt(cmpfn, &context->stepcmpfuncs[stateidx],
								  context->ppccontext);
			}

			values[keyno] = datum;
			nvalues++;

			lc1 = lnext(opstep->exprs, lc1);
			lc2 = lnext(opstep->cmpfns, lc2);
		}
	}

	/*
	 * Point partsupfunc to the entry for the 0th key of this step; the
	 * additional support functions, if any, follow consecutively.
	 */
	stateidx = PruneCxtStateIdx(context->partnatts, opstep->step.step_id, 0);
	partsupfunc = &context->stepcmpfuncs[stateidx];

	switch (context->strategy)
	{
		case PARTITION_STRATEGY_HASH:
			return get_matching_hash_bounds(context,
											opstep->opstrategy,
											values, nvalues,
											partsupfunc,
											opstep->nullkeys);

		case PARTITION_STRATEGY_LIST:
			return get_matching_list_bounds(context,
											opstep->opstrategy,
											values[0], nvalues,
											&partsupfunc[0],
											opstep->nullkeys);

		case PARTITION_STRATEGY_RANGE:
			return get_matching_range_bounds(context,
											 opstep->opstrategy,
											 values, nvalues,
											 partsupfunc,
											 opstep->nullkeys);

		default:
			elog(ERROR, "unexpected partition strategy: %d",
				 (int) context->strategy);
			break;
	}

	return NULL;
}