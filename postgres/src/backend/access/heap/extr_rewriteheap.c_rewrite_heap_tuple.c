#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashkey ;
typedef  TYPE_4__* UnresolvedTup ;
struct TYPE_31__ {void* tid; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_5__ TidHashKey ;
struct TYPE_34__ {TYPE_17__* t_data; void* t_self; } ;
struct TYPE_33__ {void* new_tid; } ;
struct TYPE_32__ {int /*<<< orphan*/  rs_old_new_tid_map; int /*<<< orphan*/  rs_unresolved_tups; int /*<<< orphan*/  rs_oldest_xmin; int /*<<< orphan*/  rs_cutoff_multi; int /*<<< orphan*/  rs_freeze_xid; TYPE_3__* rs_old_rel; int /*<<< orphan*/  rs_cxt; } ;
struct TYPE_30__ {void* old_tid; TYPE_8__* tuple; } ;
struct TYPE_29__ {TYPE_2__* rd_rel; } ;
struct TYPE_28__ {int /*<<< orphan*/  relminmxid; int /*<<< orphan*/  relfrozenxid; } ;
struct TYPE_27__ {int /*<<< orphan*/  t_heap; } ;
struct TYPE_26__ {int t_infomask; void* t_ctid; int /*<<< orphan*/  t_infomask2; TYPE_1__ t_choice; } ;
typedef  TYPE_6__* RewriteState ;
typedef  TYPE_7__* OldToNewMapping ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  void* ItemPointerData ;
typedef  int /*<<< orphan*/  HeapTupleFields ;
typedef  TYPE_8__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  HEAP2_XACT_MASK ; 
 int HEAP_UPDATED ; 
 int HEAP_XACT_MASK ; 
 int HEAP_XMAX_INVALID ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_17__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (TYPE_17__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderIndicatesMovedPartitions (TYPE_17__*) ; 
 scalar_t__ HeapTupleHeaderIsOnlyLocked (TYPE_17__*) ; 
 int /*<<< orphan*/  ItemPointerEquals (void**,void**) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (void**) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* hash_search (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 TYPE_8__* heap_copytuple (TYPE_8__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_8__*) ; 
 int /*<<< orphan*/  heap_freeze_tuple (TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logical_rewrite_heap_tuple (TYPE_6__*,void*,TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_heap_insert (TYPE_6__*,TYPE_8__*) ; 

void
rewrite_heap_tuple(RewriteState state,
				   HeapTuple old_tuple, HeapTuple new_tuple)
{
	MemoryContext old_cxt;
	ItemPointerData old_tid;
	TidHashKey	hashkey;
	bool		found;
	bool		free_new;

	old_cxt = MemoryContextSwitchTo(state->rs_cxt);

	/*
	 * Copy the original tuple's visibility information into new_tuple.
	 *
	 * XXX we might later need to copy some t_infomask2 bits, too? Right now,
	 * we intentionally clear the HOT status bits.
	 */
	memcpy(&new_tuple->t_data->t_choice.t_heap,
		   &old_tuple->t_data->t_choice.t_heap,
		   sizeof(HeapTupleFields));

	new_tuple->t_data->t_infomask &= ~HEAP_XACT_MASK;
	new_tuple->t_data->t_infomask2 &= ~HEAP2_XACT_MASK;
	new_tuple->t_data->t_infomask |=
		old_tuple->t_data->t_infomask & HEAP_XACT_MASK;

	/*
	 * While we have our hands on the tuple, we may as well freeze any
	 * eligible xmin or xmax, so that future VACUUM effort can be saved.
	 */
	heap_freeze_tuple(new_tuple->t_data,
					  state->rs_old_rel->rd_rel->relfrozenxid,
					  state->rs_old_rel->rd_rel->relminmxid,
					  state->rs_freeze_xid,
					  state->rs_cutoff_multi);

	/*
	 * Invalid ctid means that ctid should point to the tuple itself. We'll
	 * override it later if the tuple is part of an update chain.
	 */
	ItemPointerSetInvalid(&new_tuple->t_data->t_ctid);

	/*
	 * If the tuple has been updated, check the old-to-new mapping hash table.
	 */
	if (!((old_tuple->t_data->t_infomask & HEAP_XMAX_INVALID) ||
		  HeapTupleHeaderIsOnlyLocked(old_tuple->t_data)) &&
		!HeapTupleHeaderIndicatesMovedPartitions(old_tuple->t_data) &&
		!(ItemPointerEquals(&(old_tuple->t_self),
							&(old_tuple->t_data->t_ctid))))
	{
		OldToNewMapping mapping;

		memset(&hashkey, 0, sizeof(hashkey));
		hashkey.xmin = HeapTupleHeaderGetUpdateXid(old_tuple->t_data);
		hashkey.tid = old_tuple->t_data->t_ctid;

		mapping = (OldToNewMapping)
			hash_search(state->rs_old_new_tid_map, &hashkey,
						HASH_FIND, NULL);

		if (mapping != NULL)
		{
			/*
			 * We've already copied the tuple that t_ctid points to, so we can
			 * set the ctid of this tuple to point to the new location, and
			 * insert it right away.
			 */
			new_tuple->t_data->t_ctid = mapping->new_tid;

			/* We don't need the mapping entry anymore */
			hash_search(state->rs_old_new_tid_map, &hashkey,
						HASH_REMOVE, &found);
			Assert(found);
		}
		else
		{
			/*
			 * We haven't seen the tuple t_ctid points to yet. Stash this
			 * tuple into unresolved_tups to be written later.
			 */
			UnresolvedTup unresolved;

			unresolved = hash_search(state->rs_unresolved_tups, &hashkey,
									 HASH_ENTER, &found);
			Assert(!found);

			unresolved->old_tid = old_tuple->t_self;
			unresolved->tuple = heap_copytuple(new_tuple);

			/*
			 * We can't do anything more now, since we don't know where the
			 * tuple will be written.
			 */
			MemoryContextSwitchTo(old_cxt);
			return;
		}
	}

	/*
	 * Now we will write the tuple, and then check to see if it is the B tuple
	 * in any new or known pair.  When we resolve a known pair, we will be
	 * able to write that pair's A tuple, and then we have to check if it
	 * resolves some other pair.  Hence, we need a loop here.
	 */
	old_tid = old_tuple->t_self;
	free_new = false;

	for (;;)
	{
		ItemPointerData new_tid;

		/* Insert the tuple and find out where it's put in new_heap */
		raw_heap_insert(state, new_tuple);
		new_tid = new_tuple->t_self;

		logical_rewrite_heap_tuple(state, old_tid, new_tuple);

		/*
		 * If the tuple is the updated version of a row, and the prior version
		 * wouldn't be DEAD yet, then we need to either resolve the prior
		 * version (if it's waiting in rs_unresolved_tups), or make an entry
		 * in rs_old_new_tid_map (so we can resolve it when we do see it). The
		 * previous tuple's xmax would equal this one's xmin, so it's
		 * RECENTLY_DEAD if and only if the xmin is not before OldestXmin.
		 */
		if ((new_tuple->t_data->t_infomask & HEAP_UPDATED) &&
			!TransactionIdPrecedes(HeapTupleHeaderGetXmin(new_tuple->t_data),
								   state->rs_oldest_xmin))
		{
			/*
			 * Okay, this is B in an update pair.  See if we've seen A.
			 */
			UnresolvedTup unresolved;

			memset(&hashkey, 0, sizeof(hashkey));
			hashkey.xmin = HeapTupleHeaderGetXmin(new_tuple->t_data);
			hashkey.tid = old_tid;

			unresolved = hash_search(state->rs_unresolved_tups, &hashkey,
									 HASH_FIND, NULL);

			if (unresolved != NULL)
			{
				/*
				 * We have seen and memorized the previous tuple already. Now
				 * that we know where we inserted the tuple its t_ctid points
				 * to, fix its t_ctid and insert it to the new heap.
				 */
				if (free_new)
					heap_freetuple(new_tuple);
				new_tuple = unresolved->tuple;
				free_new = true;
				old_tid = unresolved->old_tid;
				new_tuple->t_data->t_ctid = new_tid;

				/*
				 * We don't need the hash entry anymore, but don't free its
				 * tuple just yet.
				 */
				hash_search(state->rs_unresolved_tups, &hashkey,
							HASH_REMOVE, &found);
				Assert(found);

				/* loop back to insert the previous tuple in the chain */
				continue;
			}
			else
			{
				/*
				 * Remember the new tid of this tuple. We'll use it to set the
				 * ctid when we find the previous tuple in the chain.
				 */
				OldToNewMapping mapping;

				mapping = hash_search(state->rs_old_new_tid_map, &hashkey,
									  HASH_ENTER, &found);
				Assert(!found);

				mapping->new_tid = new_tid;
			}
		}

		/* Done with this (chain of) tuples, for now */
		if (free_new)
			heap_freetuple(new_tuple);
		break;
	}

	MemoryContextSwitchTo(old_cxt);
}