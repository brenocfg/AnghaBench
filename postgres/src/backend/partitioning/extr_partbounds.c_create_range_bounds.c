#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int null_index; int default_index; int ndatums; scalar_t__** kind; int* indexes; int /*<<< orphan*/ ** datums; int /*<<< orphan*/  strategy; } ;
struct TYPE_14__ {scalar_t__ strategy; int /*<<< orphan*/  upperdatums; int /*<<< orphan*/  lowerdatums; scalar_t__ is_default; } ;
struct TYPE_13__ {int partnatts; int /*<<< orphan*/ * parttyplen; int /*<<< orphan*/ * parttypbyval; int /*<<< orphan*/ * partcollation; int /*<<< orphan*/ * partsupfunc; int /*<<< orphan*/  strategy; } ;
struct TYPE_12__ {scalar_t__* kind; int index; scalar_t__ lower; int /*<<< orphan*/ * datums; } ;
typedef  scalar_t__ PartitionRangeDatumKind ;
typedef  TYPE_1__ PartitionRangeBound ;
typedef  TYPE_2__* PartitionKey ;
typedef  TYPE_3__ PartitionBoundSpec ;
typedef  TYPE_4__ PartitionBoundInfoData ;
typedef  TYPE_4__* PartitionBoundInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PARTITION_RANGE_DATUM_VALUE ; 
 scalar_t__ PARTITION_STRATEGY_RANGE ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* make_one_partition_rbound (TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  qsort_arg (TYPE_1__**,int,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  qsort_partition_rbound_cmp ; 

__attribute__((used)) static PartitionBoundInfo
create_range_bounds(PartitionBoundSpec **boundspecs, int nparts,
					PartitionKey key, int **mapping)
{
	PartitionBoundInfo boundinfo;
	PartitionRangeBound **rbounds = NULL;
	PartitionRangeBound **all_bounds,
			   *prev;
	int			i,
				k;
	int			ndatums = 0;
	int			default_index = -1;
	int			next_index = 0;

	boundinfo = (PartitionBoundInfoData *)
		palloc0(sizeof(PartitionBoundInfoData));
	boundinfo->strategy = key->strategy;
	/* There is no special null-accepting range partition. */
	boundinfo->null_index = -1;
	/* Will be set correctly below. */
	boundinfo->default_index = -1;

	all_bounds = (PartitionRangeBound **)
		palloc0(2 * nparts * sizeof(PartitionRangeBound *));

	/* Create a unified list of range bounds across all the partitions. */
	ndatums = 0;
	for (i = 0; i < nparts; i++)
	{
		PartitionBoundSpec *spec = boundspecs[i];
		PartitionRangeBound *lower,
				   *upper;

		if (spec->strategy != PARTITION_STRATEGY_RANGE)
			elog(ERROR, "invalid strategy in partition bound spec");

		/*
		 * Note the index of the partition bound spec for the default
		 * partition.  There's no datum to add to the all_bounds array for
		 * this partition.
		 */
		if (spec->is_default)
		{
			default_index = i;
			continue;
		}

		lower = make_one_partition_rbound(key, i, spec->lowerdatums, true);
		upper = make_one_partition_rbound(key, i, spec->upperdatums, false);
		all_bounds[ndatums++] = lower;
		all_bounds[ndatums++] = upper;
	}

	Assert(ndatums == nparts * 2 ||
		   (default_index != -1 && ndatums == (nparts - 1) * 2));

	/* Sort all the bounds in ascending order */
	qsort_arg(all_bounds, ndatums,
			  sizeof(PartitionRangeBound *),
			  qsort_partition_rbound_cmp,
			  (void *) key);

	/* Save distinct bounds from all_bounds into rbounds. */
	rbounds = (PartitionRangeBound **)
		palloc(ndatums * sizeof(PartitionRangeBound *));
	k = 0;
	prev = NULL;
	for (i = 0; i < ndatums; i++)
	{
		PartitionRangeBound *cur = all_bounds[i];
		bool		is_distinct = false;
		int			j;

		/* Is the current bound distinct from the previous one? */
		for (j = 0; j < key->partnatts; j++)
		{
			Datum		cmpval;

			if (prev == NULL || cur->kind[j] != prev->kind[j])
			{
				is_distinct = true;
				break;
			}

			/*
			 * If the bounds are both MINVALUE or MAXVALUE, stop now and treat
			 * them as equal, since any values after this point must be
			 * ignored.
			 */
			if (cur->kind[j] != PARTITION_RANGE_DATUM_VALUE)
				break;

			cmpval = FunctionCall2Coll(&key->partsupfunc[j],
									   key->partcollation[j],
									   cur->datums[j],
									   prev->datums[j]);
			if (DatumGetInt32(cmpval) != 0)
			{
				is_distinct = true;
				break;
			}
		}

		/*
		 * Only if the bound is distinct save it into a temporary array, i.e,
		 * rbounds which is later copied into boundinfo datums array.
		 */
		if (is_distinct)
			rbounds[k++] = all_bounds[i];

		prev = cur;
	}

	/* Update ndatums to hold the count of distinct datums. */
	ndatums = k;

	/*
	 * Add datums to boundinfo.  Canonical indexes are values ranging from 0
	 * to nparts - 1, assigned in that order to each partition's upper bound.
	 * For 'datums' elements that are lower bounds, there is -1 in the
	 * 'indexes' array to signify that no partition exists for the values less
	 * than such a bound and greater than or equal to the previous upper
	 * bound.
	 */
	boundinfo->ndatums = ndatums;
	boundinfo->datums = (Datum **) palloc0(ndatums * sizeof(Datum *));
	boundinfo->kind = (PartitionRangeDatumKind **)
		palloc(ndatums *
			   sizeof(PartitionRangeDatumKind *));

	/*
	 * For range partitioning, an additional value of -1 is stored as the last
	 * element.
	 */
	boundinfo->indexes = (int *) palloc((ndatums + 1) * sizeof(int));

	for (i = 0; i < ndatums; i++)
	{
		int			j;

		boundinfo->datums[i] = (Datum *) palloc(key->partnatts *
												sizeof(Datum));
		boundinfo->kind[i] = (PartitionRangeDatumKind *)
			palloc(key->partnatts *
				   sizeof(PartitionRangeDatumKind));
		for (j = 0; j < key->partnatts; j++)
		{
			if (rbounds[i]->kind[j] == PARTITION_RANGE_DATUM_VALUE)
				boundinfo->datums[i][j] =
					datumCopy(rbounds[i]->datums[j],
							  key->parttypbyval[j],
							  key->parttyplen[j]);
			boundinfo->kind[i][j] = rbounds[i]->kind[j];
		}

		/*
		 * There is no mapping for invalid indexes.
		 *
		 * Any lower bounds in the rbounds array have invalid indexes
		 * assigned, because the values between the previous bound (if there
		 * is one) and this (lower) bound are not part of the range of any
		 * existing partition.
		 */
		if (rbounds[i]->lower)
			boundinfo->indexes[i] = -1;
		else
		{
			int			orig_index = rbounds[i]->index;

			/* If the old index has no mapping, assign one */
			if ((*mapping)[orig_index] == -1)
				(*mapping)[orig_index] = next_index++;

			boundinfo->indexes[i] = (*mapping)[orig_index];
		}
	}

	/* Set the canonical value for default_index, if any. */
	if (default_index != -1)
	{
		Assert(default_index >= 0 && (*mapping)[default_index] == -1);
		(*mapping)[default_index] = next_index++;
		boundinfo->default_index = (*mapping)[default_index];
	}

	/* The extra -1 element. */
	Assert(i == ndatums);
	boundinfo->indexes[i] = -1;

	/* All partitions must now have been assigned canonical indexes. */
	Assert(next_index == nparts);
	return boundinfo;
}