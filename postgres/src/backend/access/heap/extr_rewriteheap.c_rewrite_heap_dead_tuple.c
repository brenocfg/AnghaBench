#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashkey ;
typedef  TYPE_1__* UnresolvedTup ;
struct TYPE_11__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_2__ TidHashKey ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  rs_unresolved_tups; } ;
struct TYPE_10__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_3__* RewriteState ;
typedef  TYPE_4__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

bool
rewrite_heap_dead_tuple(RewriteState state, HeapTuple old_tuple)
{
	/*
	 * If we have already seen an earlier tuple in the update chain that
	 * points to this tuple, let's forget about that earlier tuple. It's in
	 * fact dead as well, our simple xmax < OldestXmin test in
	 * HeapTupleSatisfiesVacuum just wasn't enough to detect it. It happens
	 * when xmin of a tuple is greater than xmax, which sounds
	 * counter-intuitive but is perfectly valid.
	 *
	 * We don't bother to try to detect the situation the other way round,
	 * when we encounter the dead tuple first and then the recently dead one
	 * that points to it. If that happens, we'll have some unmatched entries
	 * in the UnresolvedTups hash table at the end. That can happen anyway,
	 * because a vacuum might have removed the dead tuple in the chain before
	 * us.
	 */
	UnresolvedTup unresolved;
	TidHashKey	hashkey;
	bool		found;

	memset(&hashkey, 0, sizeof(hashkey));
	hashkey.xmin = HeapTupleHeaderGetXmin(old_tuple->t_data);
	hashkey.tid = old_tuple->t_self;

	unresolved = hash_search(state->rs_unresolved_tups, &hashkey,
							 HASH_FIND, NULL);

	if (unresolved != NULL)
	{
		/* Need to free the contained tuple as well as the hashtable entry */
		heap_freetuple(unresolved->tuple);
		hash_search(state->rs_unresolved_tups, &hashkey,
					HASH_REMOVE, &found);
		Assert(found);
		return true;
	}

	return false;
}