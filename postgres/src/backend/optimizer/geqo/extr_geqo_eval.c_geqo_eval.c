#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct HTAB {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  total_cost; } ;
struct TYPE_8__ {struct HTAB* join_rel_hash; int /*<<< orphan*/  join_rel_list; int /*<<< orphan*/ * join_rel_level; } ;
struct TYPE_7__ {TYPE_3__* cheapest_total_path; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  TYPE_3__ Path ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Gene ;
typedef  int /*<<< orphan*/  Cost ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DBL_MAX ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_1__* gimme_tree (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_truncate (int /*<<< orphan*/ ,int) ; 

Cost
geqo_eval(PlannerInfo *root, Gene *tour, int num_gene)
{
	MemoryContext mycontext;
	MemoryContext oldcxt;
	RelOptInfo *joinrel;
	Cost		fitness;
	int			savelength;
	struct HTAB *savehash;

	/*
	 * Create a private memory context that will hold all temp storage
	 * allocated inside gimme_tree().
	 *
	 * Since geqo_eval() will be called many times, we can't afford to let all
	 * that memory go unreclaimed until end of statement.  Note we make the
	 * temp context a child of the planner's normal context, so that it will
	 * be freed even if we abort via ereport(ERROR).
	 */
	mycontext = AllocSetContextCreate(CurrentMemoryContext,
									  "GEQO",
									  ALLOCSET_DEFAULT_SIZES);
	oldcxt = MemoryContextSwitchTo(mycontext);

	/*
	 * gimme_tree will add entries to root->join_rel_list, which may or may
	 * not already contain some entries.  The newly added entries will be
	 * recycled by the MemoryContextDelete below, so we must ensure that the
	 * list is restored to its former state before exiting.  We can do this by
	 * truncating the list to its original length.  NOTE this assumes that any
	 * added entries are appended at the end!
	 *
	 * We also must take care not to mess up the outer join_rel_hash, if there
	 * is one.  We can do this by just temporarily setting the link to NULL.
	 * (If we are dealing with enough join rels, which we very likely are, a
	 * new hash table will get built and used locally.)
	 *
	 * join_rel_level[] shouldn't be in use, so just Assert it isn't.
	 */
	savelength = list_length(root->join_rel_list);
	savehash = root->join_rel_hash;
	Assert(root->join_rel_level == NULL);

	root->join_rel_hash = NULL;

	/* construct the best path for the given combination of relations */
	joinrel = gimme_tree(root, tour, num_gene);

	/*
	 * compute fitness, if we found a valid join
	 *
	 * XXX geqo does not currently support optimization for partial result
	 * retrieval, nor do we take any cognizance of possible use of
	 * parameterized paths --- how to fix?
	 */
	if (joinrel)
	{
		Path	   *best_path = joinrel->cheapest_total_path;

		fitness = best_path->total_cost;
	}
	else
		fitness = DBL_MAX;

	/*
	 * Restore join_rel_list to its former state, and put back original
	 * hashtable if any.
	 */
	root->join_rel_list = list_truncate(root->join_rel_list,
										savelength);
	root->join_rel_hash = savehash;

	/* release all the memory acquired within gimme_tree */
	MemoryContextSwitchTo(oldcxt);
	MemoryContextDelete(mycontext);

	return fitness;
}