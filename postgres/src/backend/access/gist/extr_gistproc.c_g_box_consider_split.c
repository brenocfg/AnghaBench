#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ float8 ;
typedef  scalar_t__ float4 ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_6__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_8__ {TYPE_2__ low; TYPE_1__ high; } ;
struct TYPE_9__ {int entriesCount; int first; int dim; scalar_t__ overlap; scalar_t__ ratio; scalar_t__ range; scalar_t__ leftUpper; scalar_t__ rightLower; TYPE_3__ boundingBox; } ;
typedef  TYPE_4__ ConsiderSplitContext ;

/* Variables and functions */
 scalar_t__ LIMIT_RATIO ; 
 int /*<<< orphan*/  Min (int,int) ; 
 scalar_t__ float4_div (int /*<<< orphan*/ ,int) ; 
 scalar_t__ float8_div (scalar_t__,scalar_t__) ; 
 scalar_t__ float8_mi (scalar_t__,scalar_t__) ; 
 scalar_t__ non_negative (scalar_t__) ; 

__attribute__((used)) static inline void
g_box_consider_split(ConsiderSplitContext *context, int dimNum,
					 float8 rightLower, int minLeftCount,
					 float8 leftUpper, int maxLeftCount)
{
	int			leftCount,
				rightCount;
	float4		ratio,
				overlap;
	float8		range;

	/*
	 * Calculate entries distribution ratio assuming most uniform distribution
	 * of common entries.
	 */
	if (minLeftCount >= (context->entriesCount + 1) / 2)
	{
		leftCount = minLeftCount;
	}
	else
	{
		if (maxLeftCount <= context->entriesCount / 2)
			leftCount = maxLeftCount;
		else
			leftCount = context->entriesCount / 2;
	}
	rightCount = context->entriesCount - leftCount;

	/*
	 * Ratio of split - quotient between size of lesser group and total
	 * entries count.
	 */
	ratio = float4_div(Min(leftCount, rightCount), context->entriesCount);

	if (ratio > LIMIT_RATIO)
	{
		bool		selectthis = false;

		/*
		 * The ratio is acceptable, so compare current split with previously
		 * selected one. Between splits of one dimension we search for minimal
		 * overlap (allowing negative values) and minimal ration (between same
		 * overlaps. We switch dimension if find less overlap (non-negative)
		 * or less range with same overlap.
		 */
		if (dimNum == 0)
			range = float8_mi(context->boundingBox.high.x,
							  context->boundingBox.low.x);
		else
			range = float8_mi(context->boundingBox.high.y,
							  context->boundingBox.low.y);

		overlap = float8_div(float8_mi(leftUpper, rightLower), range);

		/* If there is no previous selection, select this */
		if (context->first)
			selectthis = true;
		else if (context->dim == dimNum)
		{
			/*
			 * Within the same dimension, choose the new split if it has a
			 * smaller overlap, or same overlap but better ratio.
			 */
			if (overlap < context->overlap ||
				(overlap == context->overlap && ratio > context->ratio))
				selectthis = true;
		}
		else
		{
			/*
			 * Across dimensions, choose the new split if it has a smaller
			 * *non-negative* overlap, or same *non-negative* overlap but
			 * bigger range. This condition differs from the one described in
			 * the article. On the datasets where leaf MBRs don't overlap
			 * themselves, non-overlapping splits (i.e. splits which have zero
			 * *non-negative* overlap) are frequently possible. In this case
			 * splits tends to be along one dimension, because most distant
			 * non-overlapping splits (i.e. having lowest negative overlap)
			 * appears to be in the same dimension as in the previous split.
			 * Therefore MBRs appear to be very prolonged along another
			 * dimension, which leads to bad search performance. Using range
			 * as the second split criteria makes MBRs more quadratic. Using
			 * *non-negative* overlap instead of overlap as the first split
			 * criteria gives to range criteria a chance to matter, because
			 * non-overlapping splits are equivalent in this criteria.
			 */
			if (non_negative(overlap) < non_negative(context->overlap) ||
				(range > context->range &&
				 non_negative(overlap) <= non_negative(context->overlap)))
				selectthis = true;
		}

		if (selectthis)
		{
			/* save information about selected split */
			context->first = false;
			context->ratio = ratio;
			context->range = range;
			context->overlap = overlap;
			context->rightLower = rightLower;
			context->leftUpper = leftUpper;
			context->dim = dimNum;
		}
	}
}