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
typedef  int /*<<< orphan*/  BOX ;

/* Variables and functions */
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
#define  RTAboveStrategyNumber 141 
#define  RTBelowStrategyNumber 140 
#define  RTContainedByStrategyNumber 139 
#define  RTContainsStrategyNumber 138 
#define  RTLeftStrategyNumber 137 
#define  RTOldContainedByStrategyNumber 136 
#define  RTOldContainsStrategyNumber 135 
#define  RTOverAboveStrategyNumber 134 
#define  RTOverBelowStrategyNumber 133 
#define  RTOverLeftStrategyNumber 132 
#define  RTOverRightStrategyNumber 131 
#define  RTOverlapStrategyNumber 130 
#define  RTRightStrategyNumber 129 
#define  RTSameStrategyNumber 128 
 int /*<<< orphan*/  box_above ; 
 int /*<<< orphan*/  box_below ; 
 int /*<<< orphan*/  box_contain ; 
 int /*<<< orphan*/  box_left ; 
 int /*<<< orphan*/  box_overabove ; 
 int /*<<< orphan*/  box_overbelow ; 
 int /*<<< orphan*/  box_overlap ; 
 int /*<<< orphan*/  box_overleft ; 
 int /*<<< orphan*/  box_overright ; 
 int /*<<< orphan*/  box_right ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
rtree_internal_consistent(BOX *key, BOX *query, StrategyNumber strategy)
{
	bool		retval;

	switch (strategy)
	{
		case RTLeftStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_overright,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTOverLeftStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_right,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTOverlapStrategyNumber:
			retval = DatumGetBool(DirectFunctionCall2(box_overlap,
													  PointerGetDatum(key),
													  PointerGetDatum(query)));
			break;
		case RTOverRightStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_left,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTRightStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_overleft,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTSameStrategyNumber:
		case RTContainsStrategyNumber:
		case RTOldContainsStrategyNumber:
			retval = DatumGetBool(DirectFunctionCall2(box_contain,
													  PointerGetDatum(key),
													  PointerGetDatum(query)));
			break;
		case RTContainedByStrategyNumber:
		case RTOldContainedByStrategyNumber:
			retval = DatumGetBool(DirectFunctionCall2(box_overlap,
													  PointerGetDatum(key),
													  PointerGetDatum(query)));
			break;
		case RTOverBelowStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_above,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTBelowStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_overabove,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTAboveStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_overbelow,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		case RTOverAboveStrategyNumber:
			retval = !DatumGetBool(DirectFunctionCall2(box_below,
													   PointerGetDatum(key),
													   PointerGetDatum(query)));
			break;
		default:
			elog(ERROR, "unrecognized strategy number: %d", strategy);
			retval = false;		/* keep compiler quiet */
			break;
	}
	return retval;
}