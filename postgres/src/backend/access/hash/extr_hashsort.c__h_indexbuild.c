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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ int64 ;
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  low_mask; int /*<<< orphan*/  high_mask; int /*<<< orphan*/  max_buckets; int /*<<< orphan*/  sortstate; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * IndexTuple ;
typedef  TYPE_1__ HSpool ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  PROGRESS_CREATEIDX_TUPLES_DONE ; 
 int /*<<< orphan*/  _hash_doinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_get_indextuple_hashkey (int /*<<< orphan*/ *) ; 
 scalar_t__ _hash_hashkey2bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * tuplesort_getindextuple (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tuplesort_performsort (int /*<<< orphan*/ ) ; 

void
_h_indexbuild(HSpool *hspool, Relation heapRel)
{
	IndexTuple	itup;
	int64		tups_done = 0;
#ifdef USE_ASSERT_CHECKING
	uint32		hashkey = 0;
#endif

	tuplesort_performsort(hspool->sortstate);

	while ((itup = tuplesort_getindextuple(hspool->sortstate, true)) != NULL)
	{
		/*
		 * Technically, it isn't critical that hash keys be found in sorted
		 * order, since this sorting is only used to increase locality of
		 * access as a performance optimization.  It still seems like a good
		 * idea to test tuplesort.c's handling of hash index tuple sorts
		 * through an assertion, though.
		 */
#ifdef USE_ASSERT_CHECKING
		uint32		lasthashkey = hashkey;

		hashkey = _hash_hashkey2bucket(_hash_get_indextuple_hashkey(itup),
									   hspool->max_buckets, hspool->high_mask,
									   hspool->low_mask);
		Assert(hashkey >= lasthashkey);
#endif

		_hash_doinsert(hspool->index, itup, heapRel);

		pgstat_progress_update_param(PROGRESS_CREATEIDX_TUPLES_DONE,
									 ++tups_done);
	}
}