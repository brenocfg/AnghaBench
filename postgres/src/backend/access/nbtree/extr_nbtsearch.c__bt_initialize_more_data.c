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
struct TYPE_4__ {int moreLeft; int moreRight; } ;
struct TYPE_5__ {int markItemIndex; scalar_t__ numKilled; TYPE_1__ currPos; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_2__* BTScanOpaque ;

/* Variables and functions */
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
_bt_initialize_more_data(BTScanOpaque so, ScanDirection dir)
{
	/* initialize moreLeft/moreRight appropriately for scan direction */
	if (ScanDirectionIsForward(dir))
	{
		so->currPos.moreLeft = false;
		so->currPos.moreRight = true;
	}
	else
	{
		so->currPos.moreLeft = true;
		so->currPos.moreRight = false;
	}
	so->numKilled = 0;			/* just paranoia */
	so->markItemIndex = -1;		/* ditto */
}