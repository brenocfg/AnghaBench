#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_38__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_31__ {int /*<<< orphan*/  state; } ;
struct TYPE_37__ {TYPE_1__ ps; } ;
struct TYPE_36__ {scalar_t__ nparts; int /*<<< orphan*/ * oids; scalar_t__* is_leaf; } ;
struct TYPE_35__ {size_t* indexes; int /*<<< orphan*/ * tupslot; TYPE_6__* partdesc; int /*<<< orphan*/  reldesc; int /*<<< orphan*/ * tupmap; } ;
struct TYPE_34__ {size_t num_partitions; size_t num_dispatch; scalar_t__ subplan_resultrel_htab; TYPE_3__** partitions; TYPE_5__** partition_dispatch_info; } ;
struct TYPE_33__ {scalar_t__ ri_PartitionCheck; } ;
struct TYPE_32__ {TYPE_3__* rri; } ;
typedef  TYPE_2__ SubplanResultRelHashElem ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_4__ PartitionTupleRouting ;
typedef  TYPE_5__* PartitionDispatch ;
typedef  TYPE_6__* PartitionDesc ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_7__ ModifyTableState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_8__ ExprContext ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CMD_INSERT ; 
 int /*<<< orphan*/  CheckValidResultRel (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_CHECK_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 char* ExecBuildSlotPartitionKeyDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 TYPE_5__* ExecInitPartitionDispatchInfo (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 TYPE_3__* ExecInitPartitionInfo (TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ExecInitRoutingInfo (TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ExecPartitionCheck (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FormPartitionKeyDatum (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 TYPE_8__* GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 int PARTITION_MAX_KEYS ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * execute_attr_map_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_partition_for_tuple (TYPE_5__*,int /*<<< orphan*/ *,int*) ; 
 TYPE_2__* hash_search (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 

ResultRelInfo *
ExecFindPartition(ModifyTableState *mtstate,
				  ResultRelInfo *rootResultRelInfo,
				  PartitionTupleRouting *proute,
				  TupleTableSlot *slot, EState *estate)
{
	PartitionDispatch *pd = proute->partition_dispatch_info;
	Datum		values[PARTITION_MAX_KEYS];
	bool		isnull[PARTITION_MAX_KEYS];
	Relation	rel;
	PartitionDispatch dispatch;
	PartitionDesc partdesc;
	ExprContext *ecxt = GetPerTupleExprContext(estate);
	TupleTableSlot *ecxt_scantuple_old = ecxt->ecxt_scantuple;
	TupleTableSlot *myslot = NULL;
	MemoryContext oldcxt;

	/* use per-tuple context here to avoid leaking memory */
	oldcxt = MemoryContextSwitchTo(GetPerTupleMemoryContext(estate));

	/*
	 * First check the root table's partition constraint, if any.  No point in
	 * routing the tuple if it doesn't belong in the root table itself.
	 */
	if (rootResultRelInfo->ri_PartitionCheck)
		ExecPartitionCheck(rootResultRelInfo, slot, estate, true);

	/* start with the root partitioned table */
	dispatch = pd[0];
	while (true)
	{
		AttrNumber *map = dispatch->tupmap;
		int			partidx = -1;

		CHECK_FOR_INTERRUPTS();

		rel = dispatch->reldesc;
		partdesc = dispatch->partdesc;

		/*
		 * Convert the tuple to this parent's layout, if different from the
		 * current relation.
		 */
		myslot = dispatch->tupslot;
		if (myslot != NULL)
		{
			Assert(map != NULL);
			slot = execute_attr_map_slot(map, slot, myslot);
		}

		/*
		 * Extract partition key from tuple. Expression evaluation machinery
		 * that FormPartitionKeyDatum() invokes expects ecxt_scantuple to
		 * point to the correct tuple slot.  The slot might have changed from
		 * what was used for the parent table if the table of the current
		 * partitioning level has different tuple descriptor from the parent.
		 * So update ecxt_scantuple accordingly.
		 */
		ecxt->ecxt_scantuple = slot;
		FormPartitionKeyDatum(dispatch, slot, estate, values, isnull);

		/*
		 * If this partitioned table has no partitions or no partition for
		 * these values, error out.
		 */
		if (partdesc->nparts == 0 ||
			(partidx = get_partition_for_tuple(dispatch, values, isnull)) < 0)
		{
			char	   *val_desc;

			val_desc = ExecBuildSlotPartitionKeyDescription(rel,
															values, isnull, 64);
			Assert(OidIsValid(RelationGetRelid(rel)));
			ereport(ERROR,
					(errcode(ERRCODE_CHECK_VIOLATION),
					 errmsg("no partition of relation \"%s\" found for row",
							RelationGetRelationName(rel)),
					 val_desc ?
					 errdetail("Partition key of the failing row contains %s.",
							   val_desc) : 0));
		}

		if (partdesc->is_leaf[partidx])
		{
			ResultRelInfo *rri;

			/*
			 * Look to see if we've already got a ResultRelInfo for this
			 * partition.
			 */
			if (likely(dispatch->indexes[partidx] >= 0))
			{
				/* ResultRelInfo already built */
				Assert(dispatch->indexes[partidx] < proute->num_partitions);
				rri = proute->partitions[dispatch->indexes[partidx]];
			}
			else
			{
				bool		found = false;

				/*
				 * We have not yet set up a ResultRelInfo for this partition,
				 * but if we have a subplan hash table, we might have one
				 * there.  If not, we'll have to create one.
				 */
				if (proute->subplan_resultrel_htab)
				{
					Oid			partoid = partdesc->oids[partidx];
					SubplanResultRelHashElem *elem;

					elem = hash_search(proute->subplan_resultrel_htab,
									   &partoid, HASH_FIND, NULL);
					if (elem)
					{
						found = true;
						rri = elem->rri;

						/* Verify this ResultRelInfo allows INSERTs */
						CheckValidResultRel(rri, CMD_INSERT);

						/* Set up the PartitionRoutingInfo for it */
						ExecInitRoutingInfo(mtstate, estate, proute, dispatch,
											rri, partidx);
					}
				}

				/* We need to create a new one. */
				if (!found)
					rri = ExecInitPartitionInfo(mtstate, estate, proute,
												dispatch,
												rootResultRelInfo, partidx);
			}

			/* Release the tuple in the lowest parent's dedicated slot. */
			if (slot == myslot)
				ExecClearTuple(myslot);

			MemoryContextSwitchTo(oldcxt);
			ecxt->ecxt_scantuple = ecxt_scantuple_old;
			return rri;
		}
		else
		{
			/*
			 * Partition is a sub-partitioned table; get the PartitionDispatch
			 */
			if (likely(dispatch->indexes[partidx] >= 0))
			{
				/* Already built. */
				Assert(dispatch->indexes[partidx] < proute->num_dispatch);

				/*
				 * Move down to the next partition level and search again
				 * until we find a leaf partition that matches this tuple
				 */
				dispatch = pd[dispatch->indexes[partidx]];
			}
			else
			{
				/* Not yet built. Do that now. */
				PartitionDispatch subdispatch;

				/*
				 * Create the new PartitionDispatch.  We pass the current one
				 * in as the parent PartitionDispatch
				 */
				subdispatch = ExecInitPartitionDispatchInfo(mtstate->ps.state,
															proute,
															partdesc->oids[partidx],
															dispatch, partidx);
				Assert(dispatch->indexes[partidx] >= 0 &&
					   dispatch->indexes[partidx] < proute->num_dispatch);
				dispatch = subdispatch;
			}
		}
	}
}