#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * rd_indpred; int /*<<< orphan*/  rd_indexcxt; int /*<<< orphan*/ * rd_indextuple; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_index_indpred ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetPgIndexDescriptor () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 scalar_t__ canonicalize_qual (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 scalar_t__ eval_const_expressions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fix_opfuncids (int /*<<< orphan*/ *) ; 
 scalar_t__ heap_attisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * make_ands_implicit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ stringToNode (char*) ; 

List *
RelationGetIndexPredicate(Relation relation)
{
	List	   *result;
	Datum		predDatum;
	bool		isnull;
	char	   *predString;
	MemoryContext oldcxt;

	/* Quick exit if we already computed the result. */
	if (relation->rd_indpred)
		return copyObject(relation->rd_indpred);

	/* Quick exit if there is nothing to do. */
	if (relation->rd_indextuple == NULL ||
		heap_attisnull(relation->rd_indextuple, Anum_pg_index_indpred, NULL))
		return NIL;

	/*
	 * We build the tree we intend to return in the caller's context. After
	 * successfully completing the work, we copy it into the relcache entry.
	 * This avoids problems if we get some sort of error partway through.
	 */
	predDatum = heap_getattr(relation->rd_indextuple,
							 Anum_pg_index_indpred,
							 GetPgIndexDescriptor(),
							 &isnull);
	Assert(!isnull);
	predString = TextDatumGetCString(predDatum);
	result = (List *) stringToNode(predString);
	pfree(predString);

	/*
	 * Run the expression through const-simplification and canonicalization.
	 * This is not just an optimization, but is necessary, because the planner
	 * will be comparing it to similarly-processed qual clauses, and may fail
	 * to detect valid matches without this.  This must match the processing
	 * done to qual clauses in preprocess_expression()!  (We can skip the
	 * stuff involving subqueries, however, since we don't allow any in index
	 * predicates.)
	 */
	result = (List *) eval_const_expressions(NULL, (Node *) result);

	result = (List *) canonicalize_qual((Expr *) result, false);

	/* Also convert to implicit-AND format */
	result = make_ands_implicit((Expr *) result);

	/* May as well fix opfuncids too */
	fix_opfuncids((Node *) result);

	/* Now save a copy of the completed tree in the relcache entry. */
	oldcxt = MemoryContextSwitchTo(relation->rd_indexcxt);
	relation->rd_indpred = copyObject(result);
	MemoryContextSwitchTo(oldcxt);

	return result;
}