#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_14__ {int /*<<< orphan*/ * es_partition_directory; int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_13__ {int nparts; } ;
struct TYPE_12__ {int* indexes; int /*<<< orphan*/ * tupslot; int /*<<< orphan*/ * tupmap; int /*<<< orphan*/  reldesc; TYPE_3__* partdesc; int /*<<< orphan*/  keystate; int /*<<< orphan*/  key; } ;
struct TYPE_11__ {int num_dispatch; int max_dispatch; TYPE_2__** partition_dispatch_info; int /*<<< orphan*/  partition_root; int /*<<< orphan*/  memcxt; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ PartitionTupleRouting ;
typedef  TYPE_2__* PartitionDispatch ;
typedef  TYPE_3__* PartitionDesc ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * CreatePartitionDirectory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MakeSingleTupleTableSlot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIL ; 
 TYPE_3__* PartitionDirectoryLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PartitionDispatchData ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetPartitionKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/ * convert_tuples_by_name_map_if_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indexes ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ repalloc (TYPE_2__**,int) ; 
 int /*<<< orphan*/  table_open (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PartitionDispatch
ExecInitPartitionDispatchInfo(EState *estate,
							  PartitionTupleRouting *proute, Oid partoid,
							  PartitionDispatch parent_pd, int partidx)
{
	Relation	rel;
	PartitionDesc partdesc;
	PartitionDispatch pd;
	int			dispatchidx;
	MemoryContext oldcxt;

	if (estate->es_partition_directory == NULL)
		estate->es_partition_directory =
			CreatePartitionDirectory(estate->es_query_cxt);

	oldcxt = MemoryContextSwitchTo(proute->memcxt);

	/*
	 * Only sub-partitioned tables need to be locked here.  The root
	 * partitioned table will already have been locked as it's referenced in
	 * the query's rtable.
	 */
	if (partoid != RelationGetRelid(proute->partition_root))
		rel = table_open(partoid, RowExclusiveLock);
	else
		rel = proute->partition_root;
	partdesc = PartitionDirectoryLookup(estate->es_partition_directory, rel);

	pd = (PartitionDispatch) palloc(offsetof(PartitionDispatchData, indexes) +
									partdesc->nparts * sizeof(int));
	pd->reldesc = rel;
	pd->key = RelationGetPartitionKey(rel);
	pd->keystate = NIL;
	pd->partdesc = partdesc;
	if (parent_pd != NULL)
	{
		TupleDesc	tupdesc = RelationGetDescr(rel);

		/*
		 * For sub-partitioned tables where the column order differs from its
		 * direct parent partitioned table, we must store a tuple table slot
		 * initialized with its tuple descriptor and a tuple conversion map to
		 * convert a tuple from its parent's rowtype to its own.  This is to
		 * make sure that we are looking at the correct row using the correct
		 * tuple descriptor when computing its partition key for tuple
		 * routing.
		 */
		pd->tupmap = convert_tuples_by_name_map_if_req(RelationGetDescr(parent_pd->reldesc),
													   tupdesc);
		pd->tupslot = pd->tupmap ?
			MakeSingleTupleTableSlot(tupdesc, &TTSOpsVirtual) : NULL;
	}
	else
	{
		/* Not required for the root partitioned table */
		pd->tupmap = NULL;
		pd->tupslot = NULL;
	}

	/*
	 * Initialize with -1 to signify that the corresponding partition's
	 * ResultRelInfo or PartitionDispatch has not been created yet.
	 */
	memset(pd->indexes, -1, sizeof(int) * partdesc->nparts);

	/* Track in PartitionTupleRouting for later use */
	dispatchidx = proute->num_dispatch++;

	/* Allocate or enlarge the array, as needed */
	if (proute->num_dispatch >= proute->max_dispatch)
	{
		if (proute->max_dispatch == 0)
		{
			proute->max_dispatch = 4;
			proute->partition_dispatch_info = (PartitionDispatch *)
				palloc(sizeof(PartitionDispatch) * proute->max_dispatch);
		}
		else
		{
			proute->max_dispatch *= 2;
			proute->partition_dispatch_info = (PartitionDispatch *)
				repalloc(proute->partition_dispatch_info,
						 sizeof(PartitionDispatch) * proute->max_dispatch);
		}
	}
	proute->partition_dispatch_info[dispatchidx] = pd;

	/*
	 * Finally, if setting up a PartitionDispatch for a sub-partitioned table,
	 * install a downlink in the parent to allow quick descent.
	 */
	if (parent_pd)
	{
		Assert(parent_pd->indexes[partidx] == -1);
		parent_pd->indexes[partidx] = dispatchidx;
	}

	MemoryContextSwitchTo(oldcxt);

	return pd;
}