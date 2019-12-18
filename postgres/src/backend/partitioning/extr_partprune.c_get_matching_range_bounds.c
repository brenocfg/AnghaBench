#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_10__ {int* indexes; int ndatums; scalar_t__** kind; int /*<<< orphan*/ * datums; } ;
struct TYPE_9__ {int partnatts; scalar_t__ strategy; int /*<<< orphan*/ * partcollation; TYPE_3__* boundinfo; } ;
struct TYPE_8__ {int scan_null; int scan_default; void* bound_offsets; } ;
typedef  int StrategyNumber ;
typedef  TYPE_1__ PruneStepResult ;
typedef  TYPE_2__ PartitionPruneContext ;
typedef  TYPE_3__* PartitionBoundInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  BTEqualStrategyNumber 132 
#define  BTGreaterEqualStrategyNumber 131 
#define  BTGreaterStrategyNumber 130 
#define  BTLessEqualStrategyNumber 129 
#define  BTLessStrategyNumber 128 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PARTITION_RANGE_DATUM_MAXVALUE ; 
 scalar_t__ PARTITION_RANGE_DATUM_MINVALUE ; 
 scalar_t__ PARTITION_STRATEGY_RANGE ; 
 void* bms_add_range (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ *) ; 
 void* bms_make_singleton (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ palloc0 (int) ; 
 void* partition_bound_has_default (TYPE_3__*) ; 
 int partition_range_datum_bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  partition_rbound_datum_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PruneStepResult *
get_matching_range_bounds(PartitionPruneContext *context,
						  StrategyNumber opstrategy, Datum *values, int nvalues,
						  FmgrInfo *partsupfunc, Bitmapset *nullkeys)
{
	PruneStepResult *result = (PruneStepResult *) palloc0(sizeof(PruneStepResult));
	PartitionBoundInfo boundinfo = context->boundinfo;
	Oid		   *partcollation = context->partcollation;
	int			partnatts = context->partnatts;
	int		   *partindices = boundinfo->indexes;
	int			off,
				minoff,
				maxoff;
	bool		is_equal;
	bool		inclusive = false;

	Assert(context->strategy == PARTITION_STRATEGY_RANGE);
	Assert(nvalues <= partnatts);

	result->scan_null = result->scan_default = false;

	/*
	 * If there are no datums to compare keys with, or if we got an IS NULL
	 * clause just return the default partition, if it exists.
	 */
	if (boundinfo->ndatums == 0 || !bms_is_empty(nullkeys))
	{
		result->scan_default = partition_bound_has_default(boundinfo);
		return result;
	}

	minoff = 0;
	maxoff = boundinfo->ndatums;

	/*
	 * If there are no values to compare with the datums in boundinfo, it
	 * means the caller asked for partitions for all non-null datums.  Add
	 * indexes of *all* partitions, including the default partition if one
	 * exists.
	 */
	if (nvalues == 0)
	{
		/* ignore key space not covered by any partitions */
		if (partindices[minoff] < 0)
			minoff++;
		if (partindices[maxoff] < 0)
			maxoff--;

		result->scan_default = partition_bound_has_default(boundinfo);
		Assert(partindices[minoff] >= 0 &&
			   partindices[maxoff] >= 0);
		result->bound_offsets = bms_add_range(NULL, minoff, maxoff);

		return result;
	}

	/*
	 * If the query does not constrain all key columns, we'll need to scan the
	 * default partition, if any.
	 */
	if (nvalues < partnatts)
		result->scan_default = partition_bound_has_default(boundinfo);

	switch (opstrategy)
	{
		case BTEqualStrategyNumber:
			/* Look for the smallest bound that is = lookup value. */
			off = partition_range_datum_bsearch(partsupfunc,
												partcollation,
												boundinfo,
												nvalues, values,
												&is_equal);

			if (off >= 0 && is_equal)
			{
				if (nvalues == partnatts)
				{
					/* There can only be zero or one matching partition. */
					result->bound_offsets = bms_make_singleton(off + 1);
					return result;
				}
				else
				{
					int			saved_off = off;

					/*
					 * Since the lookup value contains only a prefix of keys,
					 * we must find other bounds that may also match the
					 * prefix.  partition_range_datum_bsearch() returns the
					 * offset of one of them, find others by checking adjacent
					 * bounds.
					 */

					/*
					 * First find greatest bound that's smaller than the
					 * lookup value.
					 */
					while (off >= 1)
					{
						int32		cmpval;

						cmpval =
							partition_rbound_datum_cmp(partsupfunc,
													   partcollation,
													   boundinfo->datums[off - 1],
													   boundinfo->kind[off - 1],
													   values, nvalues);
						if (cmpval != 0)
							break;
						off--;
					}

					Assert(0 ==
						   partition_rbound_datum_cmp(partsupfunc,
													  partcollation,
													  boundinfo->datums[off],
													  boundinfo->kind[off],
													  values, nvalues));

					/*
					 * We can treat 'off' as the offset of the smallest bound
					 * to be included in the result, if we know it is the
					 * upper bound of the partition in which the lookup value
					 * could possibly exist.  One case it couldn't is if the
					 * bound, or precisely the matched portion of its prefix,
					 * is not inclusive.
					 */
					if (boundinfo->kind[off][nvalues] ==
						PARTITION_RANGE_DATUM_MINVALUE)
						off++;

					minoff = off;

					/*
					 * Now find smallest bound that's greater than the lookup
					 * value.
					 */
					off = saved_off;
					while (off < boundinfo->ndatums - 1)
					{
						int32		cmpval;

						cmpval = partition_rbound_datum_cmp(partsupfunc,
															partcollation,
															boundinfo->datums[off + 1],
															boundinfo->kind[off + 1],
															values, nvalues);
						if (cmpval != 0)
							break;
						off++;
					}

					Assert(0 ==
						   partition_rbound_datum_cmp(partsupfunc,
													  partcollation,
													  boundinfo->datums[off],
													  boundinfo->kind[off],
													  values, nvalues));

					/*
					 * off + 1, then would be the offset of the greatest bound
					 * to be included in the result.
					 */
					maxoff = off + 1;
				}

				Assert(minoff >= 0 && maxoff >= 0);
				result->bound_offsets = bms_add_range(NULL, minoff, maxoff);
			}
			else
			{
				/*
				 * The lookup value falls in the range between some bounds in
				 * boundinfo.  'off' would be the offset of the greatest bound
				 * that is <= lookup value, so add off + 1 to the result
				 * instead as the offset of the upper bound of the only
				 * partition that may contain the lookup value.  If 'off' is
				 * -1 indicating that all bounds are greater, then we simply
				 * end up adding the first bound's offset, that is, 0.
				 */
				result->bound_offsets = bms_make_singleton(off + 1);
			}

			return result;

		case BTGreaterEqualStrategyNumber:
			inclusive = true;
			/* fall through */
		case BTGreaterStrategyNumber:

			/*
			 * Look for the smallest bound that is > or >= lookup value and
			 * set minoff to its offset.
			 */
			off = partition_range_datum_bsearch(partsupfunc,
												partcollation,
												boundinfo,
												nvalues, values,
												&is_equal);
			if (off < 0)
			{
				/*
				 * All bounds are greater than the lookup value, so include
				 * all of them in the result.
				 */
				minoff = 0;
			}
			else
			{
				if (is_equal && nvalues < partnatts)
				{
					/*
					 * Since the lookup value contains only a prefix of keys,
					 * we must find other bounds that may also match the
					 * prefix.  partition_range_datum_bsearch() returns the
					 * offset of one of them, find others by checking adjacent
					 * bounds.
					 *
					 * Based on whether the lookup values are inclusive or
					 * not, we must either include the indexes of all such
					 * bounds in the result (that is, set minoff to the index
					 * of smallest such bound) or find the smallest one that's
					 * greater than the lookup values and set minoff to that.
					 */
					while (off >= 1 && off < boundinfo->ndatums - 1)
					{
						int32		cmpval;
						int			nextoff;

						nextoff = inclusive ? off - 1 : off + 1;
						cmpval =
							partition_rbound_datum_cmp(partsupfunc,
													   partcollation,
													   boundinfo->datums[nextoff],
													   boundinfo->kind[nextoff],
													   values, nvalues);
						if (cmpval != 0)
							break;

						off = nextoff;
					}

					Assert(0 ==
						   partition_rbound_datum_cmp(partsupfunc,
													  partcollation,
													  boundinfo->datums[off],
													  boundinfo->kind[off],
													  values, nvalues));

					minoff = inclusive ? off : off + 1;
				}
				else
				{

					/*
					 * lookup value falls in the range between some bounds in
					 * boundinfo.  off would be the offset of the greatest
					 * bound that is <= lookup value, so add off + 1 to the
					 * result instead as the offset of the upper bound of the
					 * smallest partition that may contain the lookup value.
					 */
					minoff = off + 1;
				}
			}
			break;

		case BTLessEqualStrategyNumber:
			inclusive = true;
			/* fall through */
		case BTLessStrategyNumber:

			/*
			 * Look for the greatest bound that is < or <= lookup value and
			 * set maxoff to its offset.
			 */
			off = partition_range_datum_bsearch(partsupfunc,
												partcollation,
												boundinfo,
												nvalues, values,
												&is_equal);
			if (off >= 0)
			{
				/*
				 * See the comment above.
				 */
				if (is_equal && nvalues < partnatts)
				{
					while (off >= 1 && off < boundinfo->ndatums - 1)
					{
						int32		cmpval;
						int			nextoff;

						nextoff = inclusive ? off + 1 : off - 1;
						cmpval = partition_rbound_datum_cmp(partsupfunc,
															partcollation,
															boundinfo->datums[nextoff],
															boundinfo->kind[nextoff],
															values, nvalues);
						if (cmpval != 0)
							break;

						off = nextoff;
					}

					Assert(0 ==
						   partition_rbound_datum_cmp(partsupfunc,
													  partcollation,
													  boundinfo->datums[off],
													  boundinfo->kind[off],
													  values, nvalues));

					maxoff = inclusive ? off + 1 : off;
				}

				/*
				 * The lookup value falls in the range between some bounds in
				 * boundinfo.  'off' would be the offset of the greatest bound
				 * that is <= lookup value, so add off + 1 to the result
				 * instead as the offset of the upper bound of the greatest
				 * partition that may contain lookup value.  If the lookup
				 * value had exactly matched the bound, but it isn't
				 * inclusive, no need add the adjacent partition.
				 */
				else if (!is_equal || inclusive)
					maxoff = off + 1;
				else
					maxoff = off;
			}
			else
			{
				/*
				 * 'off' is -1 indicating that all bounds are greater, so just
				 * set the first bound's offset as maxoff.
				 */
				maxoff = off + 1;
			}
			break;

		default:
			elog(ERROR, "invalid strategy number %d", opstrategy);
			break;
	}

	Assert(minoff >= 0 && minoff <= boundinfo->ndatums);
	Assert(maxoff >= 0 && maxoff <= boundinfo->ndatums);

	/*
	 * If the smallest partition to return has MINVALUE (negative infinity) as
	 * its lower bound, increment it to point to the next finite bound
	 * (supposedly its upper bound), so that we don't advertently end up
	 * scanning the default partition.
	 */
	if (minoff < boundinfo->ndatums && partindices[minoff] < 0)
	{
		int			lastkey = nvalues - 1;

		if (boundinfo->kind[minoff][lastkey] ==
			PARTITION_RANGE_DATUM_MINVALUE)
		{
			minoff++;
			Assert(boundinfo->indexes[minoff] >= 0);
		}
	}

	/*
	 * If the previous greatest partition has MAXVALUE (positive infinity) as
	 * its upper bound (something only possible to do with multi-column range
	 * partitioning), we scan switch to it as the greatest partition to
	 * return.  Again, so that we don't advertently end up scanning the
	 * default partition.
	 */
	if (maxoff >= 1 && partindices[maxoff] < 0)
	{
		int			lastkey = nvalues - 1;

		if (boundinfo->kind[maxoff - 1][lastkey] ==
			PARTITION_RANGE_DATUM_MAXVALUE)
		{
			maxoff--;
			Assert(boundinfo->indexes[maxoff] >= 0);
		}
	}

	Assert(minoff >= 0 && maxoff >= 0);
	if (minoff <= maxoff)
		result->bound_offsets = bms_add_range(NULL, minoff, maxoff);

	return result;
}