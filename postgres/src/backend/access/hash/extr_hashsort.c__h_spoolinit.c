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
typedef  int uint32 ;
struct TYPE_3__ {int high_mask; int low_mask; int max_buckets; int /*<<< orphan*/  sortstate; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ HSpool ;

/* Variables and functions */
 int _hash_log2 (int) ; 
 int /*<<< orphan*/  maintenance_work_mem ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  tuplesort_begin_index_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

HSpool *
_h_spoolinit(Relation heap, Relation index, uint32 num_buckets)
{
	HSpool	   *hspool = (HSpool *) palloc0(sizeof(HSpool));

	hspool->index = index;

	/*
	 * Determine the bitmask for hash code values.  Since there are currently
	 * num_buckets buckets in the index, the appropriate mask can be computed
	 * as follows.
	 *
	 * NOTE : This hash mask calculation should be in sync with similar
	 * calculation in _hash_init_metabuffer.
	 */
	hspool->high_mask = (((uint32) 1) << _hash_log2(num_buckets + 1)) - 1;
	hspool->low_mask = (hspool->high_mask >> 1);
	hspool->max_buckets = num_buckets - 1;

	/*
	 * We size the sort area as maintenance_work_mem rather than work_mem to
	 * speed index creation.  This should be OK since a single backend can't
	 * run multiple index creations in parallel.
	 */
	hspool->sortstate = tuplesort_begin_index_hash(heap,
												   index,
												   hspool->high_mask,
												   hspool->low_mask,
												   hspool->max_buckets,
												   maintenance_work_mem,
												   NULL,
												   false);

	return hspool;
}