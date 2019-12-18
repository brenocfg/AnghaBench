#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int strategy; int ndatums; } ;
typedef  TYPE_1__* PartitionBoundInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  PARTITION_STRATEGY_LIST 129 
#define  PARTITION_STRATEGY_RANGE 128 
 int partition_bound_accepts_nulls (TYPE_1__*) ; 
 int /*<<< orphan*/  partition_bound_has_default (TYPE_1__*) ; 

bool
partitions_are_ordered(PartitionBoundInfo boundinfo, int nparts)
{
	Assert(boundinfo != NULL);

	switch (boundinfo->strategy)
	{
		case PARTITION_STRATEGY_RANGE:

			/*
			 * RANGE-type partitioning guarantees that the partitions can be
			 * scanned in the order that they're defined in the PartitionDesc
			 * to provide sequential, non-overlapping ranges of tuples.
			 * However, if a DEFAULT partition exists then it doesn't work, as
			 * that could contain tuples from either below or above the
			 * defined range, or tuples belonging to gaps between partitions.
			 */
			if (!partition_bound_has_default(boundinfo))
				return true;
			break;

		case PARTITION_STRATEGY_LIST:

			/*
			 * LIST partitioning can also guarantee ordering, but only if the
			 * partitions don't accept interleaved values.  We could likely
			 * check for this by looping over the PartitionBound's indexes
			 * array to check that the indexes are in order.  For now, let's
			 * just keep it simple and just accept LIST partitioning when
			 * there's no DEFAULT partition, exactly one value per partition,
			 * and optionally a NULL partition that does not accept any other
			 * values.  Such a NULL partition will come last in the
			 * PartitionDesc, and the other partitions will be properly
			 * ordered.  This is a cheap test to make as it does not require
			 * any per-partition processing.  Maybe we'd like to handle more
			 * complex cases in the future.
			 */
			if (partition_bound_has_default(boundinfo))
				return false;

			if (boundinfo->ndatums + partition_bound_accepts_nulls(boundinfo)
				== nparts)
				return true;
			break;

		default:
			/* HASH, or some other strategy */
			break;
	}

	return false;
}