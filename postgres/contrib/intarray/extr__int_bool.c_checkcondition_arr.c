#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_5__ {scalar_t__* arre; scalar_t__* arrb; } ;
struct TYPE_4__ {scalar_t__ val; } ;
typedef  TYPE_1__ ITEM ;
typedef  TYPE_2__ CHKVAL ;

/* Variables and functions */

__attribute__((used)) static bool
checkcondition_arr(void *checkval, ITEM *item)
{
	int32	   *StopLow = ((CHKVAL *) checkval)->arrb;
	int32	   *StopHigh = ((CHKVAL *) checkval)->arre;
	int32	   *StopMiddle;

	/* Loop invariant: StopLow <= val < StopHigh */

	while (StopLow < StopHigh)
	{
		StopMiddle = StopLow + (StopHigh - StopLow) / 2;
		if (*StopMiddle == item->val)
			return true;
		else if (*StopMiddle < item->val)
			StopLow = StopMiddle + 1;
		else
			StopHigh = StopMiddle;
	}
	return false;
}