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
typedef  int StrategyNumber ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_BOOL (int) ; 
#define  RTContainedByStrategyNumber 137 
#define  RTContainsStrategyNumber 136 
#define  RTLeftStrategyNumber 135 
#define  RTOldContainedByStrategyNumber 134 
#define  RTOldContainsStrategyNumber 133 
#define  RTOverLeftStrategyNumber 132 
#define  RTOverRightStrategyNumber 131 
#define  RTOverlapStrategyNumber 130 
#define  RTRightStrategyNumber 129 
#define  RTSameStrategyNumber 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  seg_contains ; 
 int /*<<< orphan*/  seg_left ; 
 int /*<<< orphan*/  seg_over_left ; 
 int /*<<< orphan*/  seg_over_right ; 
 int /*<<< orphan*/  seg_overlap ; 
 int /*<<< orphan*/  seg_right ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static Datum
gseg_internal_consistent(Datum key, Datum query, StrategyNumber strategy)
{
	bool		retval;

#ifdef GIST_QUERY_DEBUG
	fprintf(stderr, "internal_consistent, %d\n", strategy);
#endif

	switch (strategy)
	{
		case RTLeftStrategyNumber:
			retval =
				!DatumGetBool(DirectFunctionCall2(seg_over_right, key, query));
			break;
		case RTOverLeftStrategyNumber:
			retval =
				!DatumGetBool(DirectFunctionCall2(seg_right, key, query));
			break;
		case RTOverlapStrategyNumber:
			retval =
				DatumGetBool(DirectFunctionCall2(seg_overlap, key, query));
			break;
		case RTOverRightStrategyNumber:
			retval =
				!DatumGetBool(DirectFunctionCall2(seg_left, key, query));
			break;
		case RTRightStrategyNumber:
			retval =
				!DatumGetBool(DirectFunctionCall2(seg_over_left, key, query));
			break;
		case RTSameStrategyNumber:
		case RTContainsStrategyNumber:
		case RTOldContainsStrategyNumber:
			retval =
				DatumGetBool(DirectFunctionCall2(seg_contains, key, query));
			break;
		case RTContainedByStrategyNumber:
		case RTOldContainedByStrategyNumber:
			retval =
				DatumGetBool(DirectFunctionCall2(seg_overlap, key, query));
			break;
		default:
			retval = false;
	}

	PG_RETURN_BOOL(retval);
}