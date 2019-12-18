#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int rd_partcheckvalid; int /*<<< orphan*/ * rd_partcheck; int /*<<< orphan*/ * rd_partcheckcxt; TYPE_1__* rd_rel; } ;
struct TYPE_12__ {scalar_t__ relispartition; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Anum_pg_class_relpartbound ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextCopyAndSetIdentifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NoLock ; 
 int PartitionBoundSpec ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int bound ; 
 int /*<<< orphan*/  castNode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_partition_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_qual_from_partbound (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * list_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_partition_varattnos (int /*<<< orphan*/ *,int,TYPE_2__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stringToNode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static List *
generate_partition_qual(Relation rel)
{
	HeapTuple	tuple;
	MemoryContext oldcxt;
	Datum		boundDatum;
	bool		isnull;
	List	   *my_qual = NIL,
			   *result = NIL;
	Relation	parent;
	bool		found_whole_row;

	/* Guard against stack overflow due to overly deep partition tree */
	check_stack_depth();

	/* If we already cached the result, just return a copy */
	if (rel->rd_partcheckvalid)
		return copyObject(rel->rd_partcheck);

	/* Grab at least an AccessShareLock on the parent table */
	parent = relation_open(get_partition_parent(RelationGetRelid(rel)),
						   AccessShareLock);

	/* Get pg_class.relpartbound */
	tuple = SearchSysCache1(RELOID, RelationGetRelid(rel));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u",
			 RelationGetRelid(rel));

	boundDatum = SysCacheGetAttr(RELOID, tuple,
								 Anum_pg_class_relpartbound,
								 &isnull);
	if (!isnull)
	{
		PartitionBoundSpec *bound;

		bound = castNode(PartitionBoundSpec,
						 stringToNode(TextDatumGetCString(boundDatum)));

		my_qual = get_qual_from_partbound(rel, parent, bound);
	}

	ReleaseSysCache(tuple);

	/* Add the parent's quals to the list (if any) */
	if (parent->rd_rel->relispartition)
		result = list_concat(generate_partition_qual(parent), my_qual);
	else
		result = my_qual;

	/*
	 * Change Vars to have partition's attnos instead of the parent's. We do
	 * this after we concatenate the parent's quals, because we want every Var
	 * in it to bear this relation's attnos. It's safe to assume varno = 1
	 * here.
	 */
	result = map_partition_varattnos(result, 1, rel, parent,
									 &found_whole_row);
	/* There can never be a whole-row reference here */
	if (found_whole_row)
		elog(ERROR, "unexpected whole-row reference found in partition key");

	/* Assert that we're not leaking any old data during assignments below */
	Assert(rel->rd_partcheckcxt == NULL);
	Assert(rel->rd_partcheck == NIL);

	/*
	 * Save a copy in the relcache.  The order of these operations is fairly
	 * critical to avoid memory leaks and ensure that we don't leave a corrupt
	 * relcache entry if we fail partway through copyObject.
	 *
	 * If, as is definitely possible, the partcheck list is NIL, then we do
	 * not need to make a context to hold it.
	 */
	if (result != NIL)
	{
		rel->rd_partcheckcxt = AllocSetContextCreate(CacheMemoryContext,
													 "partition constraint",
													 ALLOCSET_SMALL_SIZES);
		MemoryContextCopyAndSetIdentifier(rel->rd_partcheckcxt,
										  RelationGetRelationName(rel));
		oldcxt = MemoryContextSwitchTo(rel->rd_partcheckcxt);
		rel->rd_partcheck = copyObject(result);
		MemoryContextSwitchTo(oldcxt);
	}
	else
		rel->rd_partcheck = NIL;
	rel->rd_partcheckvalid = true;

	/* Keep the parent locked until commit */
	relation_close(parent, NoLock);

	/* Return the working copy to the caller */
	return result;
}