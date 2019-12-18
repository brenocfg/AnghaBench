#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleHashTableData ;
typedef  TYPE_1__* TupleHashTable ;
typedef  int /*<<< orphan*/  TupleHashEntryData ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int numCols; long entrysize; int /*<<< orphan*/  exprcontext; int /*<<< orphan*/  tab_eq_func; int /*<<< orphan*/ * tableslot; int /*<<< orphan*/  hashtab; scalar_t__ hash_iv; int /*<<< orphan*/ * cur_eq_func; int /*<<< orphan*/ * in_hash_funcs; int /*<<< orphan*/ * inputslot; scalar_t__ tempcxt; scalar_t__ tablecxt; int /*<<< orphan*/ * tab_collations; int /*<<< orphan*/ * tab_hash_funcs; int /*<<< orphan*/ * keyColIdx; } ;
typedef  long Size ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ MemoryContext ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateStandaloneExprContext () ; 
 int /*<<< orphan*/  CreateTupleDescCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecBuildGroupingEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MakeSingleTupleTableSlot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MemoryContextSwitchTo (scalar_t__) ; 
 long Min (long,long) ; 
 int /*<<< orphan*/  ParallelWorkerNumber ; 
 int /*<<< orphan*/  TTSOpsMinimalTuple ; 
 scalar_t__ murmurhash32 (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  tuplehash_create (scalar_t__,long,TYPE_1__*) ; 
 long work_mem ; 

TupleHashTable
BuildTupleHashTableExt(PlanState *parent,
					   TupleDesc inputDesc,
					   int numCols, AttrNumber *keyColIdx,
					   const Oid *eqfuncoids,
					   FmgrInfo *hashfunctions,
					   Oid *collations,
					   long nbuckets, Size additionalsize,
					   MemoryContext metacxt,
					   MemoryContext tablecxt,
					   MemoryContext tempcxt,
					   bool use_variable_hash_iv)
{
	TupleHashTable hashtable;
	Size		entrysize = sizeof(TupleHashEntryData) + additionalsize;
	MemoryContext oldcontext;
	bool		allow_jit;

	Assert(nbuckets > 0);

	/* Limit initial table size request to not more than work_mem */
	nbuckets = Min(nbuckets, (long) ((work_mem * 1024L) / entrysize));

	oldcontext = MemoryContextSwitchTo(metacxt);

	hashtable = (TupleHashTable) palloc(sizeof(TupleHashTableData));

	hashtable->numCols = numCols;
	hashtable->keyColIdx = keyColIdx;
	hashtable->tab_hash_funcs = hashfunctions;
	hashtable->tab_collations = collations;
	hashtable->tablecxt = tablecxt;
	hashtable->tempcxt = tempcxt;
	hashtable->entrysize = entrysize;
	hashtable->tableslot = NULL;	/* will be made on first lookup */
	hashtable->inputslot = NULL;
	hashtable->in_hash_funcs = NULL;
	hashtable->cur_eq_func = NULL;

	/*
	 * If parallelism is in use, even if the master backend is performing the
	 * scan itself, we don't want to create the hashtable exactly the same way
	 * in all workers. As hashtables are iterated over in keyspace-order,
	 * doing so in all processes in the same way is likely to lead to
	 * "unbalanced" hashtables when the table size initially is
	 * underestimated.
	 */
	if (use_variable_hash_iv)
		hashtable->hash_iv = murmurhash32(ParallelWorkerNumber);
	else
		hashtable->hash_iv = 0;

	hashtable->hashtab = tuplehash_create(metacxt, nbuckets, hashtable);

	/*
	 * We copy the input tuple descriptor just for safety --- we assume all
	 * input tuples will have equivalent descriptors.
	 */
	hashtable->tableslot = MakeSingleTupleTableSlot(CreateTupleDescCopy(inputDesc),
													&TTSOpsMinimalTuple);

	/*
	 * If the old reset interface is used (i.e. BuildTupleHashTable, rather
	 * than BuildTupleHashTableExt), allowing JIT would lead to the generated
	 * functions to a) live longer than the query b) be re-generated each time
	 * the table is being reset. Therefore prevent JIT from being used in that
	 * case, by not providing a parent node (which prevents accessing the
	 * JitContext in the EState).
	 */
	allow_jit = metacxt != tablecxt;

	/* build comparator for all columns */
	/* XXX: should we support non-minimal tuples for the inputslot? */
	hashtable->tab_eq_func = ExecBuildGroupingEqual(inputDesc, inputDesc,
													&TTSOpsMinimalTuple, &TTSOpsMinimalTuple,
													numCols,
													keyColIdx, eqfuncoids, collations,
													allow_jit ? parent : NULL);

	/*
	 * While not pretty, it's ok to not shut down this context, but instead
	 * rely on the containing memory context being reset, as
	 * ExecBuildGroupingEqual() only builds a very simple expression calling
	 * functions (i.e. nothing that'd employ RegisterExprContextCallback()).
	 */
	hashtable->exprcontext = CreateStandaloneExprContext();

	MemoryContextSwitchTo(oldcontext);

	return hashtable;
}