#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_9__ {int* indexes; scalar_t__ ndatums; } ;
struct TYPE_8__ {int partnatts; scalar_t__ strategy; int /*<<< orphan*/ * partcollation; TYPE_3__* boundinfo; } ;
struct TYPE_7__ {int scan_null; int scan_default; int /*<<< orphan*/  bound_offsets; } ;
typedef  scalar_t__ StrategyNumber ;
typedef  TYPE_1__ PruneStepResult ;
typedef  TYPE_2__ PartitionPruneContext ;
typedef  TYPE_3__* PartitionBoundInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ HTEqualStrategyNumber ; 
 int PARTITION_MAX_KEYS ; 
 scalar_t__ PARTITION_STRATEGY_HASH ; 
 int /*<<< orphan*/  bms_add_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int bms_is_member (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_make_singleton (int) ; 
 int bms_num_members (int /*<<< orphan*/ *) ; 
 int compute_partition_hash_value (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int get_hash_partition_greatest_modulus (TYPE_3__*) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static PruneStepResult *
get_matching_hash_bounds(PartitionPruneContext *context,
						 StrategyNumber opstrategy, Datum *values, int nvalues,
						 FmgrInfo *partsupfunc, Bitmapset *nullkeys)
{
	PruneStepResult *result = (PruneStepResult *) palloc0(sizeof(PruneStepResult));
	PartitionBoundInfo boundinfo = context->boundinfo;
	int		   *partindices = boundinfo->indexes;
	int			partnatts = context->partnatts;
	bool		isnull[PARTITION_MAX_KEYS];
	int			i;
	uint64		rowHash;
	int			greatest_modulus;
	Oid		   *partcollation = context->partcollation;

	Assert(context->strategy == PARTITION_STRATEGY_HASH);

	/*
	 * For hash partitioning we can only perform pruning based on equality
	 * clauses to the partition key or IS NULL clauses.  We also can only
	 * prune if we got values for all keys.
	 */
	if (nvalues + bms_num_members(nullkeys) == partnatts)
	{
		/*
		 * If there are any values, they must have come from clauses
		 * containing an equality operator compatible with hash partitioning.
		 */
		Assert(opstrategy == HTEqualStrategyNumber || nvalues == 0);

		for (i = 0; i < partnatts; i++)
			isnull[i] = bms_is_member(i, nullkeys);

		greatest_modulus = get_hash_partition_greatest_modulus(boundinfo);
		rowHash = compute_partition_hash_value(partnatts, partsupfunc, partcollation,
											   values, isnull);

		if (partindices[rowHash % greatest_modulus] >= 0)
			result->bound_offsets =
				bms_make_singleton(rowHash % greatest_modulus);
	}
	else
	{
		/* Getting here means at least one hash partition exists. */
		Assert(boundinfo->ndatums > 0);
		result->bound_offsets = bms_add_range(NULL, 0,
											  boundinfo->ndatums - 1);
	}

	/*
	 * There is neither a special hash null partition or the default hash
	 * partition.
	 */
	result->scan_null = result->scan_default = false;

	return result;
}