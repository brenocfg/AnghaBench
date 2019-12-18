#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * steps; scalar_t__ contradictory; } ;
struct TYPE_11__ {int partnatts; scalar_t__ nparts; int /*<<< orphan*/ * exprstates; int /*<<< orphan*/ * planstate; int /*<<< orphan*/  ppccontext; int /*<<< orphan*/ * stepcmpfuncs; int /*<<< orphan*/  partsupfunc; int /*<<< orphan*/  partcollation; int /*<<< orphan*/  boundinfo; int /*<<< orphan*/  strategy; } ;
struct TYPE_10__ {scalar_t__ nparts; TYPE_1__* part_scheme; int /*<<< orphan*/  boundinfo; int /*<<< orphan*/ * baserestrictinfo; } ;
struct TYPE_9__ {int partnatts; int /*<<< orphan*/  partsupfunc; int /*<<< orphan*/  partcollation; int /*<<< orphan*/  strategy; } ;
typedef  TYPE_2__ RelOptInfo ;
typedef  TYPE_3__ PartitionPruneContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ GeneratePruningStepsContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  PARTTARGET_PLANNER ; 
 int /*<<< orphan*/ * bms_add_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  enable_partition_pruning ; 
 int /*<<< orphan*/  gen_partprune_steps (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/ * get_matching_partitions (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

Bitmapset *
prune_append_rel_partitions(RelOptInfo *rel)
{
	List	   *clauses = rel->baserestrictinfo;
	List	   *pruning_steps;
	GeneratePruningStepsContext gcontext;
	PartitionPruneContext context;

	Assert(rel->part_scheme != NULL);

	/* If there are no partitions, return the empty set */
	if (rel->nparts == 0)
		return NULL;

	/*
	 * If pruning is disabled or if there are no clauses to prune with, return
	 * all partitions.
	 */
	if (!enable_partition_pruning || clauses == NIL)
		return bms_add_range(NULL, 0, rel->nparts - 1);

	/*
	 * Process clauses to extract pruning steps that are usable at plan time.
	 * If the clauses are found to be contradictory, we can return the empty
	 * set.
	 */
	gen_partprune_steps(rel, clauses, PARTTARGET_PLANNER,
						&gcontext);
	if (gcontext.contradictory)
		return NULL;
	pruning_steps = gcontext.steps;

	/* If there's nothing usable, return all partitions */
	if (pruning_steps == NIL)
		return bms_add_range(NULL, 0, rel->nparts - 1);

	/* Set up PartitionPruneContext */
	context.strategy = rel->part_scheme->strategy;
	context.partnatts = rel->part_scheme->partnatts;
	context.nparts = rel->nparts;
	context.boundinfo = rel->boundinfo;
	context.partcollation = rel->part_scheme->partcollation;
	context.partsupfunc = rel->part_scheme->partsupfunc;
	context.stepcmpfuncs = (FmgrInfo *) palloc0(sizeof(FmgrInfo) *
												context.partnatts *
												list_length(pruning_steps));
	context.ppccontext = CurrentMemoryContext;

	/* These are not valid when being called from the planner */
	context.planstate = NULL;
	context.exprstates = NULL;

	/* Actual pruning happens here. */
	return get_matching_partitions(&context, pruning_steps);
}