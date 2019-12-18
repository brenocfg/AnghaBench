#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_2__ low; TYPE_1__ high; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int StrategyNumber ;
typedef  TYPE_3__ Point ;
typedef  TYPE_4__ BOX ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FPeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FPgt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FPlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RTAboveStrategyNumber 132 
#define  RTBelowStrategyNumber 131 
#define  RTLeftStrategyNumber 130 
#define  RTRightStrategyNumber 129 
#define  RTSameStrategyNumber 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
gist_point_consistent_internal(StrategyNumber strategy,
							   bool isLeaf, BOX *key, Point *query)
{
	bool		result = false;

	switch (strategy)
	{
		case RTLeftStrategyNumber:
			result = FPlt(key->low.x, query->x);
			break;
		case RTRightStrategyNumber:
			result = FPgt(key->high.x, query->x);
			break;
		case RTAboveStrategyNumber:
			result = FPgt(key->high.y, query->y);
			break;
		case RTBelowStrategyNumber:
			result = FPlt(key->low.y, query->y);
			break;
		case RTSameStrategyNumber:
			if (isLeaf)
			{
				/* key.high must equal key.low, so we can disregard it */
				result = (FPeq(key->low.x, query->x) &&
						  FPeq(key->low.y, query->y));
			}
			else
			{
				result = (FPle(query->x, key->high.x) &&
						  FPge(query->x, key->low.x) &&
						  FPle(query->y, key->high.y) &&
						  FPge(query->y, key->low.y));
			}
			break;
		default:
			elog(ERROR, "unrecognized strategy number: %d", strategy);
			result = false;		/* keep compiler quiet */
			break;
	}

	return result;
}