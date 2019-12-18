#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ float8 ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 scalar_t__ ARR_DATA_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_NDIM (int /*<<< orphan*/ *) ; 
 int ArrayGetNItems (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static int
width_bucket_array_float8(Datum operand, ArrayType *thresholds)
{
	float8		op = DatumGetFloat8(operand);
	float8	   *thresholds_data;
	int			left;
	int			right;

	/*
	 * Since we know the array contains no NULLs, we can just index it
	 * directly.
	 */
	thresholds_data = (float8 *) ARR_DATA_PTR(thresholds);

	left = 0;
	right = ArrayGetNItems(ARR_NDIM(thresholds), ARR_DIMS(thresholds));

	/*
	 * If the probe value is a NaN, it's greater than or equal to all possible
	 * threshold values (including other NaNs), so we need not search.  Note
	 * that this would give the same result as searching even if the array
	 * contains multiple NaNs (as long as they're correctly sorted), since the
	 * loop logic will find the rightmost of multiple equal threshold values.
	 */
	if (isnan(op))
		return right;

	/* Find the bucket */
	while (left < right)
	{
		int			mid = (left + right) / 2;

		if (isnan(thresholds_data[mid]) || op < thresholds_data[mid])
			right = mid;
		else
			left = mid + 1;
	}

	return left;
}